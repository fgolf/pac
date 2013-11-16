#!/bin/bash

# set the tag and destination folder
tag=${1:-master}

# checkout CORE
# ------------------------------------------------------------------------------------------ #

path="../../source/cms2_core"
dest=${path}
echo checking out CMS2/NtupleMacros/CORE with tag $tag
echo destination: $dest

mkdir -p $dest
pushd $dest

# clone from git
echo "git clone https://github.com/cmstas/CORE.git"
git clone https://github.com/cmstas/CORE.git
if [ "$tag" != "master" ]; then
    pushd CORE
    git checkout $tag
    popd
fi

popd # $dest
