#!/bin/bash

if [[ ! -e build ]] || [[ ! -d build ]]; then
	echo "At first make build"
elif [ -z $1 ]; then
	echo "No Parameters found."
elif [ -e $1 ]; then
	$1
else
	echo "Executable file does not exist."
fi
