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

#ifndef _OUT_PLUGIN_H_
#define _OUT_PLUGIN_H_

#include <config.h>
#include <engine/iprogress.h>
#include "iplugin.h"

namespace Plugins
{
	/*!
	 *@brief Output plugin interface.
	 */
	class IOutPlugin : public IPlugin
	{
		public:
			/*!
			 *@brief ctor
			 */
			IOutPlugin() {}
			/*!
			 *@brief dtor
			 */
			virtual ~IOutPlugin() {}
	
			/*!
			 *@brief Process all files selected by user.
			 *@param _fl Files list to fill.
			 *@param _path Where to write output files (if applicable).
			 *@param _callback For progress bar support.
			 */
			virtual void processFileList(std::list<std::string>& _fl, const std::string& _path, IProgressbar* _callback) = 0;
	};
}
#endif							 // _OUT_PLUGIN_H_
