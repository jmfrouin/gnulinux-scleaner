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

#ifndef _IPROGRESS_H_
#define _IPROGRESS_H_

#include <string>
/**
 * @brief Plugin Interface
 */
class IProgressbar
{
	public:
		/*!
		*@brief Update process progress bar callback.
		*@param _nb Update number.
		*/
		virtual void updateProgress(const std::string& _mess, int _nb) = 0;
};
#endif                           //_IPROGRESS_H_
/* vi:set ts=4: */

