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

# check out cms2 
# --------------------------------------------------------------- #

echo Checking out cms2
#tag=V05-02-28
tag=HEAD
pushd externals/build/cms2_core
./checkout.sh $tag
pushd
echo

# check out MiniFWLite 
# --------------------------------------------------------------- #

echo Checking out MiniFWLite
pushd externals/build/MiniFWLite
./checkout.sh 
pushd
echo

# check out SimpleTable 
# --------------------------------------------------------------- #

echo Checking out Ian\'s table class
tag=HEAD
pushd externals/build/SimpleTable
./checkout.sh
pushd
echo

echo externals install complete

# build all 
# --------------------------------------------------------------- #

# build the code
#make -j20
bjamr -j20
if [ $? -eq 0 ]; then
    echo build successful
else
    echo build failed
fi

