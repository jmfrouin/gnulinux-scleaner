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

/*! @page page3 Plugins documentations.
 * - @subpage backfiles
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

class CbackfilesPlugin : public Plugins::IInPlugin
{
	public:
		CbackfilesPlugin();
		~CbackfilesPlugin();

		/*!
		 *@brief From IPlugin.
		 */
		eType Type();
		bool grabNullFile()
		{
			return false;
		}

		/*!
		 *@brief From Plugins::IInPlugin
		 */
		void processFile(const std::string& _filename);
		bool needRoot();
};
#endif							 //_BACKFILES_H_
/* vi:set ts=4: */
