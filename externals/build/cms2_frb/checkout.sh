#!/bin/bash

# set the tag and destination folder
tag=${1:-master}

# checkout fakeRate
# ------------------------------------------------------------------------------------------ #

path="../../source/cms2_frb"
dest=${path}
echo checking cout CMS2/NtupleMacros/fakeRate/myBabyMaker.{h,cc} with tag $tag
echo destination: ${dest}

mkdir -p $dest
pushd $dest

# clone from git
echo "git clone https://github.com/cmstas/fakeRate.git"
git clone https://github.com/cmstas/fakeRate.git
if [ "$tag" != "master" ]; then
    pushd fakeRate
    git checkout $tag
    popd
fi
popd # $dest
