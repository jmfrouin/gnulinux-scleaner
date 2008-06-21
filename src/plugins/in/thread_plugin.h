/**
 * This file is part of scleaner project.

 * Copyright (C) 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.org
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
#include <plugins/in/in_plugin.h>
#include <tools/thread.h>

namespace Plugins
{
  /*!
   *@brief Input plugin interface.
   */
  class IThreadPlugin : public IInPlugin, public Tools::IThread
  {
    public:
      /*!
       *@brief ctor
       */
      IThreadPlugin() {}

      /*!
       *@brief dtor
       */
      virtual ~IThreadPlugin() {}

      /*!
       * @brief From InPlugin
       * @author snoogie (5/22/2008)
       * @return bool
       */
      bool Threadable() { return true; }

      //From IThread
      virtual void Run() = 0;

      //From IPlugin
      virtual std::string Description() = 0;
      virtual EType Type() = 0;
  };
}                                //namespace Plugins
#endif                           // __THREAD_IN_PLUGIN_H__
