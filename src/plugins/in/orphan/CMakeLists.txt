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
# ------------------------------------------------------
# Project : scleaner
# ------------------------------------------------------
# $Date: 2007-08-13 21:09:03 +0200 (lun, 13 aoû 2007) $
# $Rev: 14 $
# $Author: snoogie_sf $
# ------------------------------------------------------

set(orphan_src orphan.cpp)
add_library(orphan SHARED ${orphan_src}) 
target_link_libraries(orphan plugins tools)
