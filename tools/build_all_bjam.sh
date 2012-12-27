#!/bin/bash

function run_bjam
{
    local dir=$1
    local option=${2:-}
    pushd $dir
    bjam release -j20 $option
    if [ $? -eq 0 ]; then
        echo "release build succeded"
    else
        echo "release build failed"
    fi
    bjam debug -j20 $option
    if [ $? -eq 0 ]; then
        echo "debug build succeded"
    else
        echo "debug build failed"
    fi
    popd
}

run_bjam $PAC/externals/build/MiniFWLite 
run_bjam $PAC/externals/build/SimpleTable -a
run_bjam $PAC/externals/build/cms2_core  
run_bjam $PAC/externals/build/cms2_frb   
run_bjam $PAC/packages/RootTools -a        
run_bjam $PAC/packages/AnalysisTools -a
run_bjam $PAC/packages/FGTools           
run_bjam $PAC/packages/cms2 
run_bjam $PAC/analysis/ss2012 -a           
run_bjam $PAC/analysis/FakeRateStudy2011 
