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

#ifndef __THREAD_IN_PLUGIN_H__
#define __THREAD_IN_PLUGIN_H__

#include <config.h>
#include <in_plugin.h>

namespace Plugins
{
    /*!
     *@brief Input plugin interface.
     */
    class IThreadInPlugin : public IInPlugin
    {
        public:
            /*!
             *@brief ctor
             */
            IThreadInPlugin() {}

            /*!
             *@brief dtor
             */
            virtual ~IThreadInPlugin() {}

            /*!
             * @brief From InPlugin
             * @author snoogie (5/22/2008)
             * @return bool
             */
            bool Threadable() { return true; }


            //From IPlugin
            virtual EType Type() { return eUserInput; }

        protected:
            std::list<std::string>      fFL;
    };
} //namespace Plugins
#endif                           // __THREAD_IN_PLUGIN_H__
