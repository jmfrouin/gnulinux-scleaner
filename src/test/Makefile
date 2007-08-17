# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 
# ------------------------------------------------------
# Project : scleaner
# ------------------------------------------------------
# $Date: $
# $Rev: $
# $Author: $
# ------------------------------------------------------

CFLAGS = -Wall -pedantic -g -pthread

all : test_thread

test_thread: thread.o test_thread.cpp
	g++ ${CFLAGS} -o $@ $^

thread.o:	thread.cpp
	g++ ${CFLAGS} -c $^

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}
