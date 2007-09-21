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

#include <config.h>
#include <string>
#include <leak/memory_manager.h>
#include "scleaner_wx.h"
#include <engine/engine.h>
#include <libintl.h>

CMemoryManager g_mm;

#include <leak/leak_detector.h>

IMPLEMENT_APP(CSClean)

CSClean::CSClean()
{
}

bool CSClean::OnInit(void)
{
	textdomain("scleaner");
#if defined DEBUG
	std::cout << "[DBG] scleaner starting ...\n";
#endif

    bool l_ret = false;
    wxImage::AddHandler(new wxPNGHandler);

	//Retrieve CEngine instance pointer.
	m_engine = CEngine::Instance();

	//Load plugins
	m_engine->loadPlugins("/usr/share/scleaner/plugs");
	//Load GFX interface
	l_ret = m_engine->loadInterface();

    return l_ret;
}

/* vi:set ts=4: */
