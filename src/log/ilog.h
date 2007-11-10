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

#ifndef _ILOG_H
#define _ILOG_H

#include <fstream>

/*!
 * @brief Log manipulation interface
 * @version 23.10.2007
 * @author Jean-Michel Frouin (jmforuin@gnu.org)
 */
class ILog
{
	public:
		/*!
		 * @brief	Default constructor.
		 */
		ILog();
		/*!
		 * @brief	Destructor.
		 */
		virtual ~ILog();

		/*!
		 * @brief	Write report.
		 */
		virtual void Report() = 0;

	public:
		std::ofstream      m_File;
};
#endif							 //_ILOG_H_
/* vi:set ts=4: */
