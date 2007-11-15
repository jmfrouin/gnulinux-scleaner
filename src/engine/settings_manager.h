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

#ifndef _SETTINGS_MANAGER_H_
#define _SETTINGS_MANAGER_H_

#include <tools/smart_pointer.h>
#include <tools/singleton.h>
#include <string>
#include <list>

#define PREFFILE "~/.scleaner/prefs.conf"

namespace Engine
{
	/*!
	* @brief Manage all settings.
	* Load them on creation
	* Save them on destruction (or Apply)
	* @version 15.11.2007
	* @author Jean-Michel Frouin (jmfrouin@gnu.org)
	*/
	class CSettingsManager: public Tools::CSmartCpt, public Tools::TSingleton<CSettingsManager>
	{
		public:
			enum eSettings
			{
				eShowSplash = 10,
				eFolderInc,
				eFolderEx,
				eShowToolbar,
				eShowStatusbar
			};

			enum eFoldersType
			{
				eNone = 0,
				eFoldersInc,
				eFoldersEx
			};

		public:
			/*!
			* Construstor : Load preferences.
			*/
			CSettingsManager();
			
			/*!
			* Destructor : Save preferences.
			*/
			~CSettingsManager();
	
			//Kind of accessors
			/*!
			*@brief Add a folder to m_FoldersList.
			*@param _dir The directory to add (selected by user using wxDirDialog).
			*@param _parent The parent directory.
			*@param _type We add a folder to include or exclude ?.
			*@return true if folder added, false otherwise.
			*/
			bool addFolder(const std::string _dir, std::string& _parent, eFoldersType _type = eNone);
	
			/*!
			*@brief Remove a folder to m_FoldersList
			*@param _dir The directory to delete (selected by user using wxDirDialog)
			*@param _type We remove a folder to include or exclude ?.
			*/
			void delFolder(const std::string _dir, eFoldersType _type = eNone);
	

			/*!
			* Accessors
			*/
			bool getShowSplash() { return m_ShowSplash; }

			std::list<std::string>* getFoldersListPtr() { return &m_FoldersList; }

			std::list<std::string>* getExcludedFoldersListPtr() { return &m_ExcludedFoldersList; }
	
			bool getShowToolbar() { return m_ShowToolbar; }

			bool getShowStatusbar() { return m_ShowStatusbar; }

			/*!
			* Mutators
			*/
			void setShowSplash(bool _val) { m_ShowSplash = _val; }

			void setShowToolbar(bool _val) { m_ShowToolbar = _val; }

			void setShowStatusbar(bool _val) { m_ShowStatusbar = _val; }
	
		private:
			bool					m_ShowSplash;		///Display splash (only in GUI) ?

			//Folders infos
			std::list<std::string>	m_FoldersList;
			std::list<std::string>	m_ExcludedFoldersList;

			bool					m_ShowToolbar;		///Display toolbar (only in GUI) ?
			bool					m_ShowStatusbar;	///Display statusbar (only in GUI) ?
	};
} //namespace Engine

#endif //_SETTINGS_MANAGER_H_
