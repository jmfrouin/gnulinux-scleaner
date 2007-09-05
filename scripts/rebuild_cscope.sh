#!/bin/bash

#find /media/red/sdatabase/src/ -name "*.h" -o -name "*.cpp" > /home/snoogie/cscope.files
#cd /home/snoogie/
#cscope -b
#export CSCOPE_DB=/home/snoogie/cscope.out
find . -name "*.h" -o -name "*.cpp" > cscope.files
cscope -b

