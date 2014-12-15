import FWCore.ParameterSet.Config as cms
import os
import sys

## path the analysis (THIS SHOULD NOT CHANGE)
analysis_path = os.getenv("PAC") + "/analysis/python_cfg_example"
sys.path.append(analysis_path + "/pset")

## process to parse (THIS SHOULD NOT CHANGE)
process = cms.PSet()

## ------------------------------------------------------------- #
## Parameters for the selection, plot making, and fitting 
## ------------------------------------------------------------- #

process.pset = cms.PSet(

	## path to the analysis
	analysis_path = cms.string(analysis_path),

	## the sample name (from Sample.h/cc) 
	sample_name = cms.string("sample"),
	
	## integrated luminosity 
	lumi = cms.double(19.5),
	
	## output label to give it a unique name
	output_label = cms.string("v0"),

	## search regions
	search_regions = cms.vuint32(0, 1, 2, 3, 4, 5, 6),

	## select a specific sparm parameter
	mass_stop = cms.double(-1),
	mass_lsp  = cms.double(-1),
	
	## max number of events to run on
	max_events = cms.int64(-1),
	
	## verbosity (for trouble shooting)
	verbose = cms.bool(False),
)

