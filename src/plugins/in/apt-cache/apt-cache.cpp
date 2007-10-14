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
#include <sys/utsname.h>
#include <plugins/inplugin_initializer.h>
#include "apt-cache.h"
#include <wx/dir.h>
#include <leak/leak_detector.h>

Plugins::CPluginInitializerIn<Capt_cachePlugin> g_apt_cache;

Capt_cachePlugin::Capt_cachePlugin()
{
	setName("apt cache");
}


Capt_cachePlugin::~Capt_cachePlugin()
{
}


Plugins::IPlugin::eType Capt_cachePlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}


void Capt_cachePlugin::getDirectory(std::string& _path)
{
	_path = "/var/cache/apt/archives/";
}


void Capt_cachePlugin::processFile(const std::string& _filename)
{
	m_fl.push_back(_filename);
}

bool Capt_cachePlugin::needRoot()
{
	bool l_ret = false;
	l_ret = true;				 // /boot/ cannot be access by simple user
	return l_ret;
}


/* vi:set ts=4: */
