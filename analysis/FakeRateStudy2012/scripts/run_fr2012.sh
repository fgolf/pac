#!/bin/bash

nev=${1:--1}
tag=_orig

#fr2012_plots --sample qcd   --channel mu --root_file_name plots/qcd/qcd_mu$tag.root     --nev $nev
#fr2012_plots --sample qcd   --channel el --root_file_name plots/qcd/qcd_el$tag.root     --nev $nev
#hadd -f plots/qcd/qcd$tag.root plots/qcd/qcd_mu$tag.root plots/qcd/qcd_el$tag.root

#fr2012_plots --sample ttbar --channel mu --root_file_name plots/ttbar/ttbar_mu$tag.root --nev $nev
#fr2012_plots --sample ttbar --channel el --root_file_name plots/ttbar/ttbar_el$tag.root --nev $nev
#hadd -f plots/ttbar/ttbar$tag.root plots/ttbar/ttbar_mu$tag.root plots/ttbar/ttbar_el$tag.root

#fr2012_plots --sample dy    --root_file_name plots/dy/dy$tag.root       --nev $nev >& logs/dy12.log &
#fr2012_plots --sample wjets --root_file_name plots/wjets/wjets$tag.root --nev $nev >& logs/wjets12.log &
#fr2012_plots --sample data  --nev $nev --root_file_name plots/data/data_no_run_list.root >& logs/data12_no_run_list.log &
fr2012_plots --sample data --channel mu --root_file_name plots/data/data_mu$tag.root --nev $nev --run_list ../ss2012/json/final_19p47fb_cms2.txt >& logs/data_mu.log &
fr2012_plots --sample data --channel el --root_file_name plots/data/data_el$tag.root --nev $nev --run_list ../ss2012/json/final_19p47fb_cms2.txt >& logs/data_el.log &

#tail -f logs/data12.log
