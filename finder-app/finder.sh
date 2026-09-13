#!/bin/sh
# finder.sh - count files in a directory tree and lines matching a search string
# Usage: finder.sh <filesdir> <searchstr>

if [ $# -ne 2 ]; then
    echo "Error: two arguments required"
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d "$filesdir" ]; then
    echo "Error: '$filesdir' is not a directory"
    exit 1
fi

numfiles=$(find "$filesdir" -type f | wc -l | tr -d " ")
numlines=$(grep -r "$searchstr" "$filesdir" | wc -l | tr -d " ")

echo "The number of files are $numfiles and the number of matching lines are $numlines"
