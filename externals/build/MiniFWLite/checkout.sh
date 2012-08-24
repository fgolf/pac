#!/bin/bash

# checkout MiniFWLite
# ------------------------------------------------------------------------------------------ #

src_dir="../../source"
dest=MiniFWLite
echo destination: $src_dir/$dest

pushd $src_dir
echo cvs co -d $dest UserCode/JRibnik/CMS2/NtupleMacros/Tools/MiniFWLite 
cvs co -d $dest UserCode/JRibnik/CMS2/NtupleMacros/Tools/MiniFWLite 
pushd $dest
make
popd # $dest
popd # $src_dir
