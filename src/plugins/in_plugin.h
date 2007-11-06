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

#ifndef _IN_PLUGIN_H_
#define _IN_PLUGIN_H_

#include <config.h>
#include "iplugin.h"

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
			virtual bool grabNullFile() = 0;
	
			/*!
			 *@brief Selected by default configuration ?
			 *@return true if "founded files" have to been pre"set" to Yes, false otherwise
			 */
			virtual bool getDefaultSelection() = 0;

			/*!
			 *@brief Return a std::list of files targeted by plugin.
			 *@param _fl The files list to fill.
			 */
			void getFileList(std::list<std::string>& _fl)
			{
				_fl.merge(m_fl);
			}
	
			/*!
			*@brief This method add, or not, _filename to m_fl.
			*@param _filename The file name to process.
			*/
			virtual void processFile(const std::string& _filename) = 0;

			/*!
			*@brief This method fill the directory to process.
			*@note Usable only if plugin's type is e*ByFolderInput.
			*@param _filename The directory name to process.
			*/
			virtual void getDirectory(std::string& _path) = 0;


			//From IPlugin
			virtual eType Type() { return eUserInput; }
		
		protected:
			std::list<std::string>		m_fl;
	};
} //namespace Plugins
#endif							 // _IN_PLUGIN_H_
