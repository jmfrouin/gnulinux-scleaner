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

#include <fstream>
#include <sys/stat.h>
#include "engine.h"
#include "settings_manager.h"

namespace Engine
{
  CSettingsManager::CSettingsManager():
  fShowSplash(true), fShowToolbar(true), fShowStatusbar(true),
  fDelete(false), fSystemFiles(true), fRecursiveScan(true)
  {
    std::string Path;

    if(CEngine::IsRoot())
      Path += "/root";
    else
    {
      Path += "/home/";
      std::string User;
      CEngine::GetUsername(User);
      Path += User;
    }

    Path += "/.scleaner/";

    //Check that folder exist.
    struct stat Info;
    if(stat(Path.c_str(), &Info) == -1)
    {
      int Res = mkdir(Path.c_str(), 01777);
      #if defined DEBUG
      Log::CLog::Instance()->Log(__FILE__, __LINE__, Path);
      Log::CLog::Instance()->Log(__FILE__, __LINE__, " didn't exist need to created it \n");
      Log::CLog::Instance()->Log(__FILE__, __LINE__, "Creation :");
      if(!Res)
        Log::CLog::Instance()->Log(__FILE__, __LINE__, "OK\n");
      else
        Log::CLog::Instance()->Log(__FILE__, __LINE__, "KO\n");
      #endif
    }

    std::string Config(Path);
    Config += "prefs.conf";

    std::ifstream File(Config.c_str());
    unsigned int Label;

    if(File.good())
    {
      while(1)
      {
        File >> Label;
        if(File.eof())
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
          case eSystemFiles:
            File >> fSystemFiles;
            break;
          case eRecursiveScan:
            File >> fRecursiveScan;
            break;
          case ePerspective:
            File >> fPerspective;
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

    #if defined DEBUG && defined VERBOSE
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "Loading pref : \n");
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fShowSplash = ", fShowSplash, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fShowToolbar = ", fShowToolbar, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fShowStatusbar = ", fShowStatusbar, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fDelete = ", fDelete, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fSystemFiles = ", fSystemFiles, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fRecursiveScan = ", fRecursiveScan, true);
    #endif
  }

  CSettingsManager::~CSettingsManager()
  {
    std::string Path;

    if(CEngine::IsRoot())
      Path += "/root";
    else
    {
      Path += "/home/";
      std::string User;
      CEngine::GetUsername(User);
      Path += User;
    }
    Path += CONFFILE;

    //Debug
    #if defined DEBUG && defined VERBOSE
    Log::CLog::Instance()->Log(__FILE__, __LINE__, std::string("Saving pref"), true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fShowSplash = ", fShowSplash, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fShowToolbar = ", fShowToolbar, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fShowStatusbar = ", fShowStatusbar, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fDelete = ", fDelete, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fSystemFiles = ", fSystemFiles, true);
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fRecursiveScan = ", fRecursiveScan, true);
    #endif

    std::ofstream File(Path.c_str());

    //Write splash screen
    File << eShowSplash << ' ' << fShowSplash << '\n';

    //Folders include in scan
    std::list<std::string>::iterator It;
    for(It = fFoldersList.begin(); It != fFoldersList.end(); ++It)
    {
      #if defined DEBUG
      Log::CLog::Instance()->Log(__FILE__, __LINE__, "Adding :", *It, true);
      #endif
      File << eFolderInc << ' ' << *It << '\n';
    }

    //Folders exclude from scan
    for(It = fExcludedFoldersList.begin(); It != fExcludedFoldersList.end(); ++It)
    {
      #if defined DEBUG
      Log::CLog::Instance()->Log(__FILE__, __LINE__, "Excluding :", *It, true);
      #endif
      File << eFolderEx << ' ' << *It << '\n';
    }

    File << eShowToolbar << ' ' << fShowToolbar << '\n';
    File << eShowStatusbar << ' ' << fShowStatusbar << '\n';
    File << eDelete << ' ' << fDelete << '\n';
    File << eSystemFiles << ' ' << fSystemFiles << '\n';
    File << eRecursiveScan << ' ' << fRecursiveScan << '\n';
    File << ePerspective << ' ' << fPerspective << '\n';
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

    if(fRecursiveScan)
    {
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
          //If dir is a parent :D
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
    }

    if(Ret)
      FileList->push_back(dir);
    
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
}                                //namespace Engine
