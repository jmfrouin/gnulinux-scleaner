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
SET(emptyfolders_src emptyfolders.cpp)
ADD_LIBRARY(emptyfolders SHARED ${emptyfolders_src}) 
TARGET_LINK_LIBRARIES(emptyfolders plugins tools)
INSTALL(TARGETS emptyfolders DESTINATION ${PLUGSDIR}/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/plugins/in/emptyfolders/emptyfolders.html DESTINATION ${SHAREDIR}/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/plugins/in/emptyfolders/emptyfolders_fr.html DESTINATION ${SHAREDIR}/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
