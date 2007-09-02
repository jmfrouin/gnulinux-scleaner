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
#find . -name "*.h" -o -name "*.cpp" | xargs xgettext --from-code -a -d scleaner -k___ -s -o scleaner.pot 
msgfmt -o scleaner.mo -v scleaner.po
msgfmt -o scleaner_fr.mo -v scleaner_fr.po
