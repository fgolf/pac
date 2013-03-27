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
export CMS2_CORE_TAG=ss2012_V02-05-08
export CMS2_CORE=$PAC/externals/source/cms2_core/$CMS2_CORE_TAG/CORE

PATH=$project_dir/bin:$PATH
if [ -d "$project_dir/lib" ] ; then
    LD_LIBRARY_PATH=$project_dir/lib:$LD_LIBRARY_PATH
    DYLD_LIBRARY_PATH=$project_dir/lib:$DYLD_LIBRARY_PATH
    PATH=$PATH:$PAC/bin
elif [ ! -z $CMSSW_BASE ] ; then
    LD_LIBRARY_PATH=$project_dir/bin/cmssw/release:$LD_LIBRARY_PATH:$ROOTSYS/lib
    DYLD_LIBRARY_PATH=$project_dir/bin/cmssw/release:$DYLD_LIBRARY_PATH:$ROOTSYS/lib
    LD_LIBRARY_PATH=$project_dir/bin/cmssw/debug:$LD_LIBRARY_PATH
    DYLD_LIBRARY_PATH=$project_dir/bin/cmssw/debug:$DYLD_LIBRARY_PATH
    PATH=$PATH:$PAC/bin/cmssw/release
    PATH=${PATH/\/bin\/release/${PAC}\/bin\/cmssw\/release} # kludge: replace the path with bin/cmssw/release
else
    LD_LIBRARY_PATH=$project_dir/bin/release:$LD_LIBRARY_PATH
    DYLD_LIBRARY_PATH=$project_dir/bin/release:$DYLD_LIBRARY_PATH
    LD_LIBRARY_PATH=$project_dir/bin/debug:$LD_LIBRARY_PATH
    DYLD_LIBRARY_PATH=$project_dir/bin/debug:$DYLD_LIBRARY_PATH
    PATH=$PATH:$PAC/bin/release
    PATH=${PATH/\/bin\/cmssw\/release/${PAC}\/bin\/release} # kludge: replace the old path with bin/release
fi
