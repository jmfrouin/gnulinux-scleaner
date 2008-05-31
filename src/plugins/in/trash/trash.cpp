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

#include <plugins/in/inplugin_initializer.h>
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>
#include <engine/engine.h>

Plugins::CPluginInitializerIn<CtrashPlugin> gTrash;

CtrashPlugin::CtrashPlugin()
{
    SetName("trash");
}


CtrashPlugin::~CtrashPlugin()
{
    std::cout << "~CtrashPlugin : " << fFL.size() << '\n';
}


void CtrashPlugin::ProcessFile(const std::string& filename)
{
    //fFL.push_back(filename);
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
                if(NameList[Nb]->d_name != "." || NameList[Nb]->d_name != "..")
                {
                    fFL.push_back(NameList[Nb]->d_name);
                }
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
