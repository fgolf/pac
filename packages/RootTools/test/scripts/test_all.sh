#!/bin/bash 

# script to test root_tools in all three runtime environments
# 1.  compiled interactive (ACLiC)
# 2.  fully compiled C++ 
# 3.  purely interactive  (__CINT__)

path=$PAC/packages/RootTools
test_path=$path/test/scripts

# fully compiled test
echo -e "\n\n"
echo "**********************************************"
echo "*               FULLY COMPILE C++            *"
echo "**********************************************"
bjam release $path
if [ $? -eq 0 ]; then
    bjam release $path/test
else
    echo "compile failed"
fi
if [ $? -eq 0 ]; then
    $PAC/bin/release/test_root_tools
else
    echo "compile failed"
fi

# interactive test
echo "**********************************************"
echo "*               INTERACTIVE                  *"
echo "**********************************************"
echo -e "\n\n"
root -b -l -c -q "$test_path/test_root_tools.C"

# interactive compiled test
echo -e "\n\n"
echo "**********************************************"
echo "*            INTERACTIVE COMPILED            *"
echo "**********************************************"
root -b -l -c -q "$test_path/test_root_tools.C++"

