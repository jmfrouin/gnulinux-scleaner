/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

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

#ifndef __PLUGIN_MANAGER_H__
#define __PLUGIN_MANAGER_H__

#include <config.h>
#include <map>
#include <list>
#include <string>
#include <tools/singleton.h>
#include <tools/smart_pointer.h>
#include <in_plugin.h>
#include <out_plugin.h>

namespace Plugins
{
    /*!
     *@brief Common source code of all plugins.
     *@version 29.03.2008
     *@author Jean-Michel Frouin (jmfrouin@gmail.com)
     *@note This code will be put in a dynamic library (libmanager.so).
     */
    class CPluginManager: public Tools::CSmartCpt, public Tools::TSingleton<CPluginManager>
    {
        public:
            /*!
             *@brief Load all available plugins.
             *@param path The folder location.
             *@return Number of plugins founded.
             */
            int LoadPlugins (const std::string& path);

            /*!
             *@brief Add a new input plugin to the list of available plugins.
             *@param toadd Plugin to add.
             */
            void Add(IInPlugin* toadd);

            /*!
             *@brief Add a new output plugin to the list of available plugins.
             *@param toadd Plugin to add.
             */
            void Add(IOutPlugin* toadd);

            /*!
             *@brief Pointer on input plugins list
             */
            std::map<std::string, IInPlugin*>* GetInputListPtr();

            /*!
             *@brief Pointer on output plugins list
             */
            std::map<std::string, IOutPlugin*>* GetOutputListPtr();

            /*!
             *@brief Retrieve list found of ALL plugins.
             */
            void GetFileList(std::list<std::string>& fl);

            /*!
             * @brief ctor.
             */
            CPluginManager(){};

            /*!
             * @brief dtor.
             * @todo Fix the leak on plugins loaded.
             */
            ~CPluginManager();

        private:
                                     ///< List of available input plugins.
            std::map<std::string, IInPlugin*>   fInputPlugins;
                                     ///< List of available output plugins.
            std::map<std::string, IOutPlugin*>  fOutputPlugins;
    };
} //namespace Plugins
#endif                           //__PLUGIN_MANAGER_H__
/* vi:set ts=4: */
