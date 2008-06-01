/**
 * This file is part of scleaner project.

 * Copyright (C) 2008 FROUIN Jean-Michel

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

#ifndef __INPUT_PLUGIN_H__
#define __INPUT_PLUGIN_H__

#include <config.h>
#include <plugins/in/in_plugin.h>

namespace Plugins
{
    /*!
     *@brief Input plugin interface.
     */
    class IInputPlugin : public IInPlugin
    {
        public:
            /*!
             *@brief ctor
             */
            IInputPlugin() {}

            /*!
             *@brief dtor
             */
            virtual ~IInputPlugin() {}

            /*!
             *@brief Does it need to grab null file size;
             *@return true if this plugin can grab null file size, false otherwise.
             */
            virtual bool GrabNullFile() = 0;

            /*!
            *@brief This method add, or not, filename to fFL.
            *@param filename The file name to process.
            */
            virtual void ProcessFile(const std::string& filename) = 0;

            /*!
            *@brief This method fill the directory to process.
            *@note Usable only if plugin's type is eByFolderInput.
            *@param path The directory name to process.
            */
            virtual void GetDirectory(std::string& path) = 0;

            //From IPlugin
            virtual bool Threadable() { return false; }
            virtual EType Type() { return eUserInput; }
    };
} //namespace Plugins
#endif                           // __INPUT_PLUGIN_H__
