#input: /afs/cern.ch/work/c/cirkovic/FlatTree_sync/CMSSW_8_0_12/src/FlatTree/FlatTreeProducer/test/output.root

#./NtupleProducer
#--file list.txt // txt file with the list of input FlatTree files to read
#--tree FlatTree/tree // name of FlatTree TTree directory
#--outfile "output" // name of the output ROOT file
#--noe 666 // initial number of events for considered dataset to be used for normalization
#--xsec 6.66 // cross section for considered dataset to be used for normalization
#--nmax -1 // max number of events to process (-1: no limit)
#--isdata 0 // run on data or MC
#--stream -1 // 0: SingleElectron, 1: SingleMuon (only for data)
#--issig 0 // flag to mark signal events (1: signal)

cd /afs/cern.ch/work/c/cirkovic/FCNC_sync/CMSSW_8_0_12/src/tHFCNC/NtupleProducer
export LD_LIBRARY_PATH=${PWD}:${PWD}/obj:$LD_LIBRARY_PATH
make
cd test

OPTIONS=""
OPTIONS="$OPTIONS --file list1.txt" # txt file with the list of input FlatTree files to read
OPTIONS="$OPTIONS --tree FlatTree/tree" # name of FlatTree TTree directory
OPTIONS="$OPTIONS --outfile output_mu" # name of the output ROOT file
OPTIONS="$OPTIONS --noe 45000" # initial number of events for considered dataset to be used for normalization
OPTIONS="$OPTIONS --xsec 1.0" # cross section for considered dataset to be used for normalization
OPTIONS="$OPTIONS --nmax -1" # max number of events to process (-1: no limit)
OPTIONS="$OPTIONS --isdata 0" # run on data or MC
OPTIONS="$OPTIONS --stream -1" # 0: SingleElectron, 1: SingleMuon (only for data)
OPTIONS="$OPTIONS --issig 0" # flag to mark signal events (1: signal)
OPTIONS="$OPTIONS --sync 1" # 1 for muons, 0 for electrons

./NtupleProducer $OPTIONS

OPTIONS=""
OPTIONS="$OPTIONS --file list1.txt" # txt file with the list of input FlatTree files to read
OPTIONS="$OPTIONS --tree FlatTree/tree" # name of FlatTree TTree directory
OPTIONS="$OPTIONS --outfile output_el" # name of the output ROOT file
OPTIONS="$OPTIONS --noe 45000" # initial number of events for considered dataset to be used for normalization
OPTIONS="$OPTIONS --xsec 1.0" # cross section for considered dataset to be used for normalization
OPTIONS="$OPTIONS --nmax -1" # max number of events to process (-1: no limit)
OPTIONS="$OPTIONS --isdata 0" # run on data or MC
OPTIONS="$OPTIONS --stream -1" # 0: SingleElectron, 1: SingleMuon (only for data)
OPTIONS="$OPTIONS --issig 0" # flag to mark signal events (1: signal)
OPTIONS="$OPTIONS --sync 0" # 1 for muons, 0 for electrons

./NtupleProducer $OPTIONS

echo `cat events.txt`      `cat events.txt`
echo `cat muons.txt`       `cat electrons.txt`
echo `cat tmuons.txt`      `cat melectrons.txt`
echo `cat nlelectrons.txt` `cat nlmuons.txt`
echo `cat vlmuons.txt`     `cat vlelectrons.txt`
echo `cat jetsm.txt`       `cat jetse.txt`
