/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
*/
/*
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

#ifndef _KERN_H_
#define _KERN_H_

#include <config.h>
#include <plugins/iplugin.h>

/*!
*@brief Find unused kernels.
*/
class CkernelsPlugin : public IPlugin
{
    public:
        CkernelsPlugin();
        ~CkernelsPlugin();

	/*!
	*@brief From IPlugin.
	*/
	//const std::string location();
	void getFileList(std::list<std::string>& _fl);
	const std::string description();
	eType Type();

};
#endif                           //_KERN_H_
/* vi:set ts=4: */
