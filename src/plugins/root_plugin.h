/*
Copyright (C) 2007 FROUROOT Jean-Michel
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
$Date: 2007-09-25 22:33:08 +0200 (mar, 25 sep 2007) $
$Rev: 128 $
$Author: snoogie $
------------------------------------------------------
*/

#ifndef _ROOT_PLUGROOT_H_
#define _ROOT_PLUGROOT_H_

#include <config.h>
#include "in_plugin.h"

/*!
 *@brief Root input plugin interface.
 */
class IRootPlugin : public IInPlugin
{
	public:
		/*!
		 *@brief ctor
		 */
		IRootPlugin() {}
		/*!
		 *@brief dtor
		 */
		virtual ~IRootPlugin() {}

		/*!
		*@brief This method fill the directory to process.
		*@param _filename The directory name to process.
		*/
		virtual void getDirectory(std::string& _path) = 0;
};
#endif							 // _ROOT_PLUGROOT_H_
