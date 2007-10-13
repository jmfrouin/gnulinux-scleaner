/*
Copyright (C) 2007 FROUIN Jean-Michel
------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------
Project : scleaner
------------------------------------------------------
$Date: 2007-09-25 22:33:08 +0200 (mar, 25 sep 2007) $
$Rev: 128 $
$Author: snoogie $
------------------------------------------------------
*/

#ifndef _OUTPLUGIN_INITIALIZER_H_
#define _OUTPLUGIN_INITIALIZER_H_

#include <config.h>
#include <iostream>
#include <engine/engine.h>

#include "plugin_manager.h"

namespace Plugins
{
	template <class T>
	class CPluginInitializerOut
	{
		public:
			CPluginInitializerOut()
			{
				CPluginManager* l_pfm = CPluginManager::Instance();
				T* l_obj = new T;
				l_pfm->add(l_obj);
			}
	};
}
#endif							 //_OUTPLUGIN_INITIALIZER_H_
/* vi:set ts=4: */
