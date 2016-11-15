INST=IPHC


OUTBASE=${1}/CERN_${INST}
rm -rf $OUTBASE
mkdir -p $OUTBASE

CURRDIR=`pwd`

cd $CURRDIR

TEST_DIR=test_muons_${INST}
rm -rf $TEST_DIR
mkdir $TEST_DIR
cd $TEST_DIR

FILE1=${3}/muons/cut2.txt
FILE2=https://www.dropbox.com/s/391vehv7nabvlb8/Muons.csv?dl=1
FILE2=https://www.dropbox.com/s/391vehv7nabvlb8/Muons.csv?dl=1
sed -i "1s/^/     event        pT       Eta       Phi         EpdgIDcharge        miniIso miniIsoCharged miniIsoNeutral  jetPtRel    jetCSVjetPtRatio     sip3D       dxy        dz segmentCompatibility\n/" $FILE2
wget $FILE1
wget $FILE2
FILE1=`basename $FILE1`
FILE2=`basename $FILE2`
tr -s " " < $FILE1 > ${FILE1}_1
tr -s " " < $FILE2 > ${FILE2}_1

if [[ "$2" == "-1" ]]; then
python ../compare_${INST}.py muons ${FILE1}_1 ${FILE2}_1 -1 > $OUTBASE/STDOUT_muons &
else
python ../compare_${INST}.py muons ${FILE1}_1 ${FILE2}_1 $2 &
fi


#exit


cd $CURRDIR

TEST_DIR=test_electrons_${INST}
rm -rf $TEST_DIR
mkdir $TEST_DIR
cd $TEST_DIR

FILE1=${3}/electrons/cut2.txt
FILE2=https://www.dropbox.com/s/s5xqmdchi19pn1f/LastElectronsForTonight.csv?dl=1
FILE2=https://www.dropbox.com/s/s5xqmdchi19pn1f/LastElectronsForTonight.csv?dl=1
sed -i "1s/^/     event        pT       Eta       Phi         EpdgIDcharge        miniIso miniIsoCharged miniIsoNeutral  jetPtRel    jetCSVjetPtRatio     sip3D       dxy        dz               eleMVA\n/" $FILE2
wget $FILE1
wget $FILE2
FILE1=`basename $FILE1`
FILE2=`basename $FILE2`

tr -s " " < $FILE1 > ${FILE1}_1
tr -s " " < $FILE2 > ${FILE2}_1

if [[ "$2" == "-1" ]]; then
python ../compare_${INST}.py electrons ${FILE1}_1 ${FILE2}_1 -1 > $OUTBASE/STDOUT_electrons &
else
python ../compare_${INST}.py electrons ${FILE1}_1 ${FILE2}_1 $2 &
fi


#exit


cd $CURRDIR

TEST_DIR=test_taus_${INST}
rm -rf $TEST_DIR
mkdir $TEST_DIR
cd $TEST_DIR

FILE1=${3}/taus/cut1.txt
FILE2=https://www.dropbox.com/s/3xbkfy091z37k6s/TausCleanedFromElectrons1.csv?dl=1
FILE2=https://www.dropbox.com/s/3xbkfy091z37k6s/TausCleanedFromElectrons1.csv?dl=1
sed -i "1s/^/ event       pT        Eta       Phi         E       dxy       dz decayModeFinding byLooseCombinedIsolationDeltaBetaCorr3Hits\n/" $FILE2
wget $FILE1
wget $FILE2
FILE1=`basename $FILE1`
FILE2=`basename $FILE2`
tr -s " " < $FILE1 > ${FILE1}_1
tr -s " " < $FILE2 > ${FILE2}_1

if [[ "$2" == "-1" ]]; then
python ../compare_${INST}.py taus ${FILE1}_1 ${FILE2}_1 -1 > $OUTBASE/STDOUT_taus &
else
python ../compare_${INST}.py taus ${FILE1}_1 ${FILE2}_1 $2 &
fi


#exit


cd $CURRDIR

TEST_DIR=test_jets_${INST}
rm -rf $TEST_DIR
mkdir $TEST_DIR
cd $TEST_DIR

FILE1=${3}/jets/cut1.txt
FILE2=https://www.dropbox.com/s/l21saxsg4b1j7ns/JetsCleanedFromTaus.csv?dl=1
FILE2=https://www.dropbox.com/s/l21saxsg4b1j7ns/JetsCleanedFromTaus.csv?dl=1
sed -i "1s/^/ event        pT       Eta       Phi         E     CSVv2    MET pt   MET phi\n/" $FILE2
wget $FILE1
wget $FILE2
FILE1=`basename $FILE1`
FILE2=`basename $FILE2`
tr -s " " < $FILE1 > ${FILE1}_1
tr -s " " < $FILE2 > ${FILE2}_1

if [[ "$2" == "-1" ]]; then
python ../compare_${INST}.py jets ${FILE1}_1 ${FILE2}_1 -1 > $OUTBASE/STDOUT_jets &
else
python ../compare_${INST}.py jets ${FILE1}_1 ${FILE2}_1 $2 &
fi

