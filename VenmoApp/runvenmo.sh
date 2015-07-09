#!/bin/bash
cd src
javac venmoapp/*.java

if [ $# -eq 0 ]
then
java venmoapp/Runner
else
java venmoapp/Runner $1
fi
