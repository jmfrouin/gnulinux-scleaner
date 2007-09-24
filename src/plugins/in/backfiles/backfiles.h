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
$Date: 2007-09-20 19:54:41 +0200 (jeu, 20 sep 2007) $
$Rev: 109 $
$Author: snoogie $
------------------------------------------------------
*/

/*! @page page3 Plugins documentations.
* - @subpage logs
*/

/*! @page backfiles backfiles: input plugin.
* @section desc Description
* This plugin allow user to clean his backup files : <b>*.bak, *~ or #*</b> nammed files.
* <br>
* In fact it just scan <b>/home/user/</b> and its subfolders.
* @section param Parameters
* @section pb Knows bugs
* @todo Support both modes, simple user & root/sudo.
*/

#ifndef _BACKFILES_H_
#define _BACKFILES_H_

#include <config.h>
#include <plugins/in_plugin.h>

class CbackfilesPlugin : public IInPlugin
{
    public:
        CbackfilesPlugin();
        ~CbackfilesPlugin();

		/*!
		*@brief From IPlugin.
		*/
		eType Type();

		/*!
		*@brief From IInPlugin
		*@todo : Fix use of wxwidgets in plugins !!!!
		*/
		void getFileList(std::list<std::string>& _fl);
		bool needRoot();
};
#endif                           //_BACKFILES_H_
/* vi:set ts=4: */
