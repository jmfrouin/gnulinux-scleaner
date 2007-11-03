/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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

#ifndef _BY_FOLDER_PLUGIN_H_
#define _BY_FOLDER_PLUGIN_H_

#include <config.h>

namespace Plugins
{
	/*!
	 *@brief Plugin which work on a directory.
	 */
	class IByFolderPlugin : public IInPlugin
	{
		public:
			/*!
			 *@brief ctor
			 */
			IByFolderPlugin() {}
			/*!
			 *@brief dtor
			 */
			virtual ~IByFolderPlugin() {}
	
			/*!
			*@brief This method fill the directory to process.
			*@param _filename The directory name to process.
			*/
			virtual void getDirectory(std::string& _path) = 0;
	};
} //namespace Plugins
#endif							 // _BY_FOLDER_PLUGIN_H_
/* vi:set ts=4: */

