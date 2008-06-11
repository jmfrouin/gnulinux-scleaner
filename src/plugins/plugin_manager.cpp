/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

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

#include "plugin_manager.h"

#include <dlfcn.h>               ///In order to load dyn lib.
#include <dirent.h>              ///For path manipulation.
#include <iostream>
#include <string>

#include <leak/leak_detector.h>

namespace Plugins
{
    CPluginManager::~CPluginManager()
    {
    }


    int CPluginManager::LoadPlugins(const std::string& path)
    {
        struct dirent** Namelist;
        int Res = 0;
        int Nb = scandir(path.c_str(), &Namelist, 0, alphasort);
        while (Nb-- > 0)
        {
            std::string Tmp = path;
            Tmp += "/";
            Tmp += Namelist[Nb]->d_name;
            free(Namelist[Nb]);

            if (Tmp.length() > 28)
            {
                void* Handler = dlopen (Tmp.c_str(), RTLD_NOW);
                if (Handler != 0)
                    Res++;
                else
                    std::cerr << "[ERR] loadPlugins " << dlerror() << '\n';
            }
        }
        free(Namelist);
        return Res;
    }

    void CPluginManager::Add(IInPlugin* toadd)
    {
        fInputPlugins.insert(make_pair(toadd->GetName(), toadd));
    }

    void CPluginManager::Add(IOutPlugin* toadd)
    {
        fOutputPlugins.insert(make_pair(toadd->GetName(), toadd));
    }


    std::map<std::string, IInPlugin*>* CPluginManager::GetInputListPtr()
    {
        return &fInputPlugins;
    }


    std::map<std::string, IOutPlugin*>* CPluginManager::GetOutputListPtr()
    {
        return &fOutputPlugins;
    }


    void CPluginManager::GetFileList(std::list<std::string>& fl)
    {
        std::map<std::string, IInPlugin*>::iterator It;
        for(It = fInputPlugins.begin(); It != fInputPlugins.end(); ++It)
            ((*It).second)->GetFileList(fl);
    }
} //namespace Plugins

/* vi:set ts=4: */
