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
	# "wgstar2e",
	"wgstar2m",
	"wgstar2t",
	"ww_ds",
	# "dy",
	"dyjets",
	"wjets",
	"ttdil",
	"ttotr",
	"ttslb",
	"ttslo",
	"t_schan",
	"t_tchan",
	"t_tw",
	"wh_zh_tth_hww",
	"wh_zh_tth_hzz",
	"wh_zh_tth_htt"
        ]

# supported signal regions
# ---------------------------------------------------------------------------------- #

incl_signal_regions = [0, 1, 2, 3]
excl_signal_regions = [0, 1, 2, 3]

# parse inputs
# ---------------------------------------------------------------------------------- #

parser = OptionParser()

default_fr_file = "data/fake_rates/ssFR_data_ewkcor_17Apr2013.root"
default_fl_file = "data/flip_rates/ssFL_data_standard_02222013.root"
default_signal  = ""

# parameter options
parser.add_option("--nev"       , dest="nev"       , default=-1             , help="The number of events to run (-1 for all)"                 )
parser.add_option("--lumi"      , dest="lumi"      , default=1.0            , help="luminosity in fb^-1"                                      )
parser.add_option("--suffix"    , dest="suffix"    , default="png"          , help="The suffix for the histograms (eps, png, pdf, all)"       )
parser.add_option("--out_name"  , dest="out_name"  , default="test"         , help="name for all the directories associated with these yields")
parser.add_option("--anal_type" , dest="anal_type" , default="ss"           , help="analysis type"                                            )
parser.add_option("--charge"    , dest="charge"    , default=0              , help="charge of leptons (1 for +, -1 for -, 0)"                 )
parser.add_option("--sr"        , dest="sr"        , default=0              , help="signal region"                                            )
parser.add_option("--fr_file"   , dest="fr_file"   , default=default_fr_file, help="fake rate file to use"                                    )
parser.add_option("--fl_file"   , dest="fl_file"   , default=default_fl_file, help="flip rate file to use"                                    )
parser.add_option("--signal"    , dest="signal"    , default=default_signal , help="comma separated list of signal samples"                   )

