#include "../include/NtupleProducer.h"

#include "Riostream.h"
#include "TSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <assert.h>
#include <fstream>


//#include <Cintex/Cintex.h>

Tree *ntP;
TChain *ch;
Ntuple *nt;
std::vector<int> *evdebug;
int _isdata;

BTagCalibration *calib;
BTagCalibrationReader *reader_iterativefit;

unsigned int idx;

int main(int argc, char *argv[])
{
   if( argc < 4 )
     {
	std::cout << "NtupleProducer usage:" << std::endl;
	std::cout << "--file: input filename" << std::endl;
	std::cout << "--tree: TTree name" << std::endl;
	std::cout << "--noe : Number of events" << std::endl;
	std::cout << "--xsec: Cross-section" << std::endl;
	std::cout << "--nmax: Max number of events" << std::endl;
	std::cout << "--outfile: output file" << std::endl;
	std::cout << "--isdata: is data flag" << std::endl;
	std::cout << "--stream: data stream" << std::endl;
	std::cout << "--issig: is signal" << std::endl;
	std::cout << "--isttbar: is ttbar" << std::endl;
    std::cout << "--sync: lepton type" << std::endl;
	exit(1);
     }
   
   const char *fname_str = "output.root";
   const char *stream_str = "FlatTree/tree";
   float noe = 1.;
   float xsec = 1.;
   int nmax = -1;
   const char *outfile_str = "666";
   _isdata = 0;
   int dataStream = -1;
   int issig = 0;
   int isttbar = 0;
   int leptontype = 0;
   
   for(int i=0;i<argc;i++)
     {
	if( ! strcmp(argv[i],"--file") ) fname_str = argv[i+1];
	if( ! strcmp(argv[i],"--tree") ) stream_str = argv[i+1];
	if( ! strcmp(argv[i],"--noe") ) noe = atof(argv[i+1]);
	if( ! strcmp(argv[i],"--xsec") ) xsec = atof(argv[i+1]);
	if( ! strcmp(argv[i],"--nmax") ) nmax = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--outfile") ) outfile_str = argv[i+1];
	if( ! strcmp(argv[i],"--isdata") ) _isdata = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--stream") ) dataStream = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--issig") ) issig = atoi(argv[i+1]);
	if( ! strcmp(argv[i],"--isttbar") ) isttbar = atoi(argv[i+1]);
    if( ! strcmp(argv[i],"--sync") ) leptontype = atoi(argv[i+1]);
     }   

   const char *fname  = fname_str;
   const char *stream = stream_str;
   const char *outfile = outfile_str;
   
   std::cout << "--file=" << fname << std::endl;
   std::cout << "--tree=" << stream << std::endl;
   std::cout << "--noe=" << noe << std::endl;
   std::cout << "--xsec=" << xsec << std::endl;
   std::cout << "--nmax=" << nmax << std::endl;
   std::cout << "--outfile=" << outfile << std::endl;
   std::cout << "--isdata=" << _isdata << std::endl;
   std::cout << "--stream=" << dataStream << std::endl;
   std::cout << "--issig=" << issig << std::endl;
   std::cout << "--isttbar=" << isttbar << std::endl;
   std::cout << "--sync=" << leptontype << std::endl;

   ofstream evfile;
   evfile.open("events.txt");
   evfile.close();
   ofstream lepfile;
   if (leptontype)
       lepfile.open("muons.txt");
   else
       lepfile.open("electrons.txt");
   lepfile.close();
   ofstream wplfile;
   if (leptontype)
       wplfile.open("tmuons.txt");
   else
       wplfile.open("melectrons.txt");
   wplfile.close();
   ofstream nllfile;
   if (leptontype)
       nllfile.open("nlelectrons.txt");
   else
       nllfile.open("nlmuons.txt");
   nllfile.close();
   ofstream nvlfile;
   if (leptontype)
       nvlfile.open("vlmuons.txt");
   else
       nvlfile.open("vlelectrons.txt");
   nvlfile.close();
   ofstream jetfile;
   if (leptontype)
       jetfile.open("jetsm.txt");
   else
       jetfile.open("jetse.txt");
   jetfile.close();

   //FILE *_fev = fopen("/afs/cern.ch/user/c/cirkovic/www/14-11-2016/FCNC_sync_2/eventlist1.txt", "w");
   //FILE *_fev = fopen("/afs/cern.ch/user/c/cirkovic/www/15-11-2016/FCNC_sync_2/eventlist1.txt", "w");
   //FILE *_fev = fopen("/afs/cern.ch/user/c/cirkovic/www/16a-11-2016/FCNC_sync_2/eventlist1.txt", "w");
   /*
   FILE *_fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/16b-11-2016/FCNC_sync_2/eventlist1.txt", "w");
   FILE *_fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/16b-11-2016/FCNC_sync_2/eventlist2.txt", "w");
   FILE *_fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/16b-11-2016/FCNC_sync_2/eventlist3.txt", "w");
   FILE *_fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/16b-11-2016/FCNC_sync_2/eventlist4.txt", "w");
   FILE *_fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/16b-11-2016/FCNC_sync_2/eventlist5.txt", "w");
   FILE *_fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/16b-11-2016/FCNC_sync_2/eventlist6.txt", "w");
   */
   /*
   FILE *_fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/16c-11-2016/FCNC_sync_2/eventlist1.txt", "w");
   FILE *_fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/16c-11-2016/FCNC_sync_2/eventlist2.txt", "w");
   FILE *_fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/16c-11-2016/FCNC_sync_2/eventlist3.txt", "w");
   FILE *_fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/16c-11-2016/FCNC_sync_2/eventlist4.txt", "w");
   FILE *_fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/16c-11-2016/FCNC_sync_2/eventlist5.txt", "w");
   FILE *_fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/16c-11-2016/FCNC_sync_2/eventlist6.txt", "w");
   */
   /*
   FILE *_fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/16d-11-2016/FCNC_sync_2/eventlist1.txt", "w");
   FILE *_fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/16d-11-2016/FCNC_sync_2/eventlist2.txt", "w");
   FILE *_fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/16d-11-2016/FCNC_sync_2/eventlist3.txt", "w");
   FILE *_fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/16d-11-2016/FCNC_sync_2/eventlist4.txt", "w");
   FILE *_fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/16d-11-2016/FCNC_sync_2/eventlist5.txt", "w");
   FILE *_fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/16d-11-2016/FCNC_sync_2/eventlist6.txt", "w");
   */
   /*
   FILE *_fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist1.txt", "w");
   FILE *_fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist2.txt", "w");
   FILE *_fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist3.txt", "w");
   FILE *_fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist4.txt", "w");
   FILE *_fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist5.txt", "w");
   FILE *_fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist6.txt", "w");
   FILE *_fev7 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist7.txt", "w");
   FILE *_fev8 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_1/eventlist8.txt", "w");
   */
   FILE *_fev1;
   FILE *_fev2;
   FILE *_fev3;
   FILE *_fev4;
   FILE *_fev5;
   FILE *_fev6;
   FILE *_fev7;
   FILE *_fev8;

   /*
   if (leptontype) {
    _fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist1.txt", "w");
    _fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist2.txt", "w");
    _fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist3.txt", "w");
    _fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist4.txt", "w");
    _fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist5.txt", "w");
    _fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist6.txt", "w");
    _fev7 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist7.txt", "w");
    _fev8 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_mu/eventlist8.txt", "w");
   }
   else {
    _fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist1.txt", "w");
    _fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist2.txt", "w");
    _fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist3.txt", "w");
    _fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist4.txt", "w");
    _fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist5.txt", "w");
    _fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist6.txt", "w");
    _fev7 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist7.txt", "w");
    _fev8 = fopen("/afs/cern.ch/user/c/cirkovic/www/29-11-2016/FCNC_syn_el/eventlist8.txt", "w");
  }
   */
   if (leptontype) {
    _fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist1.txt", "w");
    _fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist2.txt", "w");
    _fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist3.txt", "w");
    _fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist4.txt", "w");
    _fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist5.txt", "w");
    _fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist6.txt", "w");
    _fev7 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist7.txt", "w");
    _fev8 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_mu/eventlist8.txt", "w");
   }
   else {
    _fev1 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist1.txt", "w");
    _fev2 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist2.txt", "w");
    _fev3 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist3.txt", "w");
    _fev4 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist4.txt", "w");
    _fev5 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist5.txt", "w");
    _fev6 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist6.txt", "w");
    _fev7 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist7.txt", "w");
    _fev8 = fopen("/afs/cern.ch/user/c/cirkovic/www/30-11-2016/FCNC_syn_el/eventlist8.txt", "w");
  }

   std::cout << fname << std::endl;
   Tree tree(0,const_cast<char*>(fname),stream);
   ntP = &tree;
   
   ch = tree.fChain;
   Long64_t nentries = ch->GetEntries();
   ntP->registerInputBranches(ch);
   
   nt = new Ntuple();

   nt->Init(std::string(outfile));
   nt->createVar();
   nt->setBranchAddress();

   Electron el;
   Muon mu;
   Jet jet;
   Event ev;
   Truth truth;

   calib = new BTagCalibration("csvv2","/afs/cern.ch/work/c/cirkovic/FCNC_sync/CMSSW_8_0_12/src/tHFCNC/NtupleProducer/test/CSVv2_ichep.csv");
   reader_iterativefit = new BTagCalibrationReader(BTagEntry::OP_RESHAPING,"central",
						   {"up_jes","down_jes","up_lf","down_lf",
							"up_hf","down_hf",
							"up_hfstats1","down_hfstats1",
							"up_hfstats2","down_hfstats2",
							"up_lfstats1","down_lfstats1",
							"up_lfstats2","down_lfstats2",
							"up_cferr1","down_cferr1",
							"up_cferr2","down_cferr2"});
   reader_iterativefit->load(*calib,BTagEntry::FLAV_B,"iterativefit");
   reader_iterativefit->load(*calib,BTagEntry::FLAV_C,"iterativefit");
   reader_iterativefit->load(*calib,BTagEntry::FLAV_UDSG,"iterativefit");

   std::cout << "BTagCalibration initialized" << std::endl;
   
   evdebug = new std::vector<int>();
