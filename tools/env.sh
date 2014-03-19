#!/bin/bash

# get the project dir
tools_dir=$(cd -P "$(dirname "${BASH_SOURCE[0]}")" && pwd)
project_dir=$(cd -P $tools_dir/.. && pwd)

# host name of the computer
export HOSTNAME=`hostname`

# setup boost (if its not already setup)
if [ -z $BOOST_CURRENT ]; then
    export BOOST_CURRENT=/home/users/rwkelley/code/boost/1.49.0/
    export BOOST_BUILD_PATH=$BOOST_CURRENT/tools/build/v2
    export PATH=$PATH:$BOOST_CURRENT
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$BOOST_CURRENT/stage/lib
    export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$BOOST_CURRENT/stage/lib
    alias bjamr='bjam variant=release address-model=64 architecture=ia64 threading=multi'
    alias bjamd='bjam variant=debug address-model=64 architecture=ia64 threading=multi'
    alias bjamr32='bjamr address-model=32 architecture=x86'
    alias bjamd32='bjamd address-model=32 architecture=x86'
fi

# set the path and setup shared libraries
export PAC=$project_dir
alias cdpac="cd $PAC"

# set the path to CMS2 CORE 
export CMS2CORE_TAG=ss2012_V03-02-03
export CMS2CORE=$PAC/externals/source/cms2_core/CORE

# set the path to CMS2 CORE 
export CMS2TOOLS_TAG=master
export CMS2TOOLS=$PAC/externals/source/cms2_tools/$CMS2CORE_TAG/

#set the path to CMS2 FRB
export CMS2FRB_TAG=FakeRate19March2014
export CMS2FRB=$PAC/externals/source/cms2_frb/$CMS2FRB_TAG/

# convenience
export AT=$PAC/packages/AnalysisTools
export RT=$PAC/packages/RootTools
export SS=$PAC/analysis/ss2012
alias cdat="cd $AT"
alias cdrt="cd $RT"
alias cdss="cd $SS"

# git locations
export CORE_GIT=https://github.com/cmstas/CORE.git
export FRB_GIT=https://github.com/cmstas/fakeRate.git
export PAC_GIT=https://github.com/kelleyrw/pac.git

PATH=$project_dir/bin:$PATH
if [ ! -z $CMSSW_BASE ] ; then
    LD_LIBRARY_PATH=$project_dir/bin/cmssw/debug:$LD_LIBRARY_PATH
    DYLD_LIBRARY_PATH=$project_dir/bin/cmssw/debug:$DYLD_LIBRARY_PATH
    LD_LIBRARY_PATH=$project_dir/bin/cmssw/release:$LD_LIBRARY_PATH:$ROOTSYS/lib
    DYLD_LIBRARY_PATH=$project_dir/bin/cmssw/release:$DYLD_LIBRARY_PATH:$ROOTSYS/lib
    PATH=$PATH:$PAC/bin/cmssw/release
    PATH=${PATH/\/bin\/release/${PAC}\/bin\/cmssw\/release} # kludge: replace the path with bin/cmssw/release
else
    LD_LIBRARY_PATH=$project_dir/bin/debug:$LD_LIBRARY_PATH
    DYLD_LIBRARY_PATH=$project_dir/bin/debug:$DYLD_LIBRARY_PATH
    LD_LIBRARY_PATH=$project_dir/bin/release:$LD_LIBRARY_PATH
    DYLD_LIBRARY_PATH=$project_dir/bin/release:$DYLD_LIBRARY_PATH
    PATH=$PATH:$PAC/bin/release
    PATH=${PATH/\/bin\/cmssw\/release/${PAC}\/bin\/release} # kludge: replace the old path with bin/release
fi
