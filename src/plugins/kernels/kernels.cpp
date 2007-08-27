/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
*/
/*
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
#include "kernels.h"
#include <wx/dir.h>
#include <leak/leak_detector.h>

CPluginInitializer<CkernelsPlugin> g_kernels;

CkernelsPlugin::CkernelsPlugin()
{
    setName("kernels");
}

CkernelsPlugin::~CkernelsPlugin()
{
}

//const std::string CkernelsPlugin::location()
//{
//	return "/var/log/kernels.log";
//}
//

void CkernelsPlugin::getFileList(std::list<std::string>& _fl)
{
	std::string l_path = "/boot/";

    wxDir l_dir(l_path);
	int l_size = 0;
		
   	if ( !l_dir.IsOpened() )
   	{
		std::cout << "[ERR] Cannot open folder : " << l_path << '\n';
   	}

   	wxString l_filename;

	std::string l_mask;
	l_mask = "abi*";
   	bool cont = l_dir.GetFirst(&l_filename, l_mask, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.c_str();
		_fl.push_back(l_tmp);
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "config*";
   	cont = l_dir.GetFirst(&l_filename, l_mask, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.c_str();
		_fl.push_back(l_tmp);
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "initrd*";
   	cont = l_dir.GetFirst(&l_filename, l_mask, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.c_str();
		_fl.push_back(l_tmp);
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "System.map*";
   	cont = l_dir.GetFirst(&l_filename, l_mask, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.c_str();
		_fl.push_back(l_tmp);
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "vmlinuz*";
   	cont = l_dir.GetFirst(&l_filename, l_mask, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.c_str();
		_fl.push_back(l_tmp);
   	    cont = l_dir.GetNext(&l_filename);
   	}

	//std::cout << "kernels plugin : " << l_size << " bytes" << '\n';
}


const std::string CkernelsPlugin::description()
{
	return "Kernel log cleaner";
}

IPlugin::eType CkernelsPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}
/* vi:set ts=4: */
