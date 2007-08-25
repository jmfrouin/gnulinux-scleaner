/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
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

#ifndef _APP_H_
#define _APP_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <tools/smart_pointer.h>
#include <engine/engine.h>

// Define a new application
class CSClean: public wxApp
{
	public:
		CSClean();
    	bool OnInit(void);
	
	private:
		TSmartPtr<CPluginManager> 	m_pfm;
		TSmartPtr<CEngine> 			m_engine;
};

#endif // _APP_H_
/* vi:set ts=4: */
