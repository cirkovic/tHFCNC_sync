#include "include/NtupleProducer.h"

ClassImp(Electron)
    
Electron::Electron()
{
}

Electron::~Electron()
{
}

double Electron::effArea(double _eta)
{
   double EffArea = 0.0;

   if     ( fabs(_eta) >= 0.0000 && fabs(_eta) < 1.0000 )   EffArea = 0.1703;
   else if( fabs(_eta) >= 1.0000 && fabs(_eta) < 1.4790 )   EffArea = 0.1715;
   else if( fabs(_eta) >= 1.4790 && fabs(_eta) < 2.0000 )   EffArea = 0.1213;
   else if( fabs(_eta) >= 2.0000 && fabs(_eta) < 2.2000 )   EffArea = 0.1230;
   else if( fabs(_eta) >= 2.2000 && fabs(_eta) < 2.3000 )   EffArea = 0.1635;
   else if( fabs(_eta) >= 2.3000 && fabs(_eta) < 2.4000 )   EffArea = 0.1937;
   else if( fabs(_eta) >= 2.4000 && fabs(_eta) < 5.0000 )   EffArea = 0.2393;

   return EffArea;
}


double Electron::effAreaCorrection(double _eta)
{
   return ntP->ev_rho * effArea(_eta);
   //return ntP->pv_rho * effArea(_eta);
}

void Electron::read()
{
   _ID = idx;
   
   _E   = ntP->el_E->at(idx);
   _pt  = ntP->el_pt->at(idx);
   _eta = ntP->el_eta->at(idx);
   _scleta = ntP->el_superCluster_eta->at(idx);
   _phi = ntP->el_phi->at(idx);
   _m   = ntP->el_m->at(idx);
   _dxy   = ntP->el_gsfTrack_PV_dxy->at(idx);
   _dz   = ntP->el_gsfTrack_PV_dz->at(idx);
   
   _charge   = ntP->el_charge->at(idx);
   _id   = ntP->el_id->at(idx);
   
   _isLooseCBId   = ntP->el_looseCBId->at(idx);
   _isMediumCBId   = ntP->el_mediumCBId->at(idx);
   _isTightCBId   = ntP->el_tightCBId->at(idx);
   
   if(_pt > 0.) _p4.SetPtEtaPhiE(_pt,_eta,_phi,_E);

   _superClusterEta = ntP->el_superCluster_eta->at(idx);
   _deltaEtaIn = ntP->el_deltaEtaSuperClusterTrackAtVtx->at(idx); // el_deltaEtaSeedClusterTrackAtCalo
   _deltaPhiIn = ntP->el_deltaPhiSuperClusterTrackAtVtx->at(idx); // el_deltaPhiSeedClusterTrackAtCalo
   _sigmaIEtaIEta_full5x5 = ntP->el_sigmaIetaIeta->at(idx);
   _hadronicOverEm = ntP->el_hadronicOverEm->at(idx);
   _ioEmIoP = ntP->el_IoEmIoP->at(idx);
   //_pfElectronIso = ntP->el_ecalPFClusterIso->at(idx); // el_ecalPFClusterIso, el_hcalPFClusterIso, el_pfIso_sumChargedHadronPt, el_pfIso_sumNeutralHadronEt, el_pfIso_sumPhotonEt, el_pfIso_sumPUPt
   //_pfElectronIso = (ntP->el_pfIso_sumChargedHadronPt->at(idx)+ std::max(ntP->el_pfIso_sumNeutralHadronEt->at(idx)+ntP->el_pfIso_sumPhotonEt->at(idx)-0.5*ntP->el_pfIso_sumPUPt->at(idx),0.0))/_pt; // el_ecalPFClusterIso, el_hcalPFClusterIso, el_pfIso_sumChargedHadronPt, el_pfIso_sumNeutralHadronEt, el_pfIso_sumPhotonEt, el_pfIso_sumPUPt
   _pfElectronIso = (ntP->el_pfIso_sumChargedHadronPt->at(idx)+ std::max(0.0, ntP->el_pfIso_sumNeutralHadronEt->at(idx)+ntP->el_pfIso_sumPhotonEt->at(idx)-effAreaCorrection(_eta)))/_pt; // el_ecalPFClusterIso, el_hcalPFClusterIso, el_pfIso_sumChargedHadronPt, el_pfIso_sumNeutralHadronEt, el_pfIso_sumPhotonEt, el_pfIso_sumPUPt
   _missingHits = ntP->el_numberOfLostHits->at(idx); // el_numberOfLostPixelHits, el_numberOfLostHits, el_numberOfLostHitsDefault, el_expectedMissingInnerHits, el_expectedMissingOuterHits

   _sumChargedHadronPt = ntP->el_pfIso_sumChargedHadronPt->at(idx);
   _sumNeutralHadronEt = ntP->el_pfIso_sumNeutralHadronEt->at(idx);
   _sumPhotonEt = ntP->el_pfIso_sumPhotonEt->at(idx);
   _rho = ntP->ev_rho;
   //_rho = ntP->pv_rho;
   _Aeff = effArea(_eta);
   
}

