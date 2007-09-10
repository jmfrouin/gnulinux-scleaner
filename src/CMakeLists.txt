#
# Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
# 
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
# $Date: 2007-08-13 21:09:03 +0200 (lun, 13 aoû 2007) $
# $Rev: 14 $
# $Author: snoogie_sf $
# ------------------------------------------------------
# 04/09/07 : Adding a cscope rule

PROJECT(scleaner)

INCLUDE(FindDoxygen)
INCLUDE(FindLATEX)
INCLUDE(FindUnixCommands)
INCLUDE(FindwxWidgets)

ADD_DEFINITIONS(-g -DLEAK_DETECTOR -DDEBUG )
ADD_DEFINITIONS(-Wall -MD `wx-config --cxxflags`)

INCLUDE_DIRECTORIES(AFTER SYSTEM . ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR})
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/config.h)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#For installation
SET(BINDIR /usr/bin/)
SET(SHAREDIR /usr/share/scleaner/)

SET(folder engine interface leak log tools)
FOREACH(fold ${folder})
	ADD_SUBDIRECTORY(${fold})
ENDFOREACH(fold ${folder})

SET(scleaner_src scleaner_wx.cpp)

ADD_EXECUTABLE(scleaner ${scleaner_src})
TARGET_LINK_LIBRARIES(scleaner dl engine interface leaks log plugins tools `wx-config --libs`)

# Valgrind test
ADD_CUSTOM_TARGET(valgrind COMMAND  valgrind -v --show-reachable=yes --leak-check=full scleaner)

#cscope
ADD_CUSTOM_TARGET(cscope ALL COMMAND find ${CMAKE_SOURCE_DIR} -name "*.h" -o -name "*.cpp" > ${CMAKE_SOURCE_DIR}/cscope.files && cscope -b -f${CMAKE_SOURCE_DIR}/cscope.out)

#Install
INSTALL(TARGETS scleaner DESTINATION ${BINDIR} PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/html/about.html DESTINATION ${SHAREDIR}/html/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/gfx/splash.png DESTINATION ${SHAREDIR} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
