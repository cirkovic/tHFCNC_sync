#include "include/NtupleProducer.h"

ClassImp(Electron)
    
Electron::Electron()
{
}

Electron::~Electron()
{
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
   _pfElectronIso = (ntP->el_pfIso_sumChargedHadronPt->at(idx)+ std::max(ntP->el_pfIso_sumNeutralHadronEt->at(idx)+ntP->el_pfIso_sumPhotonEt->at(idx)-0.5*ntP->el_pfIso_sumPUPt->at(idx),0.0))/_pt; // el_ecalPFClusterIso, el_hcalPFClusterIso, el_pfIso_sumChargedHadronPt, el_pfIso_sumNeutralHadronEt, el_pfIso_sumPhotonEt, el_pfIso_sumPUPt
   _missingHits = ntP->el_numberOfLostHits->at(idx); // el_numberOfLostPixelHits, el_numberOfLostHits, el_numberOfLostHitsDefault, el_expectedMissingInnerHits, el_expectedMissingOuterHits
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
   
   _relIso = (ntP->el_pfIso_sumChargedHadronPt->at(idx)+
	      std::max(ntP->el_pfIso_sumNeutralHadronEt->at(idx)+ntP->el_pfIso_sumPhotonEt->at(idx)-
		       0.5*ntP->el_pfIso_sumPUPt->at(idx),0.0))/_pt;
   
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

   _isMedium = (
           passPtMedium &&
           passEtaMedium &&
           //passDxy &&
           //passDz &&
           //passCrack &&
           //passConversionVeto &&
           //passRelIsoMedium &&
           _isMediumCBId &&
          true );

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