void Electron::init()
{
   _E        = VDEF;
   _pt       = VDEF;
   _eta      = VDEF;
   _phi      = VDEF;
   _m        = VDEF;
   _dxy        = VDEF;
   _dz        = VDEF;
   
   _isLoose   = 0;
   _isMedium  = 0;
   _isTight   = 0;
      
   _charge   = 0;
   _id   = 0;
   
   _isLooseCBId = 0;
   _isMediumCBId = 0;
   _isTightCBId = 0;
   
   _relIso = 0;

   _superClusterEta = 0;
   _deltaEtaIn = 0;
   _deltaPhiIn = 0;
   _sigmaIEtaIEta_full5x5 = 0;
   _hadronicOverEm = 0;
   _ioEmIoP = 0;
   _pfElectronIso = 0;
   _missingHits = 0;

   _sumChargedHadronPt = 0;
   _sumNeutralHadronEt = 0;
   _sumPhotonEt = 0;
   _rho = 0;
   _Aeff = 0;

}

void Electron::sel()
{   
   bool passPtLoose = (_pt > 10.);
   bool passPtMedium = (_pt > 35.);
   bool passPtTight = (_pt > 40.);
   bool passEtaLoose = (fabs(_eta) < 2.5);
   bool passEtaMedium = (fabs(_eta) < 2.1);
   bool passDxy = (fabs(_dxy) < 0.05);   
   bool passDz = (fabs(_dz) < 0.1);   
   bool passCrack = !(abs(_scleta) > 1.4442 && abs(_scleta) < 1.5660);   
   bool passConversionVeto = ntP->el_passConversionVeto->at(idx);
   
   //_relIso = (ntP->el_pfIso_sumChargedHadronPt->at(idx)+
   //      std::max(ntP->el_pfIso_sumNeutralHadronEt->at(idx)+ntP->el_pfIso_sumPhotonEt->at(idx)-
   //	       0.5*ntP->el_pfIso_sumPUPt->at(idx),0.0))/_pt;

   _relIso = (ntP->el_pfIso_sumChargedHadronPt->at(idx) +
              //std::max(0.0, ntP->el_pfIso_sumNeutralHadronPt->at(idx) + ntP->el_pfIso_sumPhotonPt->at(idx) - correction)
              //std::max(0.0, ntP->el_pfIso_sumNeutralHadronEt->at(idx) + ntP->el_pfIso_sumPhotonEt->at(idx) - correction)
              std::max(0.0, ntP->el_pfIso_sumNeutralHadronEt->at(idx) + ntP->el_pfIso_sumPhotonEt->at(idx) - effAreaCorrection(_eta))
             )/_pt;

   
   bool passRelIsoLoose = (_relIso < 0.25);
   bool passRelIsoMedium = (_relIso < 0.20);
   bool passRelIsoTight = (_relIso < 0.15);
   
   _isLoose = (
	       passPtLoose &&
	       passEtaLoose &&
	       //passDxy &&
	       //passDz &&
	       //passCrack &&
	       //passConversionVeto &&
	       //passRelIsoLoose &&
	       _isLooseCBId &&
	      true );

   /*
   _isMedium = (
           passPtMedium &&
           passEtaMedium &&
           //passDxy &&
           //passDz &&
           //passCrack &&
           //passConversionVeto &&
           passRelIsoMedium &&
           _isMediumCBId &&
          true );
    */

    if (fabs(_superClusterEta) <= 1.479) {
       _isMedium = (
               passPtMedium &&
               passEtaMedium &&
               _sigmaIEtaIEta_full5x5 <  0.00998 &&
               fabs(_deltaEtaIn)      <  0.00311 &&
               fabs(_deltaPhiIn)      <  0.103   &&
               _hadronicOverEm        <  0.253   &&
               _relIso                <  0.0695  &&
               fabs(_ioEmIoP)         <  0.134   &&
               _missingHits           <= 1       &&
               passConversionVeto                &&
              true );
    }
    else if (fabs(_superClusterEta) > 1.479) {
       _isMedium = (
               passPtMedium &&
               passEtaMedium &&
               _sigmaIEtaIEta_full5x5 <  0.0298  &&
               fabs(_deltaEtaIn)      <  0.00609 &&
               fabs(_deltaPhiIn)      <  0.045   &&
               _hadronicOverEm        <  0.0878  &&
               _relIso                <  0.0821  &&
               fabs(_ioEmIoP)         <  0.13    &&
               _missingHits           <= 1       &&
               passConversionVeto                &&
              true );
    }

   _isTight = (
	       _isLoose &&
	       passPtTight &&
	       _isMediumCBId &&
	       passRelIsoTight
	      );
   
   for(int id=0;id<evdebug->size();id++)
     {	
	if( nt->NtEvent->at(0).id() == evdebug->at(id) )
	  {
	     std::cout << "Electron #" << _ID << std::endl;
	     std::cout << "   pt=" << _pt << " eta=" << _eta << " phi=" << _phi << std::endl;
	  }
     }
}
