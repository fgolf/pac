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

option=$1
run_bjam $PAC/packages/cms2                $option
run_bjam $PAC/externals/build/cms2_core    $option
run_bjam $PAC/externals/build/cms2_frb     $option
run_bjam $PAC/externals/build/MiniFWLite   $option
run_bjam $PAC/externals/build/SimpleTable  $option
run_bjam $PAC/packages/RootTools           $option
run_bjam $PAC/packages/AnalysisTools       $option
run_bjam $PAC/packages/FGTools             $option
run_bjam $PAC/analysis/ss2012              $option
run_bjam $PAC/analysis/ewkino2012          $option
# run_bjam $PAC/analysis/FakeRateStudy2011   $option
run_bjam $PAC/analysis/FakeRateBabyMaker   $option
run_bjam $PAC/analysis/DrellYan            $option

echo ""
echo -e ########################################
echo           Build Successful
echo -e ##########################################
