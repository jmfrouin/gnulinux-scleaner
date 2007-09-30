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
$Date: 2007-09-28 18:46:28 +0200 (ven, 28 sep 2007) $
$Rev: 135 $
$Author: snoogie $
------------------------------------------------------
*/

/*! @page page3 Plugins documentations.
 * - @subpage rm
 */

/*! @page rm rm: output plugin.
 * @section desc Description
 * This plugin allow user to delete all selected files from input plugins.
 * <br>
 * @section param Parameters
 * @section pb Knows bugs
 * @section todo Todo
 */

#ifndef _RM_H_
#define _RM_H_

#include <config.h>
#include <plugins/out_plugin.h>

class CrmPlugin : public IOutPlugin
{
	public:
		CrmPlugin();
		~CrmPlugin();

		/*!
		 *@brief From IPlugin.
		 */
		eType Type();

		/*!
		*@brief From IOutPlugin
		*/
		void processFileList(std::list<std::string>& _fl, const std::string& _path, IProgressbar* _callback);
};
#endif							 //_RM_H_
/* vi:set ts=4: */
