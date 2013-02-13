#!/bin/bash

# set the tag and destination folder
tag=${1:-HEAD}

# checkout CORE
# ------------------------------------------------------------------------------------------ #

path="../../source/cms2_frb"
dest=${path}
echo checking cout CMS2/NtupleMacros/fakeRate/myBabyMaker.{h,cc} with tag $tag
echo destination: $dest

mkdir -p $dest
pushd $dest

cvs co -r $tag -d ${tag} UserCode/JRibnik/CMS2/NtupleMacros/fakeRate/myBabyMaker.cc
cvs co -r $tag -d ${tag} UserCode/JRibnik/CMS2/NtupleMacros/fakeRate/myBabyMaker.h
cvs co -r $tag -d ${tag} UserCode/JRibnik/CMS2/NtupleMacros/fakeRate/ChangeLog

popd 