//   evdebug->push_back(91408);
   
   std::cout << "Input events = " << nentries << std::endl;
   
   int Nev = 0;
   int Nmet = 0;
   int Ntl = 0;
   int N1xl = 0; //int N1tm = 0;   //int N1me = 0;
   int Nnll = 0;
   int Nvll = 0;
   int N3j = 0;
   for(Long64_t i=0;i<nentries;i++)  {

//	std::cout << i << std::endl;
	if( nmax >= 0 && i >= nmax ) break;
	
	ch->GetEntry(i);

	nt->clearVar();	
	
	// event
	ev.init();
	ev.read(xsec,noe,dataStream,issig,isttbar);

    fprintf(_fev1,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev1,"\n");

    if (ev.isFake() || ev.ndof() < 4 || ev.pv_rho() > 2 || fabs(ev.z()) > 24) continue;
    Nev++;

    fprintf(_fev2,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev2,"\n");

    if (!ev.passMETFilters()) continue;
    Nmet++;

    fprintf(_fev3,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev3,"\n");

    if (leptontype && (!ev.isTrigMuon())) continue;
    else if ((!leptontype) && (!ev.isTrigElec())) continue;
    Ntl++;

    fprintf(_fev4,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev4,"\n");

	nt->NtEvent->push_back(ev);
	
	// muons
	for(int j=0;j<ntP->mu_n;j++)
	  {
	     idx = j;
	     
	     mu.init();
	     mu.read();
	     mu.sel();
	
	     if( mu.isLoose() ) nt->NtMuonLoose->push_back(mu);	     
	     if( mu.isTight() ) nt->NtMuonTight->push_back(mu);	     

         if( mu.isLoose() && ! mu.isTight() ) nt->NtMuonLooseExtra->push_back(mu);
	  }		

	// electrons
	for(int j=0;j<ntP->el_n;j++)
	  {
	     idx = j;
	     
	     el.init();
	     el.read();
	     el.sel();

	     if( el.isLoose() ) nt->NtElectronLoose->push_back(el);
	     if( el.isMedium() ) nt->NtElectronMedium->push_back(el);
	     //if( el.isTight() ) nt->NtElectronTight->push_back(el);
	     if( el.isMedium() ) nt->NtElectronTight->push_back(el);

         if( el.isLoose() && ! el.isMedium() ) nt->NtElectronLooseExtra->push_back(el);
	  }

    int nElecLoose = nt->NtElectronLoose->size();
    int nMuonLoose = nt->NtMuonLoose->size();

    int nElecTight = nt->NtElectronTight->size();
    int nElecMedium = nt->NtElectronMedium->size();
    int nMuonTight = nt->NtMuonTight->size();

    int nElecLooseExtra = nt->NtElectronLooseExtra->size();
    int nMuonLooseExtra = nt->NtMuonLooseExtra->size();

    if (leptontype && (nMuonTight != 1)) continue;
    else if ((!leptontype) && (nElecMedium != 1)) continue;
    N1xl++;

    fprintf(_fev5,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev5,"\n");

    if (leptontype && (nElecLoose > 0)) continue;
    else if ((!leptontype) && (nMuonLoose > 0)) continue;
    Nnll++;

    fprintf(_fev6,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev6,"\n");

    if (leptontype && (nMuonLooseExtra > 0)) continue;
    else if ((!leptontype) && (nElecLooseExtra > 0)) continue;
    Nvll++;

    fprintf(_fev7,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev7,"\n");

	// jets
	for(int j=0;j<ntP->jet_n;j++)
	  {
	     idx = j;
	     
	     jet.init();
	     jet.read();
	     jet.sel();

	     if( jet.isLoose() ) nt->NtJetLoose->push_back(jet);
	     if( jet.isTight() ) nt->NtJetTight->push_back(jet);
	     if( jet.isTight() && jet.isBTag() ) nt->NtBJetTight->push_back(jet);
	  }

	if( !_isdata )
	  {	     
	     // truth
	     truth.init();
	     truth.read();
	     
	     nt->NtTruth->push_back(truth);
	  }	

	//int nElecLoose = nt->NtElectronLoose->size();
	//int nMuonLoose = nt->NtMuonLoose->size();
	
	//int nElecTight = nt->NtElectronTight->size();
	//int nMuonTight = nt->NtMuonTight->size();

	int nJetLoose = nt->NtJetLoose->size();
	int nJetTight = nt->NtJetTight->size();
	int nJetBTag = nt->NtBJetTight->size();

    /*
	if(
	   nElecTight+nMuonTight == 1 &&
	   nElecLoose+nMuonLoose == 1 &&
	   nJetTight >= 3
	  )
	  {
	     nt->fill();
	  }
    */
    //if (nJetTight < 3) continue;
    if (nJetLoose < 3) continue;
    //if (nJetLoose < 2) continue;
    N3j++;

    fprintf(_fev8,"%6d %6d %10d", ev.run(), ev.lumi(), ev.id());
    fprintf(_fev8,"\n");

    //std::cout << "cirkovic: filling #" << N3j << std::endl;
    nt->fill();
   }


   if (leptontype)
      evfile.open("events_mu.txt");
   else
      evfile.open("events_el.txt");
   evfile << Nev << "\n";
   evfile.close();

   if (leptontype)
       evfile.open("metfilters_mu.txt");
   else
       evfile.open("metfilters_el.txt");
   evfile << Nmet << "\n";
   evfile.close();

   if (leptontype)
       lepfile.open("muons.txt");
   else
       lepfile.open("electrons.txt");
   lepfile << Ntl << "\n";
   lepfile.close();

   if (leptontype)
       wplfile.open("tmuons.txt");
   else
       wplfile.open("melectrons.txt");
   wplfile << N1xl << "\n";
   wplfile.close();

   if (leptontype)
       nllfile.open("nlelectrons.txt");
   else
       nllfile.open("nlmuons.txt");
   nllfile << Nnll << "\n";
   nllfile.close();

   if (leptontype)
       nvlfile.open("vlmuons.txt");
   else
       nvlfile.open("vlelectrons.txt");
   nvlfile << Nvll << "\n";
   nvlfile.close();

   if (leptontype)
       jetfile.open("jetsm.txt");
   else
       jetfile.open("jetse.txt");
   jetfile << N3j << "\n";
   jetfile.close();

   fclose(_fev1);
   fclose(_fev2);
   fclose(_fev3);
   fclose(_fev4);
   fclose(_fev5);
   fclose(_fev6);
   fclose(_fev7);
   fclose(_fev8);

   std::cout << "Output events = " << nt->m_tree->GetEntries() << std::endl;

   delete nt;
}
