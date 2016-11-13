#ifndef READER
#define READER

#include <vector>
#include <iostream>
#include <fstream>

#include "Electron.h"
#include "Muon.h"
#include "Jet.h"
#include "Event.h"
#include "Truth.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom3.h"

#include "../include/Lepton.h"
#include "../include/Ranges.h"

//#include "../CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
//#include "../CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

extern char *flog;

#define CHECK_BIT(var,pos) (((var) & (1<<(pos))) != 0 )

#endif
