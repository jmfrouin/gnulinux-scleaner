/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.fr
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
#include <plugins/inplugin_initializer.h>
#include "backfiles.h"
#include <sys/stat.h>			 ///Get file size.
#include <leak/leak_detector.h>
#include <engine/engine.h>

Plugins::CPluginInitializerIn<CbackfilesPlugin> g_backfiles;

CbackfilesPlugin::CbackfilesPlugin()
{
	setName("backfiles");
}


CbackfilesPlugin::~CbackfilesPlugin()
{
}


void CbackfilesPlugin::processFile(const std::string& _filename)
{
	if((_filename.find("~", 0) == (_filename.length()-1)) || (_filename.find("bak", 0) == (_filename.length()-3)))
	{
		m_fl.push_back(_filename);
	}
}


std::string CbackfilesPlugin::Description()
{
	return "Find backup files (*~ and *bak files)";
}
/* vi:set ts=4: */
