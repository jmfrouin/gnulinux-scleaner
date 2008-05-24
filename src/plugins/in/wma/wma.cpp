/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.fr
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


#include <iostream>
#include <plugins/in/inplugin_initializer.h>
#include "wma.h"
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>
#include <engine/engine.h>

Plugins::CPluginInitializerIn<CwmaPlugin> gCoders;

CwmaPlugin::CwmaPlugin()
{
    SetName("wma");
}


CwmaPlugin::~CwmaPlugin()
{
}


void CwmaPlugin::ProcessFile(const std::string& filename)
{
    struct stat Info;
    unsigned int FindWMA = filename.find(".wma", 0);
    if(FindWMA == (filename.length()-4) )
    {
        std::string MP3File(filename.substr(0, FindWMA-1));
        MP3File += ".mp3";
        if(stat(MP3File.c_str(), &Info) == -1)
           fFL.push_back(filename);
    }
}


std::string CwmaPlugin::Description()
{
    return "Find music.wma if music.mp3 exist";
}
/* vi:set ts=4: */
