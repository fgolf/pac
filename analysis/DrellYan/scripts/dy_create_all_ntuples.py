#!/usr/bin/env python

# imports
# ---------------------------------------------------------------------------------- #

from optparse import OptionParser
import os
import sys

# list of samples 
# ---------------------------------------------------------------------------------- #

samples = [
	"data",
	"dy",
	"wjets",
	"ttjets",
	#"ww",
	#"wz",
	#"zz",
	#"ttg",
	#"ttw",
	#"ttz",
	#"tbz",
	#"ttww",
	#"wwg",
	#"www",
	#"wwz",
	#"wzz",
	#"zzz",
	#"wmwmqq",
	#"wpwpqq",
	#"wgstar2e",
	#"wgstar2m",
	#"wgstar2t",
	#"ww_ds",
	#"dy",
	#"wjets",
	#"ttjets",
	#"ttdil",
	#"ttotr",
	#"ttslb",
	#"ttslo",
	#"t_schan",
	#"t_tchan",
	#"t_tw",
	#"wh_zh_tth_hww",
	#"wh_zh_tth_hzz",
	#"wh_zh_tth_htt",
]

# parse inputs
# ---------------------------------------------------------------------------------- #

parser = OptionParser()

goodrun = "json/Cert_190782-190949_8TeV_06Aug2012ReReco_Collisions12_cms2.txt"

# parameter options
parser.add_option("--nev"     , dest="nev"  , default=-1      , help="The number of events to run (-1 for all)")
parser.add_option("--lumi"    , dest="lumi" , default=0.082   , help="luminosity in fb^-1"                     )
parser.add_option("--run_list", dest="json" , default=goodrun , help="json file to run on"                     )

# boolean options
parser.add_option("--test"    , action="store_true" , dest="test"    , default=False , help="test script -- print commands but do nothing")
parser.add_option("--tensor"  , action="store_true" , dest="tensor"  , default=False , help="boolean to get files from mac"               )
parser.add_option("--verbose" , action="store_true" , dest="verbose" , default=False , help="verbose print out"                           )

(options, args) = parser.parse_args()

# generate the command 
# ---------------------------------------------------------------------------------- #

# get the files from my mac
def GetInputFilenameForTensor(sample):
	if sample == "data":
		path = "/nfs-7/userdata/rwkelley/cms2/Single*_Run2012A-recover-06Aug2012-v1_AOD.root"
	elif sample == "dy":
		path = "/nfs-7/userdata/rwkelley/cms2/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1.root"
	elif sample == "ttjets":
		path = "/nfs-7/userdata/rwkelley/cms2/TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2.root"
	elif sample == "wjets":
		path = "/nfs-7/userdata/rwkelley/cms2/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1.root"
	else:
		path = ""
	return path

# get the files from my mac
def GetInputFilenameForUaf(sample):
	if sample == "data":
		path = "%s,%s"  % \
			("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/merged/*.root",\
			 "/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/SingleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged/*.root")
	elif sample == "dy":
		path = "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_1[0-9].root"
	elif sample == "ttjets":
		path = "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-24/merged_ntuple_1[0-9].root"
	elif sample == "wjets":
		path = "/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_1[0-9].root"
	else:
		path = ""
	return path

# build the command per sample
def GetCommand(sample):
	cmd = "dy_create_ntuple --sample %s --nev %d" % (sample, options.nev)
	if (sample == "data"):
		cmd += " --run_list %s" % options.json
	if (options.tensor):
		cmd += " --input \"%s\"" % GetInputFilenameForTensor(sample)
	else:
		cmd += " --input \"%s\"" % GetInputFilenameForUaf(sample)
	cmd += " >& logs/%s_ntuple.log &" % sample
	return cmd

# "main program" 
# ---------------------------------------------------------------------------------- #

def main():

	try:
		# create log dir if it doesn't exist
		if not os.path.isdir("logs"):
			print "logs dir does not exist -- creating"
   			if (not options.test):
				os.makedirs("logs")

		for sample in samples:	
			cmd = GetCommand(sample)
			print cmd
			if (not options.test):
				os.system(cmd)

		# finished
		print "finished"
		return 0
	except:
		print "Unexpected error:", sys.exc_info()[0]
		return 1


# do it
if __name__ == '__main__':
	main()
