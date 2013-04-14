#!/bin/bash

#
# Write a crab config and a wrapper script
# to submit a looper job
#

if [ $# -lt 6 ]; then
    echo "
USAGE: ./BatchProcessViaCrab.sh PSET TASK ARGS
    DSET    - cmssw dataset name
    TASK    - Unique name for this task (will be used to produce the crab_\${TASK}.cfg, wrapper_\${TASK}.sh, cms2_\${TASK}.sh)
    DBSURL  - DBS URL for the dataset 
    OUTFILE - Name of outfile (i.e. baby.root,myMassDB.root)
	WORKDIR - Working directory for crab output
    ARGS    - Argument values for wrapper script (comma separated - put \"\" as default for none)
	USELUMI - Argument to determine where to use the total number of lumis or events
	CMS2TAG - CMS2 tag 
	VSPARM  - quoated escaped comma sperated list of the sparms. eg. \"sparm1\",\"sparm2\"
	FASTSIM - fastsim flag is set (default is true since mostly use this for signal scans)
	GT      - Global tag to use
"
    exit 1
fi

DSET=$1
TASK=$2
DBSURL=$3
OUTFILE=$4
WORKING_DIR=$5
ARGS=$6
USELUMI=${7:-0}
CMS2TAG=${8:-V05-03-28}
VSPARMS=${9:-}
FASTSIM=${10:-1}
GLOBALTAG=${11:-START52_V9A::All}
CRABCFG=crab_${TASK}.cfg
WRAPPER=wrapper_${TASK}.sh
CMS2=cms2_${TASK}_cfg.py
INPUTS=input.tgz

#
# move the inputs.tgz to local dir
#

cp job_inputs/${INPUTS} .

#
# kludge for UFL's f-ed up sample
#

if [ ${USELUMI} -eq 0 ]; then
	JOBFLAGS="events_per_job          = 10000
total_number_of_events  = -1"
else
	JOBFLAGS="total_number_of_jobs    = 5000
total_number_of_lumis   = -1
lumis_per_job           = 6"
fi


#
# This is the CMS2 configuration
# to sumbit the looper job
#

# if the VSPARMS flag isn't empty, set up the sparmmaker
if [ "${VSPARMS}" != "" ]; then
	SPARMMAKER="# list of sparm parameters, be sure it is the same size as the number of parameter in the files
process.sParmMaker.vsparms = cms.untracked.vstring(${VSPARMS})
process.cms2WithEverything.replace(process.eventmakers, process.eventmakerswsparm) #adds the sparm producer in to the sequence
"
else
	SPARMMAKER=""
fi

# set the flags for faststim
if [ ${FASTSIM} -ne 0 ]; then
	HBHENOISE="process.cms2WithEverything.remove(process.cms2HBHENoiseFilterResultProducer) #need to remove this product for fastsim"
else
	HBHENOISE=""
fi

cat > ${CMS2} << EOF
import sys, os
sys.path.append( os.getenv("CMSSW_BASE") + "/src/CMS2/NtupleMaker/test" )
from CMS2.NtupleMaker.RecoConfiguration2012_cfg import *

# Global Tag
process.GlobalTag.globaltag = "${GLOBALTAG}"

# Output
process.out = cms.OutputModule(
        "PoolOutputModule",
        fileName     = cms.untracked.string('ntuple.root'),
        dropMetaData = cms.untracked.string("NONE")
)
process.outpath = cms.EndPath(process.out)

# Branches
process.out.outputCommands = cms.untracked.vstring( 'drop *' )
process.out.outputCommands.extend(cms.untracked.vstring('keep *_*Maker*_*_CMS2*'))
process.out.outputCommands.extend(cms.untracked.vstring('drop *_cms2towerMaker*_*_CMS2*'))
process.out.outputCommands.extend(cms.untracked.vstring('drop CaloTowers*_*_*_CMS2*'))

#
process.cms2WithEverything = cms.Sequence( process.ak5PFJets * process.kt6PFJets * process.cms2CoreSequence * process.cms2PFNoTauSequence * process.cms2GENSequence )
process.cms2WithEverything.remove(process.jptMaker)
process.cms2WithEverything.remove(process.hypTrilepMaker)
process.cms2WithEverything.remove(process.hypQuadlepMaker)
${HBHENOISE}
process.p = cms.Path(process.cms2WithEverything)

#
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.eventMaker.isData = cms.bool(False)
process.luminosityMaker.isData = process.eventMaker.isData
process.eventMaker.datasetName = cms.string("${DSET}")
process.eventMaker.CMS2tag = cms.string("${CMS2TAG}")

#Slim CMS2
from CMS2.NtupleMaker.SlimCms2_cff import slimcms2
process.out.outputCommands.extend(slimcms2)

${SPARMMAKER}

# to prevent crash when merging files
process.options.fileMode = cms.untracked.string('NOMERGE')

# input (for testing interactively)
process.maxEvents.input = 1
process.source.fileNames = [
	'file:/home/users/rwkelley/Data/nfs-7/edm/SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM_AODSIM_UFLPrivate_9196.root'
]
EOF

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
pset                    = ${CMS2}
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
echo "[wrapper] args = " \$@
echo "[wrapper] options = " \$options
echo "[wrapper] printenv:"
printenv

#
# library path
#
LD_LIBRARY_PATH=\${LD_LIBRARY_PATH}:\$PWD
echo "[wrapper]: LD_LIBRARY_PATH"
echo "\${LD_LIBRARY_PATH}"

#
# run CMSSW
#

cmsRun -j \$RUNTIME_AREA/crab_fjr_\$JobIndex.xml -p pset.py

echo "[wrapper] testing file"
echo ./sweepRoot -o Events ntuple.root
if [ \$(./sweepRoot -o Events ntuple.root 2>&1 | grep SUMMARY | awk '{print \$2}') == 0 ]; 
then 
    echo "[wrapper] ntuple.root file is good!"
else
    echo "[wrapper] ntuple.root is considered bad by sweepRoot..."
    exit 1
fi

# 
# run the "post processing" to insert dummy values for the branches
# (TODO: maybe make this more meaningful later)
#

for f in \$(ls ntuple*.root); 
do
	post_file=\${f%.*}_post.root
	cmd="./add_cms2_branches --input \$f --output \$post_file --xsec -999999.0 --num_events -999999 --kfactor 1.0 --filter_eff 1.0"
	echo "[wrapper]: \${cmd}" 
	eval \${cmd}
done

#
# run looper
#

# hack to get the looper to work
export PAC=\$PWD
export CMS2CORE=\$PWD

# run my looper.....
cmd="./ss2012_analysis --input \"ntuple*_post.root\" --output ${OUTFILE} ${ARGS}"
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

#
# sweepRoot
#

echo "[wrapper] testing file"
echo ./sweepRoot -o tree ${OUTFILE}
if [ \$(./sweepRoot -o tree ${OUTFILE} 2>&1 | grep SUMMARY | awk '{print \$2}') == 0 ]; 
then 
    echo "[wrapper] ${OUTFILE} file is good!"
else
    echo "[wrapper] ${OUTFILE} is considered bad by sweepRoot..."
    rm ${OUTFILE}
    exit 1
fi


EOF
chmod +x ${WRAPPER}
