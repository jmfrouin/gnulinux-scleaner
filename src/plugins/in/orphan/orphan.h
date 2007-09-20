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

#ifndef __ORPHAN_H_
#define __ORPHAN_H_

#include <config.h>
#include <plugins/iplugin.h>
#include <tools/thread.h>

/*!
*@brief Thread plugin.
*
* This plugin will find / delete orphan folder from "/home/user/.APP".
*/
class CorphanPlugin : public IPlugin, public IThread
{
    public:
        CorphanPlugin();
        ~CorphanPlugin();

		/*!
		*@brief From IPlugin.
		*/
		const std::string location();
		const std::string description();
		bool isThreadable();
		eType Type();

		/*!
		*@brief From CThread.
		*/
		virtual void __Run();

};
#endif                           //_ORPHAN_H_
/* vi:set ts=4: */
