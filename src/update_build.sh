#!/bin/bash
# 29/06/2008 : Fixing small bug due to my sed exp:
# s/${OLD}/${NEW}/
# become
# s/#define BUILD ${OLD}/#define BUILD ${NEW}/
# to avoid pb :)

OLD=`awk '/#define BUILD.*/{print $3}' $1`
echo ${OLD}
NEW=`expr ${OLD} + 1`
echo ${NEW}
sed "s/#define BUILD ${OLD}/#define BUILD ${NEW}/" $1 > temp
mv temp $1
