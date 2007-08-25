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

#include <dlfcn.h>               ///In order to load dyn lib.
#include <dirent.h>              ///For path manipulation.
#include <iostream>
#include <string>
#include "plugin_manager.h"
#include <leak/leak_detector.h>

CPluginManager::~CPluginManager()
{
	int l_size = m_PluginsList.size();
	std::cout << "I founded ";
	if(l_size > 2)
	{
    	 std::cout << l_size << " plugins : " << '\n';
	}
	else
	{
    	std::cout << l_size << " plugin : " << '\n';
	}
    std::map<std::string, IPlugin*>::iterator _it;
    for(_it = m_PluginsList.begin(); _it != m_PluginsList.end(); ++_it)
    {
        std::cout << (*_it).first << ": ";
        std::cout << ((*_it).second)->description();
        bool l_threadable = ((*_it).second)->isThreadable();
		if(l_threadable)
		{
			std::cout << "[Threadable]" << '\n';
		}
		else
		{
			std::cout << "[Standard]" << '\n';
		}
    }
}

int CPluginManager::loadPlugins(const std::string& path)
{
    struct dirent** namelist;
    int l_res = 0;
    int n = scandir(path.c_str(), &namelist, 0, alphasort);
    while (n-- > 0)
    {
        std::string tmp = path;
        tmp += "/";
        tmp += namelist[n]->d_name;

        if (tmp.length() > 8)
        {
            void* handler = dlopen (tmp.c_str(), RTLD_NOW);
            if (handler != 0)
            {
                //std::cout << " " << tmp << " loaded ! " << std::endl;
                l_res++;
            }
            else
            {
                std::cerr << "ERR : " << dlerror() << std::endl;
            }
        }
    }
    //std::cout << l_res << '\n';
    return l_res;
}

void CPluginManager::add(IPlugin* _toadd)
{
    m_PluginsList.insert(make_pair(_toadd->getName(), _toadd));
}

std::map<std::string, IPlugin*>* CPluginManager::getPluginsListPtr()
{
	std::map<std::string, IPlugin*>* l_ret;
	l_ret = &m_PluginsList;
	return l_ret;
}

void CPluginManager::getFileList(std::list<std::string>& _fl)
{
    std::map<std::string, IPlugin*>::iterator _it;
    for(_it = m_PluginsList.begin(); _it != m_PluginsList.end(); ++_it)
	{
		((*_it).second)->getFileList(_fl);
	}
}
    //int l_ret = 0;
    //int l_size = 0;

    //std::map<std::string, IPlugin*>::iterator l_it;
    //for(l_it = m_PluginsList.begin(); l_it != m_PluginsList.end(); ++l_it)
    //{
	//	std::string l_file = ((*l_it).second)->location();
	//	std::string l_path = l_file.substr(0, l_file.find_last_of("/"));
	//	std::string l_mask = l_file.substr(l_file.find_last_of("/") + 1, l_file.length());

    //	wxDir l_dir(l_path);
	//	l_size = 0;
	//	
	//	//We get all files as well archived one.
	//	l_mask += "*";

    //	if ( !l_dir.IsOpened() )
    //	{
	//		std::cout << "[ERR] Cannot open folder : " << l_path << '\n';
    //	    return 0;
    //	}

    //	wxString l_filename;

    //	bool cont = l_dir.GetFirst(&l_filename, l_mask, wxDIR_DEFAULT);
    //	while(cont)
    //	{
	//		struct stat l_info;
	//		std::string l_name(l_path);
	//		l_name += "/";
	//		l_name += l_filename.c_str();
	//		if(stat(l_name.c_str(), &l_info) == -1)
	//		{
	//			std::cout << "[ERR] : " __FILE__ << "@" << __LINE__ << ": Cannot stat " << l_filename.c_str() << '\n';
	//		}
	//		l_size += l_info.st_size;
    //	    cont = l_dir.GetNext(&l_filename);
    //	}
	//	l_ret += l_size;
	//	std::cout << ((*l_it).second)->getName() << " : " << l_size << " bytes" << '\n';
	//}

	//std::cout << "Total : " << l_ret << '\n';
    //return l_ret;
//}
/* vi:set ts=4: */
