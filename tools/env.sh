#!/bin/bash

# get the project dir
tools_dir=$(cd -P "$(dirname "${BASH_SOURCE[0]}")" && pwd)
project_dir=$(cd -P $tools_dir/.. && pwd)

# setup boost (if its not already setup)
if [ -z $BOOST_CURRENT ]; then
    #export BOOST_CURRENT=/home/users/rwkelley/code/boost/1.49.0/
    export BOOST_CURRENT=/home/users/rwkelley/code/boost/1.51.0/
    export BOOST_BUILD_BATH=$BOOST_CURRENT/tools/build/v2
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
PATH=$project_dir/bin:$PATH
LD_LIBRARY_PATH=$project_dir/lib:$LD_LIBRARY_PATH
DYLD_LIBRARY_PATH=$project_dir/lib:$DYLD_LIBRARY_PATH

