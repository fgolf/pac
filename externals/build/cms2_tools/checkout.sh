#!/bin/bash

# set the tag and destination folder
tag=${1:-master}

# checkout Tools
# ------------------------------------------------------------------------------------------ #

path="../../source/cms2_tools"
dest=${path}
echo checking out CMS2/NtupleMacros/Tools with tag $tag
echo destination: $dest

mkdir -p $dest
pushd $dest

# pull from git
echo "git init Tools"
git init Tools
pushd Tools

echo "git remote add origin https://github.com/cmstas/Tools.git"
git remote add origin https://github.com/cmstas/Tools.git

echo "git pull https://github.com/cmstas/Tools.git master"
git pull https://github.com/cmstas/Tools.git master

if [ "$tag" != "master" ]; then
    echo "git pull https://github.com/cmstas/Tools.git tag $tag"
    git pull https://github.com/cmstas/Tools.git tag $tag
fi

popd # Tools
popd # $dest
