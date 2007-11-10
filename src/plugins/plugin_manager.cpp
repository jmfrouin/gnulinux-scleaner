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

#include <dlfcn.h>				 ///In order to load dyn lib.
#include <dirent.h>				 ///For path manipulation.
#include <iostream>
#include <string>
#include "plugin_manager.h"
#include <leak/leak_detector.h>

namespace Plugins
{
	CPluginManager::~CPluginManager()
	{
		#if defined DEBUG
		//Input plugins
		int l_size = m_InputPlugins.size();
		std::cout << i8n("[DBG] I founded ");
		if(l_size > 2)
		{
			std::cout << l_size << i8n(" input plugins : ") << '\n';
		}
		else
		{
			std::cout << l_size << i8n(" input plugin : ") << '\n';
		}
		std::map<std::string, IInPlugin*>::iterator _it;
		for(_it = m_InputPlugins.begin(); _it != m_InputPlugins.end(); ++_it)
		{
			std::cout << "[DBG] " << (*_it).first << ": ";
			//bool l_threadable = ((*_it).second)->isThreadable();
			//if(l_threadable)
			//{
			//	std::cout << "[DBG] [Threadable]" << '\n';
			//}
			//else
			//{
			//	std::cout << "[DBG] [Standard]" << '\n';
			//}
		}
	
		//Output plugins
		l_size = m_OutputPlugins.size();
		std::cout << i8n("[DBG] I founded ");
		if(l_size > 2)
		{
			std::cout << l_size << i8n(" output plugins : ") << '\n';
		}
		else
		{
			std::cout << l_size << i8n(" output plugin : ") << '\n';
		}
		std::map<std::string, IOutPlugin*>::iterator _it2;
		for(_it2 = m_OutputPlugins.begin(); _it2 != m_OutputPlugins.end(); ++_it2)
		{
			std::cout << "[DBG] " << (*_it2).first << ": ";
			//bool l_threadable = ((*_it2).second)->isThreadable();
			//if(l_threadable)
			//{
			//	std::cout << "[DBG] [Threadable]" << '\n';
			//}
			//else
			//{
			//	std::cout << "[DBG] [Standard]" << '\n';
			//}
		}
		#endif
	}
	
	
	int CPluginManager::loadPlugins(const std::string& _path)
	{
		struct dirent** l_namelist;
		int l_res = 0;
		int l_nb = scandir(_path.c_str(), &l_namelist, 0, alphasort);
		while (l_nb-- > 0)
		{
			std::string l_tmp = _path;
			l_tmp += "/";
			l_tmp += l_namelist[l_nb]->d_name;
			free(l_namelist[l_nb]);
	
			if (l_tmp.length() > 28)
			{
				void* l_handler = dlopen (l_tmp.c_str(), RTLD_NOW);
				if (l_handler != 0)
				{
					l_res++;
				}
				else
				{
					std::cerr << "[ERR] loadPlugins " << dlerror() << std::endl;
				}
			}
		}
		free(l_namelist);
		return l_res;
	}
	
	
	void CPluginManager::add(IInPlugin* _toadd)
	{
		m_InputPlugins.insert(make_pair(_toadd->getName(), _toadd));
	}
	
	
	void CPluginManager::add(IOutPlugin* _toadd)
	{
		m_OutputPlugins.insert(make_pair(_toadd->getName(), _toadd));
	}
	
	
	std::map<std::string, IInPlugin*>* CPluginManager::getInputListPtr()
	{
		std::map<std::string, IInPlugin*>* l_ret;
		l_ret = &m_InputPlugins;
		return l_ret;
	}
	
	
	std::map<std::string, IOutPlugin*>* CPluginManager::getOutputListPtr()
	{
		std::map<std::string, IOutPlugin*>* l_ret;
		l_ret = &m_OutputPlugins;
		return l_ret;
	}
	
	
	void CPluginManager::getFileList(std::list<std::string>& _fl)
	{
		std::map<std::string, IInPlugin*>::iterator _it;
		for(_it = m_InputPlugins.begin(); _it != m_InputPlugins.end(); ++_it)
		{
			((*_it).second)->getFileList(_fl);
		}
	}
	
	
	//FIXME : Trash code, to clean one day
	//int l_ret = 0;
	//int l_size = 0;
	
	//std::map<std::string, IInPlugin*>::iterator l_it;
	//for(l_it = m_InputPlugins.begin(); l_it != m_InputPlugins.end(); ++l_it)
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
} //namespace Plugins

/* vi:set ts=4: */
