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
* - @subpage logs
*/

/*! @page logs logs: input plugin.
* @section desc Description
* This plugin allow user to clean <b>logs</b> files.
* <br>
* In fact it just scan <b>/var/log/</b> and its subfolders.
* @section param Parameters
* @section pb Knows bugs
* @section todo Todo
* Put folder scannings code in CEngine.
*/

#ifndef _LOGS_H_
#define _LOGS_H_

#include <config.h>
#include <plugins/in_plugin.h>

class ClogsPlugin : public IInPlugin
{
    public:
        ClogsPlugin();
        ~ClogsPlugin();

		/*!
		*@brief From IPlugin.
		*/
		const std::string description();
		const std::string author();
		const std::string version();
		eType Type();

		/*!
		*@brief From IInPlugin
		*@todo : Fix use of wxwidgets in plugins !!!!
		*/
		void getFileList(std::list<std::string>& _fl);
		bool needRoot();
};
#endif                           //_LOGS_H_
/* vi:set ts=4: */
