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

#include "trash.h"

#include <iostream>
#include <dirent.h>

#include <plugins/in/in_plugin_initializer.h>
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>
#include <engine/engine.h>

Plugins::CInPluginInitializer<CtrashPlugin> gTrash;

CtrashPlugin::CtrashPlugin()
{
    SetName("trash");
}


CtrashPlugin::~CtrashPlugin()
{
    std::cout << "~CtrashPlugin : " << fFL.size() << '\n';
}


std::string CtrashPlugin::Description()
{
    return "Find files in your trashbin";
}

void CtrashPlugin::GetFileList(std::list<std::string>& fl)
{
    fl.merge(fFL);
}

void CtrashPlugin::Run()
{
    std::string Path("/home/snoogie/.local/share/Trash/files/");
    while(fRunning)
    {
        struct dirent** NameList;
        int Nb = scandir(Path.c_str(), &NameList, 0, alphasort);
        if(Nb >= 0) //Fix Bug 4 : If no error append.
        {
            while (Nb-- > 0)
            {
                std::string Name(NameList[Nb]->d_name);
                struct stat Stat;
                //Is it a folder ?
                if(stat(Name.c_str(), &Stat) == -1)
                     std::cout << i8n("[ERR] : Cannot stat ") << Name << '\n';
                else
                {
                    if(S_ISDIR(Stat.st_mode))
                        std::cout << Name << " is a folder \n";
                }

                if(Name != "." && Name != "..")
                    fFL.push_back(Name);
                else
                    std::cout << "I skip " << Name << '\n';
                free(NameList[Nb]);
            }
            free(NameList);
        }
        else
            std::cout << ROUGE << "CtrashPlugin::Run() : Error\n" << STOP;
        fRunning=false;
    }
}
/* vi:set ts=4: */
