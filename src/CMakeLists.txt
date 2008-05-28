#
# This file is part of scleaner project.
#
# Copyright (C) 2007 FROUIN Jean-Michel
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
# 02/11/07 : Adding a build counter
# 04/09/07 : Adding a cscope rule
# 17/05/08 : Adding profiling code

PROJECT(scleaner)

#Others dependencies for scleaner
FOREACH(LIB zlibK)
FIND_LIBRARY(${LIB}dev NAMES wx${LIB}${_DBG} PATHS ${WX_LIB_DIR} NO_DEFAULT_PATH)
ENDFOREACH(LIB)

INCLUDE(FindDoxygen)
INCLUDE(FindLATEX)
INCLUDE(FindUnixCommands)
INCLUDE(FindwxWidgets)
INCLUDE(FindBZip2)
INCLUDE(cmake/FindAPT.cmake)

SET(SCLEANER_CFLAGS "-pg ")
SET(SCLEANER_LDFLAGS "-pg ")

IF(PROFILE)
        SET(SCLEANER_CFLAGS "-pg ${SCLEANER_CFLAGS}")
        SET(SCLEANER_LDFLAGS "-pg ${SCLEANER_LDFLAGS}")
ENDIF(PROFILE)

ADD_DEFINITIONS(-Wall -MD -pg -g -DLEAK_DETECTOR `wx-config --cxxflags` -DwxUSE_UNICODE -DDEBUG -DVERBOSE)

INCLUDE_DIRECTORIES(AFTER SYSTEM . ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR})
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/config.h)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#For installation
SET(BINDIR /usr/bin/)
SET(SHAREDIR /usr/share/doc/scleaner/)
SET(SHAREAPP /usr/share/applications/)
SET(PLUGSDIR /usr/share/scleaner/plugs/)
SET(MANDIR /usr/share/man/man1/)
SET(ICONS /usr/share/pixmaps/)
SET(LANG_FR /usr/share/locale/fr/LC_MESSAGES/)

SET(folder engine interface leak log plugins tools)
FOREACH(fold ${folder})
        ADD_SUBDIRECTORY(${fold})
ENDFOREACH(fold ${folder})

SET(scleaner_src scleaner_wx.cpp)

ADD_EXECUTABLE(scleaner ${scleaner_src})
SET_TARGET_PROPERTIES(scleaner PROPERTIES LINK_FLAGS "-pg" COMPILE_FLAGS "-pg")
TARGET_LINK_LIBRARIES(scleaner pthread dl engine interface leaks log plugins tools `wx-config --libs`)

# Valgrind test
ADD_CUSTOM_TARGET(valgrind COMMAND  valgrind -v --show-reachable=yes --leak-check=full scleaner)

#cscope
#ADD_CUSTOM_TARGET(cscope ALL COMMAND find ${CMAKE_SOURCE_DIR} -name "*.h" -o -name "*.cpp" > ${CMAKE_SOURCE_DIR}/cscope.files && cscope -b -f${CMAKE_SOURCE_DIR}/cscope.out)

#build counter
ADD_CUSTOM_TARGET(update_counter ALL COMMAND bash ${CMAKE_SOURCE_DIR}/update_build.sh ${CMAKE_SOURCE_DIR}/def.h)

#Install
INSTALL(TARGETS scleaner DESTINATION ${BINDIR} PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/gfx/splash.png DESTINATION ${SHAREDIR} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/scleaner.1 DESTINATION ${MANDIR} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/fr/scleaner.mo DESTINATION ${LANG_FR} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/scleaner.desktop DESTINATION ${SHAREAPP} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/sudo_scleaner.desktop DESTINATION ${SHAREAPP} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/gfx/scleaner.png DESTINATION ${ICONS} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/gfx/scleaner.xpm DESTINATION ${ICONS} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/gfx/scleaner_root.xpm DESTINATION ${ICONS} PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
