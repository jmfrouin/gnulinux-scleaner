#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.

PROG=scleaner

#!/bin/bash
if [ $# -ne 1 ]; then
	echo $0 version
	exit
fi
tar cvf ${PROG}_$1.orig.tar . --exclude=${PROG}_$1.orig.tar --exclude=.svn --exclude=build > /dev/null
echo Creating tar archive : ${PROG}_$1.orig.tar
gzip ${PROG}_$1.orig.tar 
echo Compression of tar archive : ${PROG}_$1.orig.tar.gz
mv ${PROG}_$1.orig.tar.gz build/
echo Moving ${PROG}_$1.orig.tar.gz to build
mkdir build/${PROG}-$1
echo Creating build/${PROG}-$1 directory
cd build/${PROG}-$1
echo Entering build/${PROG}-$1 directory
dh_make -s
echo dh_make
#cmake ../../src/
#echo Launching cmake
dpkg-buildpackage -rfakeroot 
echo Package built
