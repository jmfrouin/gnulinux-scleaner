/*
Copyright (C) 2007 FROUIN Jean-Michel
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
$Date$
$Rev$
$Author$
------------------------------------------------------
*/

#ifndef _NAME_H_
#define _NAME_H_

#include <config.h>
#include <string>

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
		virtual const std::string& getName();

		/*!
		 *@brief Set the current name.
		 *@param _Name A string which contain the name.
		 */
		virtual void setName(const std::string& _Name);

	private:
		std::string     m_Name;	 ///< The name.

};
#endif							 //_NAME_H_
/* vi:set ts=4: */
