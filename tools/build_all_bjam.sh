#!/bin/bash

bjam release -j20 $PAC/externals/build/MiniFWLite
bjam release -j20 $PAC/externals/build/SimpleTable
bjam release -j20 $PAC/externals/build/cms2_core
bjam release -j20 $PAC/packages/RootTools
bjam release -j20 $PAC/packages/AnalysisTools
bjam release -j20 $PAC/packages/FGTools
bjam release -j20 $PAC/packages/cms2
bjam release -j20 $PAC/analysis/ss2012
