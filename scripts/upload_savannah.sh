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

#!/bin/bash
if [ $# -ne 3 ]; then
	echo $0 filename login projectname
	exit
fi
echo First sign the file:
gpg -b --use-agent $1
chmod 644 $1 $1.sig
echo Give read permissions to your files!
scp $1 $1.sig $2@dl.sv.nongnu.org:/releases/$3/
echo Uploaded!
