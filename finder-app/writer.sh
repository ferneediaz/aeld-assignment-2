#!/bin/sh
# writer.sh - write a string to a file, creating parent directories as needed
# Usage: writer.sh <writefile> <writestr>

if [ $# -ne 2 ]; then
    echo "Error: two arguments required"
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

writefile=$1
writestr=$2

if ! mkdir -p "$(dirname "$writefile")"; then
    echo "Error: could not create directory for '$writefile'"
    exit 1
fi

if ! echo "$writestr" > "$writefile"; then
    echo "Error: could not create file '$writefile'"
    exit 1
fi
