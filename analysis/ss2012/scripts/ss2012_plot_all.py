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
	"ww",
	"wz",
	"zz",
	"ttg",
	"ttw",
	"ttz",
	"tbz",
	"ttww",
	"wwg",
	"www",
	"wwz",
	"wzz",
	"zzz",
	"wmwmqq",
	"wpwpqq",
	"wgstar2e",
	"wgstar2m",
	"wgstar2t",
	"ww_ds",
	"dy",
	"wjets",
	"ttjets",
	"ttdil",
	"ttotr",
	"ttslb",
	"ttslo",
	"t_schan",
	"t_tchan",
	"t_tw",
	"wh_zh_tth_hww",
	"wh_zh_tth_hzz",
	"wh_zh_tth_htt",
]

# supported signal regions
# ---------------------------------------------------------------------------------- #

incl_signal_regions = [ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, \
					   10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
					   20, 21, 22, 23, 24, 25, 26, 27, 28, 29, \
					   30, 31, 32, 33, 34, 35] 
excl_signal_regions = [ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, \
					   10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
					   20, 21, 22, 23, 24, 25, 26, 27, 28, 29, \
					   30, 31, 32, 33, 34, 35] 

# parse inputs
# ---------------------------------------------------------------------------------- #

parser = OptionParser()

default_fr_file = "data/fake_rates/ssFR_data_ewkcor_17Apr2013.root"
default_fl_file = "data/flip_rates/ssFL_data_standard_02222013.root"

# parameter options
parser.add_option("--nev"       , dest="nev"       , default=-1             , help="The number of events to run (-1 for all)"                 )
parser.add_option("--lumi"      , dest="lumi"      , default=1.0            , help="luminosity in fb^-1"                                      )
parser.add_option("--suffix"    , dest="suffix"    , default="all"          , help="The suffix for the histograms (eps, png, pdf, all)"       )
parser.add_option("--out_name"  , dest="out_name"  , default="test"         , help="name for all the directories associated with these yields")
parser.add_option("--anal_type" , dest="anal_type" , default="high_pt"      , help="analysis type"                                            )
parser.add_option("--nbtags"    , dest="nbtags"    , default=0              , help="# btags"                                                  )
parser.add_option("--njets"     , dest="njets"     , default=2              , help="# jets"                                                   )
parser.add_option("--min_ht"    , dest="min_ht"    , default=80.0           , help="minimum HT"                                               )
parser.add_option("--charge"    , dest="charge"    , default=0              , help="charge of leptons (1 for +, -1 for -, 0)"                 )
parser.add_option("--sr"        , dest="sr"        , default=0              , help="signal region"                                            )
parser.add_option("--fr_file"   , dest="fr_file"   , default=default_fr_file, help="fake rate file to use"                                    )
parser.add_option("--fl_file"   , dest="fl_file"   , default=default_fl_file, help="flip rate file to use"                                    )

# boolean options
parser.add_option("--test"       , action="store_true"  , dest="test"       , default=False , help="test script -- print commands but do nothing"   )
parser.add_option("--excl"       , action="store_true"  , dest="excl"       , default=False , help="use exclusive SR"                               )
parser.add_option("--incl"       , action="store_false" , dest="excl"       , default=False , help="use incl SR (default)"                          )
parser.add_option("--no_hist"    , action="store_true"  , dest="no_hist"    , default=False , help="do not create histograms, do everything else"   )
parser.add_option("--do_caption" , action="store_true"  , dest="do_caption" , default=False , help="create the caption for the SR above the tabular")
parser.add_option("--verbose"    , action="store_true"  , dest="verbose"    , default=False , help="verbose print out"                              )

(options, args) = parser.parse_args()


if (options.excl):
	signal_region_type = "exclusive"
else:
	signal_region_type = "inclusive"

# make the histograms for a particular sample and signal region
# ---------------------------------------------------------------------------------- #

