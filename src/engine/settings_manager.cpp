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

#include <fstream>
#include "engine.h"
#include "settings_manager.h"

namespace Engine
{
	CSettingsManager::CSettingsManager():
	m_ShowSplash(true), m_ShowToolbar(true), m_ShowStatusbar(true)
	{
		std::string l_path;

		if(CEngine::isRoot())
		{
			l_path += "/root";
		}
		else
		{
			l_path += "/home/";
			std::string l_user;
			CEngine::getUsername(l_user);
			l_path += l_user;
		}
		
		//Fixme : need to create folder : bug 5
		std::string l_config(l_path);
		l_config += "/.scleaner/prefs.conf";


		std::ifstream l_File(l_config.c_str());
		unsigned int l_Label;

		if(l_File.good())
		{
			while(1)
			{
				l_File >> l_Label;
				if(l_File.eof() == true)
				{
					break;
				}
				std::string l_folder;
				switch(l_Label)
				{
					case eShowSplash:
						l_File >> m_ShowSplash;
						break;
					case eFolderInc:
						l_File >> l_folder;
						m_FoldersList.push_back(l_folder);
						break;
					case eFolderEx:
						l_File >> l_folder;
						m_ExcludedFoldersList.push_back(l_folder);
						break;
					case eShowToolbar:
						l_File >> m_ShowToolbar;
						break;
					case eShowStatusbar:
						l_File >> m_ShowStatusbar;
						break;
					default:
						continue;
				}
			}		
		}
		else
		{
			//Default configuration
			m_FoldersList.push_back("/home");
			m_ExcludedFoldersList.push_back(l_path);
		}

		#if defined DEBUG
		std::cout << "Loading pref : \n";
		std::cout << "m_ShowSplash = " << m_ShowSplash << '\n';
		std::cout << "m_ShowToolbar = " << m_ShowToolbar << '\n';
		std::cout << "m_ShowStatusbar = " << m_ShowStatusbar << '\n';
		#endif
	}
	

	CSettingsManager::~CSettingsManager()
	{
		std::string l_path;

		if(CEngine::isRoot())
		{
			l_path += "/root";
		}
		else
		{
			l_path += "/home/";
			std::string l_user;
			CEngine::getUsername(l_user);
			l_path += l_user;
		}
		
		std::string l_config(l_path);
		l_config += "/.scleaner/prefs.conf";

		std::ofstream l_File(l_config.c_str());

		//Splash screen
		l_File << eShowSplash << ' ' << m_ShowSplash << '\n';

		//Debug
		#if defined DEBUG
		std::cout << "Saving pref\n";
		std::cout << "m_ShowSplash = " << m_ShowSplash << '\n';
		std::cout << "m_ShowToolbar = " << m_ShowToolbar << '\n';
		std::cout << "m_ShowStatusbar = " << m_ShowStatusbar << '\n';
		#endif

		//Folders include in scan
		std::list<std::string>::iterator l_it;
		for(l_it = m_FoldersList.begin(); l_it != m_FoldersList.end(); ++l_it)
		{
			#if defined DEBUG
			std::cout << "Adding :" << *l_it << '\n';
			#endif
			l_File << eFolderInc << ' ' << *l_it << '\n';
		}

		//Folders exclude from scan
		for(l_it = m_ExcludedFoldersList.begin(); l_it != m_ExcludedFoldersList.end(); ++l_it)
		{
			#if defined DEBUG
			std::cout << "Excluding :" << *l_it << '\n';
			#endif
			l_File << eFolderEx << ' ' << *l_it << '\n';
		}

		//Show toolbar
		l_File << eShowToolbar << ' ' << m_ShowToolbar << '\n';

		//Show status bar
		l_File << eShowStatusbar << ' ' << m_ShowStatusbar << '\n';
	}


	bool CSettingsManager::addFolder(std::string _dir, std::string& _parent, eFoldersType _type)
	{
		bool l_ret = true;

		std::list<std::string>* l_fl;

		switch(_type)
		{
			case eFoldersInc:
				l_fl = &m_FoldersList;
				break;
			case eFoldersEx:
				l_fl = &m_ExcludedFoldersList;
				break;
			default:
				l_fl = 0;
				break;
		}
		
		//Search a parent folder:
		std::list<std::string>::iterator l_it;
		bool l_clean = false;
		for(l_it = l_fl->begin(); l_it != l_fl->end(); ++l_it)
		{
			//If a parent is found
			if(_dir.find(*l_it, 0) != std::string::npos)
			{
				_parent = *l_it;
				l_ret = false;
				break;
			}
			else
			{
				//If _dir is a parent :D
				if((*l_it).find(_dir, 0) != std::string::npos)
				{
					l_clean = true;
					break;
				}
			}
		}
	
		if(l_clean)
		{	
			l_it = l_fl->begin();
			do
			{
				if((*l_it).find(_dir, 0) != std::string::npos)
				{
					std::list<std::string>::iterator l_it2erase = l_it;
					++l_it;
					l_fl->erase(l_it2erase);
				}
				else
				{
					++l_it;
				}
			}while(l_it != l_fl->end());
		}
		
		if(l_ret)
		{
			l_fl->push_back(_dir);
		}
		else
		{
			//If a parent folder is found, no need to add is child.
			#if defined DEBUG
			std::cerr << "[WRG] Parent folder found : " << (*l_it) << " no need to add " << _dir << '\n';
			#endif
		}
		
		return l_ret;
	}
	
	void CSettingsManager::delFolder(const std::string _dir, eFoldersType _type)
	{
		std::list<std::string>::iterator l_it;
		std::list<std::string>* l_fl;

		switch(_type)
		{
			case eFoldersInc:
				l_fl = &m_FoldersList;
				break;
			case eFoldersEx:
				l_fl = &m_ExcludedFoldersList;
				break;
			default:
				l_fl = 0;
				break;
		}

		if(l_fl != 0)
		{
			for(l_it = l_fl->begin(); l_it != l_fl->end(); ++l_it)
			{
				if((*l_it) == _dir)
				{
					l_fl->erase(l_it);
					break;
				}
			}
		}
	}
} //namespace Engine
