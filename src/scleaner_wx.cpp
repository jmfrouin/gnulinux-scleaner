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

#include <config.h>
#include <list>
#include <string>
#include <plugins/plugin_manager.h>
#include <leak/memory_manager.h>

#include <interface/maininterface.h>
#include "scleaner_wx.h"
#include <engine/engine.h>

CMemoryManager g_mm;

#include <leak/leak_detector.h>

IMPLEMENT_APP(CSClean)

CSClean::CSClean()
{
}

bool CSClean::OnInit(void)
{
    bool l_ret = false;

	//Plugins manager
	m_pfm = CPluginManager::Instance();
    l_ret = m_pfm->loadPlugins("plugs");

	//Engine
	m_engine = CEngine::Instance();

	CMainInterface* l_Main = new CMainInterface(NULL, wxID_ANY, wxT(NAME), wxDefaultPosition, wxSize(365, 290));
    l_Main->Show(true);
    return true;
}

/* vi:set ts=4: */