# boolean options
parser.add_option("--test"            , action="store_true"  , dest="test"            , default=False , help="test script -- print commands but do nothing"    )
parser.add_option("--excl"            , action="store_true"  , dest="excl"            , default=False , help="use exclusive SR"                                )
parser.add_option("--incl"            , action="store_false" , dest="excl"            , default=False , help="use incl SR (default)"                           )
parser.add_option("--no_hist"         , action="store_true"  , dest="no_hist"         , default=False , help="do not create histograms , do everything else"   )
parser.add_option("--do_caption"      , action="store_true"  , dest="do_caption"      , default=False , help="create the caption for the SR above the tabular" )
parser.add_option("--verbose"         , action="store_true"  , dest="verbose"         , default=False , help="verbose print out"                               )
parser.add_option("--mc_only"         , action="store_true"  , dest="mc_only"         , default=False , help="do not run on data"                              )
parser.add_option("--combine_signals" , action="store_true"  , dest="combine_signals" , default=False , help="combine signals"                                 )
parser.add_option("--combine_bkgds"   , action="store_true"  , dest="combine_bkgds"   , default=False , help="combine backgrounds"                             )
parser.add_option("--do_sf"           , action="store_false" , dest="do_sf"           , default=True  , help="apply mc scale factors"                          )
parser.add_option("--print_evt_list"  , action="store_true"  , dest="print_evt_list"  , default=False , help="print evt,ls,run for is_ss events to file"       )
parser.add_option("--norm_hist"       , action="store_true"  , dest="normalize_hists" , default=False , help="normalize histograms to unit area"               )
parser.add_option("--hybrid"          , action="store_true"  , dest="do_hybrid"       , default=False , help="use data-driven bkgd estimates with MC signal"   )
parser.add_option("--categorize_rare" , action="store_true"  , dest="categorize_rare" , default=False , help="group rare SM bkgd into categories"              )

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
        if (options.anal_type == "ss"):
                cmd = "ewkino2012_ss_plots"
        else:
                cmd = ""

	# luminosity
	cmd += " --lumi %1.3f" % float(options.lumi)
	
        # let's deal with signal samples with sparm parameters
        sample_list = sample.split('-');        
        sample_with_underscores = sample.replace('-','_')
        if (len(sample_list) == 1):
                is_signal = False
        else:
                is_signal = True

	# the signal region
	cmd += " --sr %d" % signal_region

	# the input sample
        if (is_signal):
                cmd += " --sample %s" % sample_list[0]
        else:
                cmd += " --sample %s" % sample

	# signal region stem 
	signal_region_stem = "sr%d" % signal_region

	# root file name
	if (int(options.charge) == 1):
                if (is_signal):
                        root_file_name = "%s_pp.root" % sample_with_underscores
                else:
                        root_file_name = "%s_pp.root" % sample
	elif (int(options.charge) == -1):
                if (is_signal):
                        root_file_name = "%s_mm.root" % sample_with_underscores
                else:
                        root_file_name = "%s_mm.root" % sample
	else:
                if (is_signal):
                        root_file_name = "%s.root" % sample_with_underscores
                else:
                        root_file_name = "%s.root" % sample

	# output filename
        if (is_signal):
                cmd += " --output plots/%s/%s/%s/%s/%s" % (options.out_name, options.anal_type, signal_region_type, signal_region_stem, root_file_name)
        else:
                cmd += " --output plots/%s/%s/%s/%s/%s" % (options.out_name, options.anal_type, signal_region_type, signal_region_stem, root_file_name)
	
	# options
	cmd += " --nev %s"                            % int(options.nev)
	cmd += " --fr_file %s"                        % str(options.fr_file)
	cmd += " --fl_file %s"                        % str(options.fl_file)
	cmd += " --charge %d"                         % int(options.charge)
	cmd += " --anal_type %s"                      % options.anal_type
        cmd += " --do_sf %d"                          % int(options.do_sf)

        if (options.print_evt_list):
                event_list_file = "logs/%s/%s_event_list.log" % (signal_region_stem, sample)
                cmd += " --evt_list %s" % str(event_list_file)

        if (is_signal):
                if (len(sample_list) >= 2):
                        cmd += " --sparm0 %f" % float(sample_list[1])
                if (len(sample_list) >= 3):
                        cmd += " --sparm1 %f" % float(sample_list[2])

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

        if (options.mc_only):
                bkgds = "all"
                signal_with_underscores = options.signal.replace('-','_')
                cmd = "root -b -q -l \"macros/OverlaySSPlotsMC.C+ (%1.3f,\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, %d, %d, \\\"%s\\\", %d, \\\"%s\\\")\" 2> /dev/null" \
                    % (float(options.lumi), str(options.out_name), str(sr_name), str(options.anal_type), str(signal_with_underscores), str(bkgds), bool(options.combine_signals), bool(options.combine_bkgds), \
                               bool(options.normalize_hists), str(srt_name), int(options.charge), str(options.suffix))        
        elif (options.do_hybrid):
                signal_with_underscores = options.signal.replace('-','_')
                cmd = "root -b -q -l \"macros/OverlaySSPlotsHybrid.C+ (%1.3f,\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, %d, %d, %d, \\\"%s\\\", %d, \\\"%s\\\")\" 2> /dev/null" \
                    % (float(options.lumi), str(options.out_name), str(sr_name), str(options.anal_type), str(signal_with_underscores), bool(options.combine_signals), bool(options.categorize_rare), bool(options.combine_bkgds), \
                               bool(options.normalize_hists), str(srt_name), int(options.charge), str(options.suffix))
        else:
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

        if (options.mc_only):
                bkgds = "all"
                signal_with_underscores = options.signal.replace('-','_')
                cmd = "root -b -q -l \"macros/PrintYieldsMC.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, %d, \\\"%s\\\", %d, false); %s %s\" " \
                    % (options.out_name, sr_name, options.anal_type, str(signal_with_underscores), str(bkgds), bool(options.combine_signals), bool(options.combine_bkgds), srt_name, int(options.charge), operator, text_name)
        elif (options.do_hybrid):
                signal_with_underscores = options.signal.replace('-','_')
                cmd = "root -b -q -l \"macros/PrintYieldsHybrid.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, false); %s %s\" " \
                    % (options.out_name, sr_name, options.anal_type, str(signal_with_underscores), srt_name, int(options.charge), operator, text_name)
        else:
                cmd = "root -b -q -l \"macros/PrintYields.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, false, %d); %s %s\" " \
                    % (options.out_name, sr_name, options.anal_type, srt_name, int(options.charge), int (options.do_caption), operator, text_name)

	if (options.verbose):
		print cmd
	if (not options.test):
		os.system(cmd)

	# tex file
	tex_name  = "%s/sr%d.tex" % (table_path, signal_region)

        if (options.mc_only):
                bkgds = "all"
                signal_with_underscores = options.signal.replace('-','_')                
                cmd = "root -b -q -l \"macros/PrintYieldsMC.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, %d, \\\"%s\\\", %d, true, %d); >& %s\" " \
                    % (options.out_name, sr_name, options.anal_type, str(signal_with_underscores), str(bkgds), bool(options.combine_signals), bool(options.combine_bkgds), srt_name, int(options.charge), int(options.do_caption), tex_name)
        elif (options.do_hybrid):
                signal_with_underscores = options.signal.replace('-','_')
                cmd = "root -b -q -l \"macros/PrintYieldsHybrid.C+ (\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\",\\\"%s\\\", %d, true, %d); >& %s\" " \
                    % (options.out_name, sr_name, options.anal_type, str(signal_with_underscores), srt_name, int(options.charge), int(options.do_caption), tex_name)
        else:
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
		

# "main program" 
# ---------------------------------------------------------------------------------- #

def main():

        # let's append signals to the list of samples to process
        if (len(options.signal) > 0):
                signal_list = options.signal.split(',')
                for item in signal_list:
                        samples.append(item)

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
                                # print_summary_table()
                else:
                        print "making plots for all inclusive signal regions"
                        for sr in incl_signal_regions:
                                for sample in samples:	
                                        make_hist(sr, sample)
                                overlay_hist(sr)
                                do_append = (sr != incl_signal_regions[0])
                                print_yield_table(sr, do_append)
                                # print_summary_table()
        else:	
                sr = int(options.sr)
                print "making plots for signal region %d..." % sr
                for sample in samples:                        
                        make_hist(sr, sample)
                overlay_hist(sr)
                print_yield_table(sr, False)
		
        print "finished"
	#except:
	#	print "Unexpected error:", sys.exc_info()[0]
	#	return 1


# do it
if __name__ == '__main__':
	main()
