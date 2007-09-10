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
timestamp=`date +%d%m%y_%H%M%S`
if [ $# -ne 1 ]; then
	echo $0 version
	exit
fi
tar cvf ${PROG}_$1.tar * --exclude=.svn --exclude=build --exclude=build2 > /dev/null
echo Creating tar archive : ${PROG}_$1.tar
gzip ${PROG}_$1.tar 
echo Compression of tar archive : ${PROG}_$1.tar.gz
