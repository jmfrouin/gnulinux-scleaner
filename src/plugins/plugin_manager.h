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
$Date: 2007-08-13 21:07:17 +0200 (lun, 13 aoû 2007) $
$Rev: 13 $
$Author: snoogie_sf $
------------------------------------------------------

*/

#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

#include <config.h>
#include <map>
#include <string>
#include <tools/singleton.h>
#include <tools/smart_pointer.h>
#include "iplugin.h"

/*!
 *@brief Common source code of all plugins.
 *@note This code will be put in a dynamic library (libmanager.so).
 */
class CPluginManager: public CSmartCpt, public TSingleton<CPluginManager>
{
    public:
        /*!
         *@brief Load all available plugins.
         *@param path The folder location.
         *@return Number of plugins founded.
         */
        int loadPlugins (const std::string& path);

        /*!
         *@brief Add a new plugin to the list of available plugins.
         *@param _toadd Plugin to add.
         */
        void add(IPlugin* _toadd);

		/*!
		*@brief Pointer on plugins list
		*/
		std::map<std::string, IPlugin*>* getPluginsListPtr();

        /*!
         *@brief Return space used for all available plugins.
		 *@return Size in bytes.
         */
        int SpaceUsed();

        /*!
         * @brief ctor.
         */
        CPluginManager(){};

        /*!
         * @brief dtor.
         */
        ~CPluginManager();

    private:
        std::map<std::string, IPlugin*> m_PluginsList;	///< List of available plugins.
};
#endif                           //_PLUGIN_MANAGER_H_
/* vi:set ts=4: */
