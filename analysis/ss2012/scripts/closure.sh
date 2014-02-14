
#
#type=normal
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c"
#
#type=abs
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 1
#
#type=onlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 2
#
#type=absonlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 3
#
#
#echo "use 20 GeV FR"
#type=normal
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}20.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr20c" --mufr "h_mufr20c"
#
#type=abs
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}20.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr20c" --mufr "h_mufr20c" --FR_opt 1
#
#type=onlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}20.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr20c" --mufr "h_mufr20c" --FR_opt 2
#
#type=absonlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}20.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr20c" --mufr "h_mufr20c" --FR_opt 3
#
#echo "use 60 GeV FR"
#type=normal
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}60.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr60c" --mufr "h_mufr60c"
#
#type=abs
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}60.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr60c" --mufr "h_mufr60c" --FR_opt 1
#
#type=onlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}60.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr60c" --mufr "h_mufr60c" --FR_opt 2
#
#type=absonlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}60.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr60c" --mufr "h_mufr60c" --FR_opt 3
#

#echo "Signal Region 10"
#type=normal
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 10 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c"
#
#type=abs
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 10 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 1
#
#type=onlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 10 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 2
#
#type=absonlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 10 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 3
#
#echo "Signal Region 20"
#type=normal
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 20 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c"
#
#type=abs
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 20 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 1
#
#type=onlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 20 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 2
#
#type=absonlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test8Jan14${type}.root --sr 20 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 3
#


# Trying Wjets, but there isn't enough statistics!

#type=normal
#ss2012_closure_test --sample wjets --output output/closure_test8Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --fr_file "plots/fake_rates/7Jan2014${type}/ssFR_qcd_standard_7Jan2014${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c"

# January 23

#type=
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c"
#type=absonlyiso
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 2
#type=absonlyisoFOpt
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 4
#echo "Use 20 GeV FR"
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr20c" --mufr "h_mufr20c" --FR_opt 4
#echo "Use 60 GeV FR"
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr60c" --mufr "h_mufr60c" --FR_opt 4
#echo "SR10"
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 10 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 4
#echo "SR20"
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 20 --excl 1 --anal_type high_pt --input "babies/hpt/ttjets_powheg*.root,babies/hpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 4
#
#echo "Use low pT MC when using option 4"
#ss2012_closure_test --sample ttjets --output output/closure_test23Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/23Jan2014B${type}/ssFR_qcd_standard_23Jan2014B${type}.root" --elfr "h_mufr40c" --mufr "h_mufr40c" --FR_opt 4
#

# January 31

#31Jan14: new binning
#30Jan14: old binning
 

type=onlyisoFOpt
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr40c" --mufr "h_mufr40c" --FR_opt 4
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr20c" --mufr "h_mufr20c" --FR_opt 4
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr60c" --mufr "h_mufr60c" --FR_opt 4
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 10 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr40c" --mufr "h_mufr40c" --FR_opt 4
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 20 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr40c" --mufr "h_mufr40c" --FR_opt 4
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr40c" --mufr "h_mufr40c" --FR_opt 4 --ht 200
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr40c" --mufr "h_mufr40c" --FR_opt 4 --ht 200 --met 50
ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root" --elfr "h_elfr40c" --mufr "h_mufr40c" --FR_opt 4 --ht 400 --met 50


# Use FR made with ALL the Electron QCD MC, even the low stats files.
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr40c" --mufr "h_elfr40c" --FR_opt 4
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr20c" --mufr "h_elfr40c" --FR_opt 4
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr60c" --mufr "h_elfr40c" --FR_opt 4
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 10 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr40c" --mufr "h_elfr40c" --FR_opt 4
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 20 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr40c" --mufr "h_elfr40c" --FR_opt 4
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr40c" --mufr "h_elfr40c" --FR_opt 4 --ht 200
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr40c" --mufr "h_elfr40c" --FR_opt 4 --ht 200 --met 50
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root" --elfr "h_elfr40c" --mufr "h_elfr40c" --FR_opt 4 --ht 400 --met 50
#ss2012_closure_test --sample wjets  --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "/nfs-7/userdata/gzevi/babies/ss2012/V03-02-02/lpt/wjets_large.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBinsFO4/testQCDEleAllSamplesFix1530OldBinsFO4.root"  --elfr "h_elfr40c" --mufr "h_elfr40c" --FR_opt 4



#ss2012_closure_test --sample wjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "/nfs-7/userdata/gzevi/babies/ss2012/V03-02-02/hpt/wjets_large.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBins/testQCDEleAllSamplesFix1530OldBins.root" --elfr "h_elfr40c" --mufr "h_elfr40c"
#ss2012_closure_test --sample ttjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "babies/lpt/ttjets_powheg*.root,babies/lpt/ttslq.root" --fr_file "plots/fake_rates/testQCDEleAllSamplesFix1530OldBins/testQCDEleAllSamplesFix1530OldBins.root" --elfr "h_elfr40c" --mufr "h_elfr40c"


#ss2012_closure_test --sample wjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "/nfs-7/userdata/gzevi/babies/ss2012/V03-02-02/lpt/wjets_large.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root"  --FR_opt 4
#ss2012_closure_test --sample wjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "/nfs-7/userdata/gzevi/babies/ss2012/V03-02-02/lpt/wjets_large.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root"  --FR_opt 4 --ht 200
#ss2012_closure_test --sample wjets --output output/closure_test30Jan14${type}.root --sr 0 --excl 1 --anal_type high_pt --input "/nfs-7/userdata/gzevi/babies/ss2012/V03-02-02/lpt/wjets_large.root" --fr_file "plots/fake_rates/30Jan2014${type}/ssFR_qcd_standard_30Jan2014${type}.root"  --FR_opt 4 --ht 200 --met 50