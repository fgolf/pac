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

# pull from git
echo "git init fakeRate"
git init fakeRate
pushd fakeRate

echo "git remote add origin git@github.com:cmstas/fakeRate.git"
git remote add origin git@github.com:cmstas/fakeRate.git

if [[ "$tag" -eq "master" ]]; then
    echo "git pull https://github.com/cmstas/fakeRate.git master"
    git pull https://github.com/cmstas/fakeRate.git master
else
    echo "git pull https://github.com/cmstas/fakeRate.git tag $tag"
    git pull https://github.com/cmstas/fakeRate.git tag $tag
fi

popd # fakeRate
popd # $dest
