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

SET(tbz_src tbz.cpp)
ADD_LIBRARY(tbz SHARED ${tbz_src}) 
TARGET_LINK_LIBRARIES(tbz plugins tools /usr/lib/libtar.a)
INSTALL(TARGETS tbz DESTINATION ${PLUGSDIR}/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/plugins/out/tbz/tbz.html DESTINATION ${SHAREDIR}/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
