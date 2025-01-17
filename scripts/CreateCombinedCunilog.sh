#!/bin/bash
#************************************************************************************
#
#	File:		Creates the combined/merged unilog source code file.
#	Why:		To make it easier to include cunilog in other projects.
#	OS:			Unix shell
#   Author:		Thomas
#	Created:	2024-11-02
#
#   License:	Public domain.
#
#	History
#	-------
#
#	When		Who				what
#	------------------------------------------------------------------------------------
#	2024-11-02	Thomas			Created.
#
#***********************************************************************************/
clear
echo "*************************************************************************"
echo "Unix/Linux bash script to create the combined cunilog source code files."
echo "*************************************************************************"
echo ""
echo "Press any key to carry out the creation, or press CTRL-C to cancel."
read ans

ext=""
destcombinedpath="../src/c/combined"

cunilog="${destcombinedpath}/cunilog_combined"
src="../src/c"

# The header files.
srch=""
# The code files.
srcc=""

sfiles="./SingleFiles.txt"
while read -r oneline
do
    if [ "${oneline:0:1}" = ";" ]; then
        # The line starts with a semicolon. This is a comment.
        :
    elif [ "$oneline" = "" ]; then
        # The line's empty. We ignore empty lines too.
        :
    elif [ "${oneline:0:1}" = ":" ]; then
        # This is either ":.h" or ":.c". We grab and use it.
        ext="${oneline:1:2}"
    elif [ "${oneline:0:1}" = "/" ]; then
        # A single file starts with a forward slash. This means we have
        #   to prepend our src folder.
        filename="$src$oneline$ext"
        if [ "$ext" = ".h" ]; then
            srch="$srch $filename"
            echo "$filename"
        elif [ "$ext" = ".c" ]; then
            srcc="$srcc $filename"
            echo "$filename"
        fi
    else
        # A single file doesn't start with a forward slash. We expect
        #   this file to be in the current foler.
        filename="$oneline$ext"
        if [ "$ext" = ".h" ]; then
            srch="$srch $filename"
            echo "$filename"
        elif [ "$ext" = ".c" ]; then
            srcc="$srcc $filename"
            echo "$filename"
        fi
    fi
done <"$sfiles"

# Write out the combined files.
cat $srch > $cunilog.h
cat $srcc > $cunilog.c
echo "Done."
