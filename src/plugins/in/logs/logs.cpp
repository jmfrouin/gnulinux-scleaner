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
$Date$
$Rev$
$Author$
------------------------------------------------------
*/

#include <iostream>
#include <plugins/plugin_initializer.h>
#include "logs.h"
#include <wx/dir.h>
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>

CPluginInitializer<ClogsPlugin> g_logs;

ClogsPlugin::ClogsPlugin()
{
    setName("logs");
}

ClogsPlugin::~ClogsPlugin()
{
}

const std::string ClogsPlugin::description()
{
	return "This plugin allow user to clean all logs, located in /var/log. This plugin needs root access !!";
}

const std::string ClogsPlugin::author()
{
	return "Frouin Jean-Michel";
}

const std::string ClogsPlugin::version()
{
	return "0.3";
}

IPlugin::eType ClogsPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}

//From IInPlugin
void ClogsPlugin::getFileList(std::list<std::string>& _fl)
{
	std::string l_path = "/var/log/";
	std::string l_mask = "*";

	wxString l_upath(l_path.c_str(), wxConvUTF8);
    wxDir l_dir(l_upath);

#if defined DEBUG
	int l_size = 0;
#endif

	//We get all files as well archived one. (*.1 *.2 ...)
   	if ( !l_dir.IsOpened() )
   	{
		std::cout << "[ERR] Cannot open folder : " << l_path << '\n';
   	}

   	wxString l_filename;

	wxString l_umask(l_mask.c_str(), wxConvUTF8);
   	bool cont = l_dir.GetFirst(&l_filename, l_umask, wxDIR_DEFAULT);
   	while(cont)
   	{
		//struct stat l_info;
		//std::string l_name(l_path);
		//l_name += "/";
		//l_name += l_filename.c_str();
		//if(stat(l_name.c_str(), &l_info) == -1)
		//{
		//	std::cout << "[ERR] : " __FILE__ << "@" << __LINE__ << ": Cannot stat " << l_filename.c_str() << '\n';
		//}
		//l_size += l_info.st_size;
		std::string l_tmp = l_path;
		l_tmp += l_filename.fn_str();
		_fl.push_back(l_tmp);
   	    cont = l_dir.GetNext(&l_filename);
   	}

#if defined DEBUG
	std::cout << "[DBG] Logs plugin : " << l_size << " bytes" << '\n';
#endif
}

bool ClogsPlugin::needRoot()
{
	bool l_ret;
	l_ret = true; // In order to access /var/log/ we nned root access.
	return l_ret;
}

/* vi:set ts=4: */
