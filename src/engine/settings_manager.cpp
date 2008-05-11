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

#include <fstream>
#include "engine.h"
#include "settings_manager.h"

namespace Engine
{
    CSettingsManager::CSettingsManager():
    fShowSplash(true), fShowToolbar(true), fShowStatusbar(true)
    {
        std::string Path;

        if(CEngine::IsRoot())
        {
            Path += "/root";
        }
        else
        {
            Path += "/home/";
            std::string User;
            CEngine::GetUsername(User);
            Path += User;
        }

        //Fixme : need to create folder : bug 5
        std::string Config(Path);
        Config += "/.scleaner/prefs.conf";

        std::ifstream File(Config.c_str());
        unsigned int Label;

        if(File.good())
        {
            while(1)
            {
                File >> Label;
                if(File.eof() == true)
                    break;
                std::string Folder;
                switch(Label)
                {
                    case eShowSplash:
                        File >> fShowSplash;
                        break;
                    case eFolderInc:
                        File >> Folder;
                        fFoldersList.push_back(Folder);
                        break;
                    case eFolderEx:
                        File >> Folder;
                        fExcludedFoldersList.push_back(Folder);
                        break;
                    case eShowToolbar:
                        File >> fShowToolbar;
                        break;
                    case eShowStatusbar:
                        File >> fShowStatusbar;
                        break;
                    case eDelete:
                        File >> fDelete;
                        break;
                    default:
                        continue;
                }
            }
        }
        else
        {
            //Default configuration
            fFoldersList.push_back("/home");
            fExcludedFoldersList.push_back(Path);
        }

        #if defined DEBUG
        std::cout << "[DBG] Loading pref : \n";
        std::cout << "[DBG] fShowSplash = " << fShowSplash << '\n';
        std::cout << "[DBG] fShowToolbar = " << fShowToolbar << '\n';
        std::cout << "[DBG] fShowStatusbar = " << fShowStatusbar << '\n';
        std::cout << "[DBG] fDelete = " << fDelete << '\n';
        #endif
    }


    CSettingsManager::~CSettingsManager()
    {
        std::string Path;

        if(CEngine::IsRoot())
        {
            Path += "/root";
        }
        else
        {
            Path += "/home/";
            std::string User;
            CEngine::GetUsername(User);
            Path += User;
        }

        std::string Config(Path);
        Config += "/.scleaner/prefs.conf";

        std::ofstream File(Config.c_str());

        //Debug
        #if defined DEBUG
        std::cout << "[DBG] Saving pref\n";
        std::cout << "[DBG] fShowSplash = " << fShowSplash << '\n';
        std::cout << "[DBG] fShowToolbar = " << fShowToolbar << '\n';
        std::cout << "[DBG] fShowStatusbar = " << fShowStatusbar << '\n';
        std::cout << "[DBG] fDelete = " << fDelete << '\n';
        #endif

        //Write splash screen
        File << eShowSplash << ' ' << fShowSplash << '\n';

        //Folders include in scan
        std::list<std::string>::iterator It;
        for(It = fFoldersList.begin(); It != fFoldersList.end(); ++It)
        {
            #if defined DEBUG
            std::cout << "[DBG] Adding :" << *It << '\n';
            #endif
            File << eFolderInc << ' ' << *It << '\n';
        }

        //Folders exclude from scan
        for(It = fExcludedFoldersList.begin(); It != fExcludedFoldersList.end(); ++It)
        {
            #if defined DEBUG
            std::cout << "[DBG] Excluding :" << *It << '\n';
            #endif
            File << eFolderEx << ' ' << *It << '\n';
        }

        //Show toolbar
        File << eShowToolbar << ' ' << fShowToolbar << '\n';

        //Show status bar
        File << eShowStatusbar << ' ' << fShowStatusbar << '\n';

        //Delete files after output plugin
        File << eDelete << ' ' << fDelete << '\n';
    }


    bool CSettingsManager::AddFolder(std::string dir, std::string& parent, eFoldersType type)
    {
        bool Ret = true;

        std::list<std::string>* FileList;

        switch(type)
        {
            case eFoldersInc:
                FileList = &fFoldersList;
                break;
            case eFoldersEx:
                FileList = &fExcludedFoldersList;
                break;
            default:
                FileList = 0;
                break;
        }

        //Search a parent folder:
        std::list<std::string>::iterator It;
        bool Clean = false;
        for(It = FileList->begin(); It != FileList->end(); ++It)
        {
            //If a parent is found
            if(dir.find(*It, 0) != std::string::npos)
            {
                parent = *It;
                Ret = false;
                break;
            }
            else
            {
                //If _dir is a parent :D
                if((*It).find(dir, 0) != std::string::npos)
                {
                    Clean = true;
                    break;
                }
            }
        }

        if(Clean)
        {
            It = FileList->begin();
            do
            {
                if((*It).find(dir, 0) != std::string::npos)
                {
                    std::list<std::string>::iterator It2erase = It;
                    ++It;
                    FileList->erase(It2erase);
                }
                else
                    ++It;
            }while(It != FileList->end());
        }

        if(Ret)
            FileList->push_back(dir);
        else
        {
            //If a parent folder is found, no need to add is child.
            #if defined DEBUG
            std::cerr << "[WRG] Parent folder found : " << (*It) << " no need to add " << dir << '\n';
            #endif
        }

        return Ret;
    }

    void CSettingsManager::DelFolder(const std::string dir, eFoldersType type)
    {
        std::list<std::string>::iterator It;
        std::list<std::string>* FileList;

        switch(type)
        {
            case eFoldersInc:
                FileList = &fFoldersList;
                break;
            case eFoldersEx:
                FileList = &fExcludedFoldersList;
                break;
            default:
                FileList = 0;
                break;
        }

        if(FileList != 0)
        {
            for(It = FileList->begin(); It != FileList->end(); ++It)
            {
                if((*It) == dir)
                {
                    FileList->erase(It);
                    break;
                }
            }
        }
    }
} //namespace Engine
