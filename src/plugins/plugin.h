/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

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

#ifndef __IPLUGIN_H__
#define __IPLUGIN_H__

#include <config.h>
#include <string>
#include <list>
#include <tools/name.h>

/*!
 *@brief Define a plugin.
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
      //! All input plugins' type
      enum EType
      {
        eUserInput,              /*!< Basic input plugin: call for each files found in user defined folders. */
        eRootInput,              /*!< Input plugin which require root privileges.*/
        eThreadableInput,        /*!<  Threadable input plugin, run alone from others.*/
        eRootThreadableInput,    /*!< eRootInput + eThreadableInput*/
        eOutput                  /*!<  Output plugin.*/
      };

    public:
      /*!
       * @brief ctor
       * @author snoogie (5/22/2008)
       */
      IPlugin(){}

      /*!
       * @brief dtor
       * @author snoogie (5/22/2008)
       */
      virtual ~IPlugin(){}

      /*!
       * @brief Threadable plugin ?
       * @author snoogie (5/22/2008)
       * @return bool true on threadable plugin, false otherwise
       */
      bool Threadable();

      /*!
       * @brief Full 'user friendly' description.
       * @todo Add a 'tech friendly' description.
       * @author snoogie (5/22/2008)
       * @return std::string
       */
      virtual std::string Description() = 0;

      /*!
       * @brief Type from EType.
       * @author snoogie (5/22/2008)
       * @return EType
       */
      virtual EType Type() = 0;
  };
}                                //namespace Plugins
#endif                           //__IPLUGIN_H__
/* vi:set ts=4: */
