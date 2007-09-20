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

#ifndef _IN_PLUGIN_H_
#define _IN_PLUGIN_H_

#include <config.h>
#include "iplugin.h"

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
			*@brief Does it need to be run as root (sudo) ?
			*/
			virtual bool needRoot() = 0;

			/*!
			*@brief Return a std::list of files targeted by plugin.
			*/
			virtual void getFileList(std::list<std::string>& _fl) = 0;
};

#endif // _IN_PLUGIN_H_
