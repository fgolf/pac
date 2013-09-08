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

# pull from git
echo "git init CORE"
git init CORE
pushd CORE

echo "git remote add origin https://github.com/cmstas/CORE.git"
git remote add origin https://github.com/cmstas/CORE.git

echo "git pull https://github.com/cmstas/CORE.git master"
git pull https://github.com/cmstas/CORE.git master

if [ "$tag" != "master" ]; then
    echo "git pull https://github.com/cmstas/CORE.git tag $tag"
    git pull https://github.com/cmstas/CORE.git tag $tag
fi

popd # CORE
popd # $dest
