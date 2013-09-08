#/bin/bash

echo Seting up PAC for the first time...
echo

# check that ROOT is installed
# --------------------------------------------------------------- #

echo Checking that ROOT is installed.
: ${ROOTSYS?"ROOT is not setup -- exiting"}
echo check complete
echo

echo installing the externals...
mkdir -p externals/source/
echo

# check out cms2 CORE
# --------------------------------------------------------------- #

tag=$CMS2CORE_TAG
echo Checking out cms2 with tag $tag
pushd externals/build/cms2_core
./checkout.sh $tag
pushd
echo

# check out cms2 Tools
# (mostly for MiniFWLite)
# --------------------------------------------------------------- #

tag=$CMS2TOOLS_TAG
echo Checking out cms2 with tag $tag
pushd externals/build/cms2_tools
./checkout.sh $tag
pushd
echo

# check out myBabyMaker (for fake rate babies) 
# --------------------------------------------------------------- #

tag=$CMS2FRB_TAG
echo Checking out myBabyMaker with tag $tag
pushd externals/build/cms2_frb
./checkout.sh $tag
pushd
echo
 
# check out SimpleTable 
# --------------------------------------------------------------- #

tag=HEAD
echo Checking out Ian\'s table class with tag $tag
pushd externals/build/SimpleTable
./checkout.sh
pushd
echo

echo externals install complete

# build all 
# --------------------------------------------------------------- #

# build the code
pushd $PAC/tools
./build_all_bjam.sh
if [ $? -eq 0 ]; then
    echo Build successful!
else
    echo Build failed...
fi
popd