def make_hist(signal_region, sample):

	# check signal region
	if (options.excl):
		#signal_region_type = "exclusive"
		if (signal_region < excl_signal_regions[0] or signal_region > excl_signal_regions[-1]):
			raise Error("signal region %d not supported. exiting" % signal_region)
	else:
		#signal_region_type = "inclusive"
		if (signal_region < incl_signal_regions[0] or signal_region > incl_signal_regions[-1]):
			raise Error("signal region %d not supported. exiting" % signal_region)

	# start the command
	cmd = "ss2012_plots"	

	# luminosity
	cmd += " --lumi %1.3f" % float(options.lumi)
	
	# the signal region
	cmd += " --sr %d" % signal_region

	# the input sample
	cmd += " --sample %s" % sample

	# signal region stem 
	signal_region_stem = "sr%d" % signal_region

	# root file name
	if (int(options.charge) == 1):
		root_file_name = "%s_pp.root" % sample
	elif (int(options.charge) == -1):
		root_file_name = "%s_mm.root" % sample
	else:	
		root_file_name = "%s.root" % sample
		
	# output filename
	cmd += " --output plots/%s/%s/%s/%s/%s" % (options.out_name, options.anal_type, signal_region_type, signal_region_stem, root_file_name)
	
	# options
	cmd += " --nev %s"                            % int(options.nev)
	cmd += " --nbtags %s"                         % int(options.nbtags)
	cmd += " --njets %s"                          % int(options.njets)
	cmd += " --fr_file %s"                        % str(options.fr_file)
	cmd += " --fl_file %s"                        % str(options.fl_file)
	cmd += " --charge %d"                         % int(options.charge)
	cmd += " --ht %1.3f"                          % float(options.min_ht)
	cmd += " --anal_type %s"                      % options.anal_type 
	if (options.excl):
		cmd += " --excl 1"
	else:
		cmd += " --excl 0"

	# logname
	if (int(options.charge) == 1):
		log_file_name = "%s_pp.log" % sample
	elif (int(options.charge) == -1):
		log_file_name = "%s_mm.log" % sampl#e
	else:	
		log_file_name = "%s.log" % sample
		if (not options.verbose):
			cmd += " > logs/%s" % log_file_name

	if (not options.no_hist):
		if (options.verbose):
			print "making plots for %s in signal region %d..." % (sample, signal_region)
			print cmd
		if (not options.test):
			os.system(cmd)

	return	

# make the histograms for a particular sample and signal region
# ---------------------------------------------------------------------------------- #

def overlay_hist(signal_region):
	print "overlaying plots for signal region %d" % signal_region
	sr_name = "sr%d" % signal_region
	if (options.excl):
		srt_name = "exclusive"
	else:
		srt_name = "inclusive"
	cmd = "root -b -q -l \"macros/OverlaySSPlots.C+ (%1.3f,\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, \\\"%s\\\")\" 2> /dev/null" \
		% (float(options.lumi), str(options.out_name), str(sr_name), str(options.anal_type), str(srt_name), int(options.charge), str(options.suffix))
	if (options.verbose):
		print cmd
	if (not options.test):
		os.system(cmd)

# make the yield table particular sample and signal region
# ---------------------------------------------------------------------------------- #

def print_yield_table(signal_region, do_append):
	print "printing yield tables for signal region %d" % signal_region

	sr_name = "sr%d" % signal_region
	if (options.excl):
		srt_name = "exclusive"
	else:
		srt_name = "inclusive"

	# table directory
	table_path = "tables/%s/%s/%s" % (options.out_name, options.anal_type, srt_name) 
	if not os.path.isdir(table_path):
		print "%s does not exist -- creating" % table_path
   		if (not options.test):
			os.makedirs(table_path)

	if (do_append):
		operator = ">>"	
	else:
		operator = ">"	

	# text file
	text_name  = "%s/sr%d.txt" % (table_path, signal_region)

	cmd = "root -b -q -l \"macros/PrintYields.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, false); %s %s\" " \
		% (options.out_name, sr_name, options.anal_type, srt_name, int(options.charge), operator, text_name)
	if (options.verbose):
		print cmd
	if (not options.test):
		os.system(cmd)

	# tex file
	tex_name  = "%s/sr%d.tex" % (table_path, signal_region)

	cmd = "root -b -q -l \"macros/PrintYields.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, true, %d); >& %s\" " \
		% (options.out_name, sr_name, options.anal_type, srt_name, int(options.charge), int(options.do_caption), tex_name)
	if (options.verbose):
		print cmd
	if (not options.test):
		os.system(cmd)
		
