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

#define PREFFILE "~/.scleaner/prefs.conf"

namespace Engine
{
	/*!
	* @brief Manage all settings.
	* Load them on creation
	* Save them on destruction (or Apply)
	* @version 09.11.2007
	* @author Jean-Michel Frouin (jmfrouin@gnu.org)
	*/
	class CSettingsManager: public Tools::CSmartCpt, public Tools::TSingleton<CSettingsManager>
	{
		public:
			/*!
			* Construstor : Load preferences.
			*/
			CSettingsManager();
			
			/*!
			* Destructor : Save preferences.
			*/
			~CSettingsManager();
	
			/*!
			* Accessors
			*/
			bool getShowSplash() { return m_ShowSplash; }
	
			/*!
			* Mutators
			*/
			void setShowSplash(bool _val) { m_ShowSplash = _val; }
	
	
		private:
			bool				m_ShowSplash;	///Display splash (only in GUI) ?
	
	};
} //namespace Engine

#endif //_SETTINGS_MANAGER_H_
