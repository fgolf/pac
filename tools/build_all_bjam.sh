#!/bin/bash


function run_bjam
{
    local dir=$1
    local option=${2:-}
    pushd $dir
    bjam variant=release address-model=64 architecture=ia64 threading=multi -j20 $option
    if [ $? -eq 0 ]; then
        echo "release build succeeded"
    else
        echo "release build failed"
		exit 1
    fi
    bjam variant=debug address-model=64 architecture=ia64 threading=multi -j20 $option
    if [ $? -eq 0 ]; then
        echo "debug build succeeded"
    else
        echo "debug build failed"
		exit 1
    fi
    popd
}

run_bjam $PAC/externals/build/cms2_core  
run_bjam $PAC/externals/build/cms2_frb   
run_bjam $PAC/externals/build/MiniFWLite 
run_bjam $PAC/externals/build/SimpleTable
run_bjam $PAC/packages/RootTools
run_bjam $PAC/packages/AnalysisTools
run_bjam $PAC/packages/FGTools           
run_bjam $PAC/packages/cms2 
run_bjam $PAC/analysis/ss2012
run_bjam $PAC/analysis/FakeRateStudy2011 
