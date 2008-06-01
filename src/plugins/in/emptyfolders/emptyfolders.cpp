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
#include <dirent.h>              ///For path manipulation.
#include <sys/stat.h>
#include <engine/engine.h>
#include <leak/leak_detector.h>
#include <plugins/in/in_plugin_initializer.h>
#include "emptyfolders.h"

Plugins::CInPluginInitializer<CemptyfoldersPlugin> gEmptyFolders;

CemptyfoldersPlugin::CemptyfoldersPlugin()
{
    SetName("empty folders");
}


CemptyfoldersPlugin::~CemptyfoldersPlugin()
{
}


void CemptyfoldersPlugin::ProcessFile(const std::string& filename)
{
    struct stat Stat;

    //Try to stat file.
    if(stat(filename.c_str(), &Stat) == -1)
        std::cout << i8n("[ERR] : Cannot stat ") << filename << '\n';
    else
    {
        if(S_ISDIR(Stat.st_mode))
        {
            struct dirent** NameList;
            int Nb = scandir(filename.c_str(), &NameList, 0, alphasort);
            if(Nb != -1) //Fix Bug 4 : If no error append.
            {
                if(Nb == 2) //So contain only : . and ..
                    fFL.push_back(filename);
                while (Nb-- > 0)
                    free(NameList[Nb]);
                free(NameList);
            }
        }
    }
}


std::string CemptyfoldersPlugin::Description()
{
    return "Find empty folder size";
}
/* vi:set ts=4: */
