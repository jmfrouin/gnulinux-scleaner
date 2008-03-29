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

#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

#include <config.h>
#include <string>
#include <list>
#include <tools/name.h>

/*!
*@brief Contain all code to manage plugins.
*/
namespace Plugins
{
    /**
     * @brief Plugin Interface
     * @version 06.05.2007
     * @author Jean-Michel Frouin (jmfrouin@gmail.com)
     */
    class IPlugin : public Tools::CName
    {
        public:
            enum eType
            {
                eUserInput,
                eUserByFolderInput,
                eRootInput,
                eRootByFolderInput,
                eOutput
            };

        public:
            /*!
             * @brief ctor
             */
            IPlugin(){}

            /*!
             * @brief dtor.
             */
            virtual ~IPlugin(){}

            /*!
             *@brief Description.
             */
            virtual std::string Description() = 0;

            /*!
             *@brief Input or output plugin ?
             */
            virtual eType Type() = 0;
    };
} //namespace Plugins
#endif                           //_IPLUGIN_H_
/* vi:set ts=4: */
