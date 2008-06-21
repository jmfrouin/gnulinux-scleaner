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

#ifndef __NAME_H__
#define __NAME_H__

#include <config.h>
#include <string>

/*!
 *@brief Various tools classes.
 */
namespace Tools
{
  /**
   * @brief A base class who named an object.
   */
  class CName
  {
    public:
      /*!
       *@brief Default constructor.
       */
      CName();

      /*!
       *@brief Destructor.
       */
      virtual ~CName();

      /*!
       *@brief Retrieve the current name.
       *@return A string which contain the name.
       */
      virtual const std::string& GetName();

      /*!
       *@brief Set the current name.
       *@param name A string which contain the name.
       */
      virtual void SetName(const std::string& name);

    private:
      std::string     fName;     ///< The name.

  };
}
#endif                           //__NAME_H__
/* vi:set ts=4: */