# make the summary table (printed all the signal region) 
# (inclusive only for now)
# ---------------------------------------------------------------------------------- #

def print_summary_table():
	print "printing summary tables"

	# table directory
	table_path = "tables/%s" % options.out_name 
	if not os.path.isdir(table_path):
		print "%s does not exist -- creating" % table_path
   		if (not options.test):
			os.makedirs(table_path)

	# text file
	text_name  = "%s/yields_summary_%s.txt" % (table_path, options.out_name)
	cmd = "root -b -q -l \"macros/PrintSummaryYieldsWrapper.C (\\\"%s\\\", %d, 0); > %s\" " % (options.out_name, int(options.charge), text_name)
	if (options.verbose):
		print cmd
	if (not options.test):
		os.system(cmd)
		os.system("cat %s" % text_name)

	# tex file
	tex_name  = "%s/yields_summary_%s.tex" % (table_path, options.out_name)
	cmd = "root -b -q -l \"macros/PrintSummaryYieldsWrapper.C (\\\"%s\\\", %d, 1); > %s\" " % (options.out_name, int(options.charge), tex_name)
	if (options.verbose):
		print cmd
	if (not options.test):
		os.system(cmd)
		
# print a very simple yield table with format:
# n_search_region oberved_yield total_predicted_yield total_predicted_yield_uncertainty fake_yields fake_yields_uncertainty rare_yields rare_yields_uncertainty chargeflip_yields chargeflip_yields_uncertainty     
# ---------------------------------------------------------------------------------- #

def print_yield_and_predictions():
	print "printing yield and prediction tables"

	# table directory
	table_path = "tables/%s" % options.out_name 
	if not os.path.isdir(table_path):
		print "%s does not exist -- creating" % table_path
   		if (not options.test):
			os.makedirs(table_path)

	# text file
	text_name  = "%s/yields_and_pred_%s_%s_%s.txt" % (table_path, options.anal_type, signal_region_type, options.out_name)
	cmd = "root -b -q -l \"macros/PrintYieldAndPredictionsWrapper.C (\\\"%s\\\", \\\"%s\\\", \\\"%s\\\", \\\"%s\\\");\" " % (options.out_name, options.anal_type, signal_region_type, text_name)
	if (options.verbose):
		print cmd
	if (not options.test):
		os.system(cmd)
		os.system("cat %s" % text_name)


# "main program" 
# ---------------------------------------------------------------------------------- #

def main():

	#try:
		if (int(options.sr) < 0):
			if (options.excl):
				print "making plots for all exclusive signal regions"
				for sr in excl_signal_regions:
					if (sr <= 28 or (sr > 28 and options.anal_type == "high_pt")):
						for sample in samples:	
					 		make_hist(sr, sample)
						overlay_hist(sr)
						do_append = (sr != excl_signal_regions[0])
						print_yield_table(sr, do_append)
				#print_summary_table()
				print_yield_and_predictions()
			else:
				print "making plots for all inclusive signal regions"
				for sr in incl_signal_regions:
					print "making plots for signal region %d..." % sr 
					if (sr <= 28 or (sr > 28 and options.anal_type == "high_pt")):
						for sample in samples:	
					 		make_hist(sr, sample)
						overlay_hist(sr)
						do_append = (sr != incl_signal_regions[0])
						print_yield_table(sr, do_append)
				#print_summary_table()
				print_yield_and_predictions()
		else:	
			sr = int(options.sr)
			print "making plots for signal region %d..." % sr
			# make the plots for all the samples
			for sample in samples:	
				make_hist(sr, sample)
			overlay_hist(sr)
			print_yield_table(sr, False)
		
		# finished
		print "finished"
	#except:
	#	print "Unexpected error:", sys.exc_info()[0]
	#	return 1


# do it
if __name__ == '__main__':
	main()
