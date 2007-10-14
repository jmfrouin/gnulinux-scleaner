/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <dirent.h>				 ///For path manipulation.
#include <sys/stat.h>
#include <engine/engine.h>
#include <leak/leak_detector.h>
#include <plugins/inplugin_initializer.h>
#include "emptyfolders.h"

Plugins::CPluginInitializerIn<CemptyfoldersPlugin> g_emptyfolders;

CemptyfoldersPlugin::CemptyfoldersPlugin()
{
	setName("empty folders");
}


CemptyfoldersPlugin::~CemptyfoldersPlugin()
{
}


Plugins::IPlugin::eType CemptyfoldersPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}


void CemptyfoldersPlugin::processFile(const std::string& _filename)
{
	struct stat l_stat;

	//Try to stat file.
	if(stat(_filename.c_str(), &l_stat) == -1)
	{
		std::cout << i8n("[ERR] : Cannot stat ") << _filename << '\n';
	}
	else
	{
		//std::cout << "Stat : " << l_stat.st_mode << '\n';
		if(S_ISDIR(l_stat.st_mode))
		{
			struct dirent** l_namelist;
			int l_nb = scandir(_filename.c_str(), &l_namelist, 0, alphasort);
			if(l_nb == 2) //So contain only : . and ..
			{
				m_fl.push_back(_filename);
			}
			while (l_nb-- > 0)
			{
				free(l_namelist[l_nb]);
			}
			free(l_namelist);
		}
	}
}


bool CemptyfoldersPlugin::needRoot()
{
	bool l_ret;
	l_ret = false;				 // This plugin will work in both (user/root) mode.
	return l_ret;
}
/* vi:set ts=4: */
