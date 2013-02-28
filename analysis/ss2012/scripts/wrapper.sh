#!/bin/bash

#
# args
#

FILEID=$1
FILE=$2
SAMPLE=$3
ATYPE=$4
RUNLIST=$5
OPTIONS=$6
COPYDIR=$7

echo "[wrapper] FILEID   = " ${FILEID}   | ./appendTimeStamp.sh
echo "[wrapper] FILE     = " ${FILE}     | ./appendTimeStamp.sh
echo "[wrapper] SAMPLE   = " ${SAMPLE}   | ./appendTimeStamp.sh
echo "[wrapper] ATYPE    = " ${ATYPE}    | ./appendTimeStamp.sh
echo "[wrapper] RUNLIST  = " ${RUNLIST}  | ./appendTimeStamp.sh
echo "[wrapper] OPTIONS  = " ${OPTIONS}  | ./appendTimeStamp.sh
echo "[wrapper] COPYDIR  = " ${COPYDIR}  | ./appendTimeStamp.sh
echo

#
# set up environment
#
echo
echo "[wrapper] setting env" | ./appendTimeStamp.sh
export CMS_PATH=/code/osgcode/cmssoft/cms
export SCRAM_ARCH=slc5_amd64_gcc462
source /code/osgcode/cmssoft/cmsset_default.sh
source /code/osgcode/fgolf/5.30-patches/bin/thisroot.sh
export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
echo

echo
echo "[wrapper] envirment variables" | ./appendTimeStamp.sh
/bin/env
echo

#
# print out which worker node 
#
echo
echo "[wrapper] worker node is" `/bin/hostname` | ./appendTimeStamp.sh
echo "[wrapper] running as user " `/usr/bin/whoami` | ./appendTimeStamp.sh
echo

#
# untar input sandbox
#
echo
echo "[wrapper] extracting input sandbox" | ./appendTimeStamp.sh
tar -zxvf input.tgz
echo

#
# run it
#

ls -l ${FILE}
if [ $? -ne 0 ]; then
    echo ${FILE} "[wrapper] is missing or is inaccessable" | ./appendTimeStamp.sh
    exit 99
fi

#
# set a job exit code for record keeping
#
JOB_EXIT_CODE=-0

#
# check directory permissions
#
echo
echo "[wrapper} permission of CWD: " `ls -ld $PWD` | ./appendTimeStamp.sh
echo

#
# begin time stamp
#
echo
echo "[wrapper] starting job: " | ./appendTimeStamp.sh
echo

echo -e "
#!/bin/bash

# run the driver script
./driver.sh ${FILE} ${FILEID} ${SAMPLE} ${ATYPE} ${RUNLIST} ${OPTIONS}

# test the output
JOB_EXIT_CODE=`echo $?`
if [[ $JOB_EXIT_CODE -ne 0 ]] ; then
    echo
    echo "[runme.sh] JOB_EXIT_CODE = $JOB_EXIT_CODE" 
    echo
fi
" > runme.sh

echo
if [ ! -f runme.sh ]; then
    echo "[wrapper] runme.sh doesn't exist." | ./appendTimeStamp.sh
    JOB_EXIT_CODE=99
else
    echo "runme.sh is:" | ./appendTimeStamp.sh
    echo
    cat runme.sh
fi
echo

if [[ $JOB_EXIT_CODE -ne 0 ]] ; then
    echo
    echo "[wrapper] JOB_EXIT_CODE = $JOB_EXIT_CODE" | ./appendTimeStamp.sh
    echo
    exit $JOB_EXIT_CODE
fi

source runme.sh

#
# record runme exit code
#
JOB_EXIT_CODE=`echo $?`
if [[ $JOB_EXIT_CODE -ne 0 ]] ; then
    echo
    echo "[wrapper] JOB_EXIT_CODE = $JOB_EXIT_CODE" | ./appendTimeStamp.sh
    echo
fi

#
# end time stamp
#
echo
echo "[wrapper] ending job: " | ./appendTimeStamp.sh
echo

#
# do something with output
#

ls -la
echo
echo "[wrapper] checking certificate" | ./appendTimeStamp.sh
voms-proxy-info --all
echo

#
# only copy files that pass sweepRoot
#
echo
echo "[wrapper] copying file" | ./appendTimeStamp.sh
OUTPUT=`ls ./ | grep ${FILEID}`
./sweepRoot -o tree $OUTPUT
echo OUTPUT = $OUTPUT
ls -l $OUTPUT
#if [ $(du -b $OUTPUT | cut -f 1) -le 23136 ];
echo ./sweepRoot -o tree $OUTPUT
if [ $(./sweepRoot -o tree $OUTPUT 2>&1 | grep SUMMARY | awk '{print $2}') == 0 ];
then 
    echo "[wrapper] preparing to transfer $OUTPUT to ${COPYDIR}/${OUTPUT}..." | ./appendTimeStamp.sh
    lcg-cp -b -D srmv2 --vo cms -t 2400 --verbose file:`pwd`/${OUTPUT} srm://bsrm-1.t2.ucsd.edu:8443/srm/v2/server?SFN=${COPYDIR}/${OUTPUT}
else
    echo "[wrapper] $OUTPUT is considered bad by sweepRoot..." | ./appendTimeStamp.sh
fi
echo

#
# clean up
#
echo
echo "[wrapper] cleaning up" | ./appendTimeStamp.sh
for FILE in `find . -not -name "*stderr" -not -name "*stdout"`; do rm -rf $FILE; done
echo "[wrapper] cleaned up"
ls
