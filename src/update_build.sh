#!/bin/bash

OLD=`awk '/#define BUILD.*/{print $3}' $1`
#echo ${OLD}
NEW=`expr ${OLD} + 1`
#echo ${NEW}
sed "s/${OLD}/${NEW}/" $1 > temp
mv temp $1
