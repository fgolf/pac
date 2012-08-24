#!/bin/bash

# checkout Ian's SimpleTable class
# ------------------------------------------------------------------------------------------ #

src_dir="../../source"
dest=SimpleTable
echo destination: $src_dir/$dest

pushd $src_dir
echo cvs co -d $dest UserCode/IMacneill/UCSDTools/SimpleTable 
cvs co -d $dest UserCode/IMacneill/UCSDTools/SimpleTable 
pushd $dest
make
popd # $dest
popd # $src_dir
