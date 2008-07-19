#!/bin/bash
NAME=scleaner_$1
echo "Building debian package for : "$NAME
#Create a release folder
cp -r /home/snoogie/dev/scleaner/ $NAME
#Clean it
rm -rf $NAME/build $NAME/.git
#Enter folder
cd $NAME 
#Update changelog
dch -i
#Copy changelog to upstream :D
cp debian/changelog /home/snoogie/dev/scleaner/debian
#create debian package
dpkg-buildpackage -rfakeroot
