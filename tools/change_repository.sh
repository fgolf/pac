#!/bin/bash
# Test whether we got an argument for the new CVS Repository value - exit if not
# 	-z <somestring> is a bash conditional experssion that returns true 
# 	if the <somestring> has a zero length
if [ -z "$1" ] || [ -z "$2" ]; then 
  echo "

You must supply the old and new values for CVS Repository
usage: $0 <oldcvsrepositoryvalue> <newcvsrepositoryvalue>

Example: 
	./changerepository.sh /usr/dev/cvsrep /Users/Shared/cvsrep
"
  exit
fi
# Assign Repository values passed on the command line
old_repos=$1
new_repos=$2
# walk the current directory (find . ) and if the path matches */CVS/Repository, 
# replace the old  CVS Repository location with the new. We use % to delimit the
# regular expression as we expect the locations to include / slashes.
find . -path "*/CVS/Repository" | while read f; do
  newRepository=`cat $f | sed -e s%$old_repos%$new_repos%`
  echo $newRepository > $f
done
