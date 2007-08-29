/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
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
$Date$
$Rev$
$Author$
------------------------------------------------------

*/

#include <iostream>
#include <plugins/plugin_initializer.h>
#include "tbz.h"
#include <wx/dir.h>
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>

CPluginInitializer<CtbzPlugin> g_tbz;

CtbzPlugin::CtbzPlugin()
{
    setName("tbz");
}

CtbzPlugin::~CtbzPlugin()
{
}

void CtbzPlugin::processFileList(std::list<std::string>& _fl)
{
	std::cout << "tbz output plugins" << '\n';
}

const std::string CtbzPlugin::description()
{
	return "This plugin allow user to create a tarball then compress it using bzip2.";
}

const std::string CtbzPlugin::author()
{
	return "Frouin Jean-Michel";
}

const std::string CtbzPlugin::version()
{
	return "0.1";
}

IPlugin::eType CtbzPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}
/* vi:set ts=4: */
