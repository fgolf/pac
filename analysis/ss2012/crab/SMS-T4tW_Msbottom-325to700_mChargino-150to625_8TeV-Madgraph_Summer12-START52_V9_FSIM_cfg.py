import sys, os
sys.path.append( os.getenv("CMSSW_BASE") + "/src/CMS2/NtupleMaker/test" )
from CMS2.NtupleMaker.RecoConfiguration2012_cfg import *

# Global Tag
process.GlobalTag.globaltag = "START52_V9A::All"

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
process.cms2WithEverything.remove(process.cms2HBHENoiseFilterResultProducer) #need to remove this product for fastsim
process.p = cms.Path(process.cms2WithEverything)

#
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.eventMaker.isData = cms.bool(False)
process.luminosityMaker.isData = process.eventMaker.isData

#Slim CMS2
from CMS2.NtupleMaker.SlimCms2_cff import slimcms2
process.out.outputCommands.extend(slimcms2)
process.eventMaker.datasetName = cms.string("/SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph/Summer12-START52_V9_FSIM/USER")
process.eventMaker.CMS2tag = cms.string("V05-03-23")

# list of sparm parameters, be sure it is the same size as the number of parameter in the files
process.sParmMaker.vsparms = cms.untracked.vstring("msbottom","mchargino","mlsp")
process.cms2WithEverything.replace(process.eventmakers, process.eventmakerswsparm) #adds the sparm producer in to the sequence

# to prevent crash when merging files
process.options.fileMode = cms.untracked.string('NOMERGE')

# input
process.maxEvents.input = 1
process.source.fileNames = [
	'file:/home/users/rwkelley/Data/edm/SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph_Summer12-START52_V9_FSIM_AODSIM_UFLPrivate_9196.root'
]
