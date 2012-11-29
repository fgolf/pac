#!/bin/bash

# set the tag and destination folder
tag=${1:-HEAD}

# checkout CORE
# ------------------------------------------------------------------------------------------ #

path="../../source/cms2_core"
dest=${path}/${tag}
echo checking cout CMS2/NtupleMacros/CORE with tag $tag
echo destination: $dest

mkdir -p $dest
pushd $dest

cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/jetSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/electronSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/electronSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/electronSelectionsParameters.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/electronSelectionsParameters.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/eventSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/eventSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/jetSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/jetSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/mcSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/mcSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/metSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/metSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/MITConversionUtilities.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/MITConversionUtilities.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/muonSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/muonSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/ssSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/ssSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/susySelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/susySelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/trackSelections.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/trackSelections.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/triggerUtils.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/triggerUtils.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/utilities.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/utilities.h
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/mcbtagSFuncert.cc
#cvs co -r $tag -d CORE         UserCode/JRibnik/CMS2/NtupleMacros/CORE/mcbtagSFuncert.h
#cvs co -r $tag -d CORE/jetcorr UserCode/JRibnik/CMS2/NtupleMacros/CORE/jetcorr
#cvs co -r $tag -d CORE/tcmet   UserCode/JRibnik/CMS2/NtupleMacros/CORE/tcmet

popd 
