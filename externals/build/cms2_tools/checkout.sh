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

# clone from git
echo "git clone https://github.com/cmstas/Tools.git"
git clone https://github.com/cmstas/Tools.git
if [ "$tag" != "master" ]; then
    pushd Tools
    git checkout $tag
    popd
fi

popd # $dest
