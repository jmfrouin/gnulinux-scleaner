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
#include <sys/utsname.h>
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

const std::string CkernelsPlugin::description()
{
	return "This plugins allow user to removed all unused kernels. This plugin need root access !!";
}

const std::string CkernelsPlugin::author()
{
	return "Frouin Jean-Michel";
}

const std::string CkernelsPlugin::version()
{
	return "0.1";
}

IPlugin::eType CkernelsPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}

//From IInPlugin
void CkernelsPlugin::getFileList(std::list<std::string>& _fl)
{
	//First get current kernel version
	std::string l_kernel;
	utsname l_temp;

	if(uname(&l_temp) != 0)
	{
		std::cerr << "[CEngine::getKernelVersion] Error !\n";
	}
	else
	{
		l_kernel = l_temp.release;
		std::cout << l_kernel << '\n';
	}

	std::string l_path = "/boot/";

	wxString l_upath(l_path.c_str(), wxConvUTF8);
    wxDir l_dir(l_upath);
   	if ( !l_dir.IsOpened() )
   	{
		std::cout << "[ERR] Cannot open folder : " << l_path << '\n';
   	}

   	wxString l_filename;

	std::string l_mask;
	l_mask = "abi*";

	wxString l_umask(l_mask.c_str(), wxConvUTF8);
   	bool cont = l_dir.GetFirst(&l_filename, l_umask, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.fn_str();
		//If this isn't a current kernel file
		if(l_tmp.find(l_kernel) == std::string::npos)
		{
			_fl.push_back(l_tmp);
		}
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "config*";

	wxString l_umask2(l_mask.c_str(), wxConvUTF8);
   	cont = l_dir.GetFirst(&l_filename, l_umask2, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.fn_str();
		//If this isn't a current kernel file
		if(l_tmp.find(l_kernel) == std::string::npos)
		{
			_fl.push_back(l_tmp);
		}
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "initrd*";

	wxString l_umask3(l_mask.c_str(), wxConvUTF8);
   	cont = l_dir.GetFirst(&l_filename, l_umask3, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.fn_str();
		//If this isn't a current kernel file
		if(l_tmp.find(l_kernel) == std::string::npos)
		{
			_fl.push_back(l_tmp);
		}
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "System.map*";

	wxString l_umask4(l_mask.c_str(), wxConvUTF8);
   	cont = l_dir.GetFirst(&l_filename, l_umask4, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.fn_str();
		//If this isn't a current kernel file
		if(l_tmp.find(l_kernel) == std::string::npos)
		{
			_fl.push_back(l_tmp);
		}
   	    cont = l_dir.GetNext(&l_filename);
   	}
	l_mask = "vmlinuz*";

	wxString l_umask5(l_mask.c_str(), wxConvUTF8);
   	cont = l_dir.GetFirst(&l_filename, l_umask5, wxDIR_DEFAULT);
   	while(cont)
   	{
		std::string l_tmp = l_path;
		l_tmp += l_filename.fn_str();
		//If this isn't a current kernel file
		if(l_tmp.find(l_kernel) == std::string::npos)
		{
			_fl.push_back(l_tmp);
		}
   	    cont = l_dir.GetNext(&l_filename);
   	}

	//std::cout << "kernels plugin : " << l_size << " bytes" << '\n';
}
bool CkernelsPlugin::needRoot()
{
	bool l_ret = false;
	l_ret = true; // /boot/ cannot be access by simple user
	return l_ret;
}
/* vi:set ts=4: */
