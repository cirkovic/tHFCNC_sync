#INBASE=http://test-cirkovic.web.cern.ch/test-cirkovic/01-12-2015/Synchronization/1
INBASE=http://test-cirkovic.web.cern.ch/test-cirkovic/25-01-2016/Synchronization/1

OUTBASE=~/www/25-01-2016/Synchronization_compare/1/

sh compare_CERN_CERN.sh $OUTBASE -1 $INBASE
sh compare_CERN_ND.sh $OUTBASE -1 $INBASE
sh compare_CERN_IPHC.sh $OUTBASE -1 $INBASE
sh compare_CERN_IHEP.sh $OUTBASE -1 $INBASE
