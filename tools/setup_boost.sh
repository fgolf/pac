#!/bin/bash
install_path=${1:-${HOME}/code}

echo '********************************************************************'
echo '*                         BOOST Setup                              *'
echo '********************************************************************'
boost_version=1_49_0
boost_version_local=`echo ${boost_version} | sed s/_/\./g`
boost_source=http://svn.boost.org/svn/boost/tags/release/Boost_${boost_version} 
boost_dest=${install_path}/boost/${boost_version_local}
echo installing boost $boost_version_local to $boost_dest
if [ -e $boost_dest ]; then
    echo BOOST $boost_version already exists!!  Skipping!
else
    if [ ! -d ${install_path}/boost ]; then
        echo creating ${install_path}/boost
        mkdir -p ${install_path}/boost
    fi
    svn co $boost_source $boost_dest 
    pushd $boost_dest
    ./bootstrap.sh
    ./b2 -j 10
    popd
fi
