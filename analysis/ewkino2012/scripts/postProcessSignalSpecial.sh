#!/bin/bash

##
## 130
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino130*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2/$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.31 --kfactor 1 --filter_eff 1 --num_events 162205
done

##
## 150
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino150*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2//$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.18 --kfactor 1 --filter_eff 1 --num_events 171612
done

##
## 175
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino175*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2//$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.10 --kfactor 1 --filter_eff 1 --num_events 162232
done

##
## 200
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino200*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2//$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.06 --kfactor 1 --filter_eff 1 --num_events 80344
done

##
## 250
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino250*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2//$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.024 --kfactor 1 --filter_eff 1 --num_events 76462
done

##
## 300
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino300*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2//$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.011 --kfactor 1 --filter_eff 1 --num_events 74118
done

##
## 350
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino350*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2//$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.006 --kfactor 1 --filter_eff 1 --num_events 28613
done

##
## 400
##
for f in `ls /nfs-7/userdata/olivito/ewkinoHiggs_WHWW/*chargino400*.root` ; do    
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v2//$outfile"
    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec 0.003 --kfactor 1 --filter_eff 1 --num_events 35048
done

##
## 1D private, all
##
for f in `ls /hadoop/cms/store/user/fgolf/CMS2_V05-03-31/WinoNLSP_WinoNLSP/*.root` ; do
    prepath=${f%/*}
    outfile=${f##*/}
    outfile=${outfile/.root/_out.root}
    outfile="/nfs-7/userdata/fgolf/susy_higgs/sswh_v3/$outfile"
    echo    $PAC/bin/release/add_cms2_branches_signal_special --input $f --output $outfile --xsec -999999.0 --num_events -999999 --kfactor 1.0 --filter_eff 1.0
done