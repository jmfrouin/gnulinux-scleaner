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

#ifndef __IN_PLUGIN_H__
#define __IN_PLUGIN_H__

#include <config.h>
#include <plugins/iplugin.h>

namespace Plugins
{
    /*!
     *@brief Input plugin interface.
     */
    class IInPlugin : public IPlugin
    {
        public:
            /*!
             *@brief ctor
             */
            IInPlugin() {}

            /*!
             *@brief dtor
             */
            virtual ~IInPlugin() {}

            /*!
             *@brief Does it need to grab null file size;
             *@return true if this plugin can grab null file size, false otherwise.
             */
            virtual bool GrabNullFile() = 0;

            /*!
             *@brief Selected by default configuration ?
             *@return true if "founded files" have to been pre"set" to Yes, false otherwise
             */
            virtual bool GetDefaultSelection() = 0;

            /*!
             *@brief Return a std::list of files targeted by plugin.
             *@param fl The files list to fill.
             */
            virtual void GetFileList(std::list<std::string>& fl)
            {
                fl.merge(fFL);
            }

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

            /*!
             * @brief Define is a plugin is threadable.
             * @author snoogie (5/22/2008)
             * @return bool true if threadable, false otherwise.
             */
            virtual bool Threadable() { return false; }


            //From IPlugin
            virtual EType Type() { return eUserInput; }

        protected:
            std::list<std::string> fFL;
    };
} //namespace Plugins
#endif                           // __IN_PLUGIN_H__
