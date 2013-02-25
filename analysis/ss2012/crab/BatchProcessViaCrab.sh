#!/bin/bash

#
# Write a crab config and a wrapper script
# to submit a looper job
#


if [ ! $# -eq 6 ]; then
    echo "
USAGE: ./BatchProcessViaCrab.sh PSET TASK ARGS
    PSET    - the name of the CMSSW pset you want to run
    DSET    - cmssw dataset name
    TASK    - Unique name for this task (will be used to produce the crab_${TASK}.cfg, wrapper_${TASK}.sh)
    DBSURL  - DBS URL for the dataset 
    OUTFILE - Name of outfile (i.e. baby.root,myMassDB.root)
    ARGS    - Argument values for wrapper script (comma separated - put \"\" as default for none)
"
    exit 1
fi

MYPSET=$1
DSET=$2
TASK=$3
DBSURL=$4
OUTFILE=$5
ARGS=$6
CRABCFG=crab_${TASK}.cfg
WRAPPER=wrapper_${TASK}.sh
INPUTS=input.tgz
WORKING_DIR="/nfs-7/userdata/${USER}/babies/cms2_V05-03-23_ss2012_V02-05-01"

JOBFLAGS="events_per_job          = 10000
total_number_of_events  = -1"
if [ ${DSET} == "/SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph/Summer12-START52_V9_FSIM/USER" ]; then
JOBFLAGS="lumis_per_job           = 100
total_number_of_lumis   = -1"
fi


#
# This is the crab configuration
# to sumbit the looper job
#

cat > ${CRABCFG} << EOF

[CRAB]
jobtype   = cmssw
scheduler = remoteGlidein
use_server = 0

[CMSSW]
datasetpath             = ${DSET}
pset                    = ${MYPSET}
output_file             = ${OUTFILE}
${JOBFLAGS}
ignore_edm_output       = 1
dbs_url                 = ${DBSURL} 

[USER]
script_exe              = ${WRAPPER}
script_arguments        = ${ARGS}
return_data             = 1
ui_working_dir          = ${WORKING_DIR}/${TASK}
additional_input_files  = ${INPUTS}


EOF

#
# make the tar file to run the looper
# include everything needed to run looper
#

cp job_inputs/${INPUTS} .

#
# This is the wrapper that will run
# the looper on the remote WN
# - the first argument is always the job index
# - the latter arguments are as provided in the crab cfg
#

cat > ${WRAPPER} << EOF
#!/bin/bash

tar -zxf ${INPUTS}

#
# args
#

JobIndex=\$1

echo "[wrapper] JobIndex = " \${JobIndex}

#
# run CMSSW
#

cmsRun -j \$RUNTIME_AREA/crab_fjr_\$JobIndex.xml -p pset.py

# 
# run the "post processing" to insert dummy values for the branches
# (TODO: maybe make this more meaningful later)
#

root -b -q -l "AddCMS2Branches.C+(\"ntuple.root\", \"ntuple_postprocessed.root\", -999999, -999999.0, 1.0, 1.0)"

#
# library path
#
LD_LIBRARY_PATH=\${LD_LIBRARY_PATH}:\$PWD
echo "[wrapper]: LD_LIBRARY_PATH"
echo "\${LD_LIBRARY_PATH}"

#
# run looper
#

# run my looper.....
cmd="./ss2012_analysis --input ntuple_postprocessed.root --output ${OUTFILE} ${ARGS}"
echo "[wrapper]: \${cmd}" 
eval \${cmd}

#
# at this point we should have
# a baby ntuple... :)
#
ls ${OUTFILE}
if [ \$? -ne 0 ]; then 
    echo "[wrapper]: ${OUTFILE} is missing" 
    exit 1
fi


EOF
chmod +x ${WRAPPER}
