#!/bin/bash

#
# args
#

FILEID=$1
DATATYPE=$2
FILE=$3
REALDATA=$4
RUNLIST=$5
COPYDIR=$6

echo "[wrapper] FILEID    = " ${FILEID}
echo "[wrapper] DATATYPE  = " ${DATATYPE}
echo "[wrapper] FILE      = " ${FILE}
echo "[wrapper] REALDATA  = " ${REALDATA}
echo "[wrapper] RUNLIST   = " ${RUNLIST}
echo "[wrapper] COPYDIR   = " ${COPYDIR}

#
# set up environment
#

echo "[wrapper] setting env"
#source /code/osgcode/fgolf/5.30-patches/bin/thisroot.sh
source /code/osgcode/imacneill/root/05.34.07/bin/thisroot.sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
export PATH=:$PATH:$PWD
export PAC=$PWD
env
# export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH                                     

#
# untar input sandbox
#

echo "[wrapper] extracting input sandbox"
tar -zxvf input.tgz

#
# print out which worker node 
#
echo "[wrapper] worker node is"
/bin/hostname 
/usr/bin/whoami

#
# check the file's existence
#
ls -l ${FILE}
if [ $? -ne 0 ]; then
    echo ${FILE} "[wrapper] is missing or is inaccessable"
    exit 99
fi

#
# run it
#

echo "
{
gROOT->ProcessLine(\".L processData.C\");
processData(\"${FILEID}\", ${DATATYPE}, \"${FILE}\", ${REALDATA}, \"${RUNLIST}\");
}
" > runme.C
root -b -q runme.C

#
# do something with output
#

ls -la
echo "[wrapper] checking certificate"
voms-proxy-info --all

#
# only copy files that pass sweepRoot
#

echo "[wrapper] copying file"
OUTPUT=`ls ./ | grep ${FILEID}`
./sweepRoot -o tree $OUTPUT
echo OUTPUT = $OUTPUT
echo ./sweepRoot -o tree $OUTPUT
if [ $(./sweepRoot -o tree $OUTPUT 2>&1 | grep SUMMARY | awk '{print $2}') == 0 ]; 
then 
    echo "[wrapper] preparing to transfer $OUTPUT to ${COPYDIR}/${OUTPUT}..."
    lcg-cp -b -D srmv2 --vo cms -t 2400 --verbose file:`pwd`/${OUTPUT} srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${OUTPUT}
else
    echo "[wrapper] $OUTPUT is considered bad by sweepRoot..."
fi

#
# clean up
#

echo "[wrapper] cleaning up"
for FILE in `find . -not -name "*stderr" -not -name "*stdout"`; do rm -rf $FILE; done
echo "[wrapper] cleaned up"
ls


