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
$Date: 2007-09-22 19:17:21 +0200 (sam, 22 sep 2007) $
$Rev: 115 $
$Author: snoogie $
------------------------------------------------------
*/

#include <iostream>
#include <plugins/plugin_initializer.h>
#include "backfiles.h"
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>
#include <engine/engine.h>

CPluginInitializer<CbackfilesPlugin> g_backfiles;

CbackfilesPlugin::CbackfilesPlugin()
{
    setName("backfiles");
}

CbackfilesPlugin::~CbackfilesPlugin()
{
}

IPlugin::eType CbackfilesPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}

//From IInPlugin
void CbackfilesPlugin::getFileList(std::list<std::string>& _fl)
{
	CEngine* l_Eng = CEngine::Instance();
	if(l_Eng != 0)
	{
		std::string l_path("/home/");
		std::string l_username;
		bool l_res = l_Eng->getUsername(l_username);
		if(l_res)
		{
			l_path += l_username;
			l_path += "/";
		}
		l_Eng->getFileList(_fl, l_path, "~");
		l_Eng->getFileList(_fl, l_path, ".bak");
	}
}

bool CbackfilesPlugin::needRoot()
{
	bool l_ret;
	l_ret = false; // This plugin will work in both (user/root) mode.
	return l_ret;
}

/* vi:set ts=4: */
