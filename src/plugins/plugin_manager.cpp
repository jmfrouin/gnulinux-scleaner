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

#include <dlfcn.h>               ///In order to load dyn lib.
#include <dirent.h>              ///For path manipulation.
#include <iostream>
#include <string>
#include "plugin_manager.h"
#include <leak/leak_detector.h>

namespace Plugins
{
    CPluginManager::~CPluginManager()
    {
        #if defined DEBUG && defined VERBOSE
        //Input plugins
        int Size = fInputPlugins.size();
        std::cout << i8n("[DBG] I founded ");
        if(Size > 2)
            std::cout << Size << i8n(" input plugins : ") << '\n';
        else
            std::cout << Size << i8n(" input plugin : ") << '\n';
        std::map<std::string, IInPlugin*>::iterator It;
        for(It = fInputPlugins.begin(); It != fInputPlugins.end(); ++It)
            std::cout << (*It).first << ", ";
        std::cout << '\n';

        //Output plugins
        Size = fOutputPlugins.size();
        std::cout << i8n("[DBG] I founded ");
        if(Size > 2)
            std::cout << Size << i8n(" output plugins : ") << '\n';
        else
            std::cout << Size << i8n(" output plugin : ") << '\n';
        std::map<std::string, IOutPlugin*>::iterator It2;
        for(It2 = fOutputPlugins.begin(); It2 != fOutputPlugins.end(); ++It2)
            std::cout << "[DBG] " << (*It2).first << "\n";
        #endif
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
                    std::cerr << "[ERR] loadPlugins " << dlerror() << std::endl;
            }
        }
        free(Namelist);
        return Res;
    }


    void CPluginManager::Add(IInPlugin* toadd)
    {
        fInputPlugins.insert(make_pair(toadd->GetName(), toadd));
        #if defined DEBUG && defined VERBOSE
        std::cout << "[DBG] CPluginManager::Add " << toadd->GetName() << '\n';
        #endif
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


    //FIXME : Trash code, to clean one day
    //int Ret = 0;
    //int Size = 0;

    //std::map<std::string, IInPlugin*>::iterator lIt;
    //for(lIt = fInputPlugins.begin(); lIt != fInputPlugins.end(); ++lIt)
    //{
    //  std::string l_file = ((*lIt).second)->location();
    //  std::string lpath = l_file.substr(0, l_file.find_last_of("/"));
    //  std::string l_mask = l_file.substr(l_file.find_last_of("/") + 1, l_file.length());

    //  wxDir l_dir(lpath);
    //  Size = 0;
    //
    //  //We get all files as well archived one.
    //  l_mask += "*";

    //  if ( !l_dir.IsOpened() )
    //  {
    //      std::cout << "[ERR] Cannot open folder : " << lpath << '\n';
    //      return 0;
    //  }

    //  wxString l_filename;

    //  bool cont = l_dir.GetFirst(&l_filename, l_mask, wxDIR_DEFAULT);
    //  while(cont)
    //  {
    //      struct stat l_info;
    //      std::string l_name(lpath);
    //      l_name += "/";
    //      l_name += l_filename.c_str();
    //      if(stat(l_name.c_str(), &l_info) == -1)
    //      {
    //          std::cout << "[ERR] : " __FILE__ << "@" << __LINE__ << ": Cannot stat " << l_filename.c_str() << '\n';
    //      }
    //      Size += l_info.st_size;
    //      cont = l_dir.GetNext(&l_filename);
    //  }
    //  Ret += Size;
    //  std::cout << ((*lIt).second)->getName() << " : " << Size << " bytes" << '\n';
    //}

    //std::cout << "Total : " << Ret << '\n';
    //return Ret;
    //}
} //namespace Plugins

/* vi:set ts=4: */
