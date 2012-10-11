#!/bin/bash

ss2012_outreach --sample t1tttt_fastsim --output babies_outreach3/t1tttt.root     --nev 500000  --sparms 1 --fit_file plots/outreach/t1tttt_or.root         >& logs/t1tttt_fastsim_outreach.log &
ss2012_outreach --sample glusbottom     --output babies_outreach3/glusbottom.root --nev -1      --sparms 1 --fit_file plots/outreach/glusbottom_or.root     >& logs/glusbottom_outreach.log     &    
#ss2012_outreach --sample glustop        --output babies_outreach3/glustop.root    --nev -1      --sparms 1 --fit_file plots/outreach/glustop_or.root        >& logs/glustop_outreach.log        &       
ss2012_outreach --sample lm9            --output babies_outreach3/lm9.root        --nev -1      --sparms 1 --fit_file plots/outreach/lm9_or.root            >& logs/lm9_outreach.log            &           
#ss2012_outreach --sample sbottomtop     --output babies_outreach3/sbottomtop.root --nev -1      --sparms 1 --fit_file plots/outreach/sbottomtop_or.root     >& logs/sbottomtop_outreach.log     &    

