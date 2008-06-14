/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.org
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

#include "scleaner_wx.h"
#include <config.h>
#include <string>
#include <leak/memory_manager.h>
#include <engine/engine.h>

CMemoryManager g_mm;

#include <leak/leak_detector.h>
#include <log/log.h>

IMPLEMENT_APP(CSClean)

CSClean::CSClean()
{
}

CSClean::~CSClean()
{
    //delete Log::CLog::Instance();
}

bool CSClean::OnInit(void)
{
    //i8n
    setlocale( LC_ALL, "" );
    bindtextdomain( "scleaner", "/usr/share/locale" );
    textdomain( "scleaner" );

    #if defined DEBUG
    std::cout << i8n("[DBG] scleaner starting ...\n");
    #endif

    bool Ret = false;
    wxImage::AddHandler(new wxPNGHandler);

    //Retrieve Engine::CEngine instance pointer.
    fEngine = Engine::CEngine::Instance();

    //Load plugins
    fEngine->LoadPlugins(PLUG_FOLDER);

    //Load GFX interface
    Ret = fEngine->LoadInterface();

    return Ret;
}


/* vi:set ts=4: */
