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

/*! @page page3 Plugins documentations.
* - @subpage kernels
*/

/*! @page kernels kernels: input plugin.
* @section desc Description
* This plugin allow user to remove all <b>kernels</b> unused, automatically installed on system.
* <br>
* @section param Parameters
* @section pb Knows bugs
* @section todo Todo
*/

#ifndef _KERN_H_
#define _KERN_H_

#include <config.h>
#include <plugins/in_plugin.h>

/*!
*@brief Find unused kernels.
*/
class CkernelsPlugin : public IInPlugin
{
    public:
        CkernelsPlugin();
        ~CkernelsPlugin();

		/*!
		*@brief From IPlugin.
		*/
		const std::string description();
		const std::string author();
		const std::string version();
		eType Type();

		/*!
		*@brief From IInPlugin
		*/
		void getFileList(std::list<std::string>& _fl);
		bool needRoot();
};
#endif                           //_KERN_H_
/* vi:set ts=4: */
