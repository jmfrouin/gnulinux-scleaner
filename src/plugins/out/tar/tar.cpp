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
$Date: 2007-08-28 13:37:21 +0200 (mar, 28 aoû 2007) $
$Rev: 44 $
$Author: snoogie $
------------------------------------------------------

*/

#include <iostream>
#include <plugins/plugin_initializer.h>
#include "tar.h"
#include <wx/dir.h>
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>

CPluginInitializer<CtarPlugin> g_tar;

CtarPlugin::CtarPlugin()
{
    setName("tar");
}

CtarPlugin::~CtarPlugin()
{
}

//const std::string CtarPlugin::location()
//{
//	return "/var/log/tar.log";
//}
//

void CtarPlugin::processFileList(std::list<std::string>& _fl)
{
	std::cout << "tar output plugins" << '\n';
}

const std::string CtarPlugin::description()
{
	return "This plugin allow user to create a tarball";
}

const std::string CtarPlugin::author()
{
	return "Frouin Jean-Michel";
}

const std::string CtarPlugin::version()
{
	return "0.1";
}

IPlugin::eType CtarPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}
/* vi:set ts=4: */
