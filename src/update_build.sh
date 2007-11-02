#!/bin/bash

OLD=`awk '/#define BUILD.*/{print $3}' $1`
NEW=`expr ${OLD} + 1`
sed "30s/${OLD}/${NEW}/" $1 > temp
mv temp $1

