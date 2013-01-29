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
]

# supported signal regions
# ---------------------------------------------------------------------------------- #

incl_signal_regions = [ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, \
					   10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
					   20, 21, 22, 23, 24, 25, 26, 27, 28] 
excl_signal_regions = [ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, \
					   10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
					   20, 21, 22, 23, 24, 25, 26, 27, 28] 

# parse inputs
# ---------------------------------------------------------------------------------- #

parser = OptionParser()

# parameter options
parser.add_option("--nev"       , dest="nev"       , default=-1       , help="The number of events to run (-1 for all)"                 )
parser.add_option("--lumi"      , dest="lumi"      , default=1.0      , help="luminosity in fb^-1"                                      )
parser.add_option("--suffix"    , dest="suffix"    , default="all"    , help="The suffix for the histograms (eps, png, pdf, all)"       )
parser.add_option("--out_name"  , dest="out_name"  , default="test"   , help="name for all the directories associated with these yields")
parser.add_option("--anal_type" , dest="anal_type" , default="high_pt", help="analysis type"                                            )
parser.add_option("--nbtags"    , dest="nbtags"    , default=0        , help="# btags"                                                  )
parser.add_option("--njets"     , dest="njets"     , default=2        , help="# jets"                                                   )
parser.add_option("--l1_min_pt" , dest="l1_min_pt" , default=5.0      , help="minimum pT on leading lepton"                             )
parser.add_option("--l1_max_pt" , dest="l1_max_pt" , default=100000.0 , help="maximum pT on leading lepton"                             )
parser.add_option("--l2_min_pt" , dest="l2_min_pt" , default=5.0      , help="minimum pT on trailing lepton"                            )
parser.add_option("--l2_max_pt" , dest="l2_max_pt" , default=100000.0 , help="maximum pT on trailing lepton"                            )
parser.add_option("--min_ht"    , dest="min_ht"    , default=80.0     , help="minimum HT"                                               )
parser.add_option("--charge"    , dest="charge"    , default=0        , help="charge of leptons (1 for +, -1 for -, 0)"                 )
parser.add_option("--sr"        , dest="sr"        , default=0        , help="signal region"                                            )

# boolean options
parser.add_option("--test"   , action="store_true" , dest="test"   , default=False, help="test script -- print commands but do nothing")
parser.add_option("--excl"   , action="store_true" , dest="excl"   , default=False, help="use exclusive SR"                            )
parser.add_option("--incl"   , action="store_false", dest="excl"   , default=False, help="use incl SR (default)"                       )
parser.add_option("--no_hist", action="store_true" , dest="no_hist", default=False, help="do not create histograms, do everything else")
parser.add_option("--verbose", action="store_true" , dest="verbose", default=False, help="verbose print out"                           )

(options, args) = parser.parse_args()

# make the histograms for a particular sample and signal region
# ---------------------------------------------------------------------------------- #

def make_hist(signal_region, sample):

	# check signal region
	if (options.excl):
		signal_region_type = "exclusive"
		if (signal_region < excl_signal_regions[0] or signal_region > excl_signal_regions[-1]):
			raise Error("signal region %d not supported. exiting" % signal_region)
	else:
		signal_region_type = "inclusive"
		if (signal_region < incl_signal_regions[0] or signal_region > incl_signal_regions[-1]):
			raise Error("signal region %d not supported. exiting" % signal_region)

	# start the command
	cmd = "ss2012_plots.exe"	

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
	#cmd += " --fr_file %s"                        % "data/fake_rates/ssFR_data_standard_16Dec2012.root" 
	cmd += " --fr_file %s"                        % "data/fake_rates/ssFR_data_standard_d0cut.root" 
	cmd += " --charge %d"                         % int(options.charge)
	cmd += " --l1_min_pt %1.3f --l1_max_pt %1.3f" % (float(options.l1_min_pt), float(options.l1_max_pt))
	cmd += " --l2_min_pt %1.3f --l2_max_pt %1.3f" % (float(options.l2_min_pt), float(options.l2_max_pt))
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

	cmd = "root -b -q -l \"macros/PrintYields.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, true); >& %s\" " \
		% (options.out_name, sr_name, options.anal_type, srt_name, int(options.charge), tex_name)
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
		

# "main program" 
# ---------------------------------------------------------------------------------- #

def main():

	#try:
		if (int(options.sr) < 0):
			if (options.excl):
				print "making plots for all exclusive signal regions"
				for sr in excl_signal_regions:
					for sample in samples:	
						make_hist(sr, sample)
					overlay_hist(sr)
					do_append = (sr != excl_signal_regions[0])
					print_yield_table(sr, do_append)
				#print_summary_table()
			else:
				print "making plots for all inclusive signal regions"
				for sr in incl_signal_regions:
					print "making plots for signal region %d..." % sr 
					for sample in samples:	
						make_hist(sr, sample)
					overlay_hist(sr)
					do_append = (sr != incl_signal_regions[0])
					print_yield_table(sr, do_append)
				#print_summary_table()
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
