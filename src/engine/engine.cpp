/**
 * This file is part of scleaner project.

 * Visit scleaner website : http://www.scleaner.org
 * Copyright (C) 2000 Yann Guidon <whygee@f-cpu.org>
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

#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>              /* for lstat() */
#include <stdlib.h>              /* for malloc() */
#include <sstream>
#include <fstream>
#include <pwd.h>
#include <dirent.h>
#include <mntent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <sys/utsname.h>
#include <plugins/in/in_plugin.h>
#include <plugins/in/input_plugin.h>
#include <plugins/in/thread_plugin.h>
#include <tools/timer.h>
#include <log/log.h>
#include "settings_manager.h"
#include "dpkg-db.h"
#include "engine.h"

namespace Engine
{
  CEngine::CEngine():
  fInterface(0), fAvailableInputPlugs(0), fOutputPlugs(0), fCount(0), fSelInPlugins(false)
  {
    //Initialisation
    fAvailableInputPlugs = Plugins::CPluginManager::Instance()->GetInputListPtr();
    fOutputPlugs = Plugins::CPluginManager::Instance()->GetOutputListPtr();
    fSettings = CSettingsManager::Instance();
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "[DBG] CEngine started", "", true);
  }

  CEngine::~CEngine()
  {
    #if defined DEBUG
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "[DBG] ~CEngine\n");
    std::list<std::string>::iterator It;
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "fUnselectedInputPlugs : \n");
    for(It = fUnselectedInputPlugs.begin(); It != fUnselectedInputPlugs.end(); ++It)
      Log::CLog::Instance()->Log(__FILE__, __LINE__,  *It);
    #endif
  }

  int CEngine::LoadPlugins(const std::string& path)
  {
    //Plugins manager
    fPFM = Plugins::CPluginManager::Instance();
    return fPFM->LoadPlugins(path);
  }

  bool CEngine::LoadInterface()
  {
    bool Ret = false;

    fInterface = new GUI::CMainInterface(NULL, wxID_ANY, wxT(NAME), SYMBOL_POSITION, SYMBOL_INTERFACE_SIZE);
    if(fInterface)
    {
      fInterface->Show(true);
      Ret = true;
    }

    return Ret;
  }

  bool CEngine::IsRoot()
  {
    if(getuid() || geteuid())
      return false;
    else
      return true;
  }

  bool CEngine::GetKernelVersion(std::string& version)
  {
    bool Ret = false;
    utsname Temp;
    if(uname(&Temp) != 0)
      std::cerr << i8n("[ERR] CEngine::getKernelVersion error !\n");
    else
    {
      version += Temp.release;
      Ret = true;
    }

    return Ret;
  }

  bool CEngine::CallOutputPlugin(std::list<std::string>& list, std::string& name, const std::string& path, IProgressbar* callback)
  {
    bool Ret = false;
    std::cout << "CallOutputPlugin, name : " << name << '\n';
    std::map<std::string, Plugins::IOutPlugin*>* OutputPlugs;
    OutputPlugs = fPFM->GetOutputListPtr();
    Plugins::IOutPlugin* Plug = (*OutputPlugs)[name];
    if(Plug)
    {
      Plug->ProcessFileList(list, path, callback);
      Ret = true;
    }
    else
      std::cout << i8n("[WNG] : null") << '\n';
    return Ret;
  }

  bool CEngine::GetUsername(std::string& username)
  {
    bool Ret = false;

    uid_t Uid = geteuid();

    struct passwd* Passwd = 0;
    Passwd = getpwuid(Uid);

    #if defined DEBUG
    Log::CLog::Instance()->Log(__FILE__, __LINE__, i8n("[DBG] CEngine::getUsername UID: "), Uid, true);
    #endif

    if (Passwd)
    {
      username = Passwd->pw_name;
      #if defined DEBUG
      Log::CLog::Instance()->Log(__FILE__, __LINE__, i8n("[DBG] CEngine::getUsername Username: "), username, true);
      #endif
      Ret = true;
    }

    return Ret;
  }

  void CEngine::FormatSize(double size, std::string& str)
  {
    std::stringstream Temp;

    if(size > (1<<30))
      Temp << ROUND((size / (1<<30))) << i8n("GB");
    else
    if(size > (1<<20))
      Temp << ROUND(size / (1<<20)) << i8n("MB");
    else
    if(size > (1<<10))
      Temp << ROUND(size / (1<<10)) << i8n("KB");
    else
    if(!size)
      Temp << i8n("NULL");
    else
      Temp << size;
    str += Temp.str();
  }

  double CEngine::GetFreeSpace(const std::string& path, std::string& usedspace, std::string& freespace, std::string& total)
  {
    double Ret = 0;

    FILE* MountTable;
    struct mntent* MountEntry;

    MountTable = setmntent(FSTAB, "r");

    if (!MountTable)
      perror(FSTAB);
    else
    {
      double Free, Used, Total;
      Free = Used = Total = 0;

      while ((MountEntry = getmntent(MountTable)))
      {
        struct statfs Stat;
        double BlocksUsed;
        double BlocksPercentUsed;

        if (statfs(MountEntry->mnt_dir, &Stat) != 0)
          perror(MountEntry->mnt_dir);
        else
        {
          if (Stat.f_blocks > 0)
          {
            BlocksUsed = Stat.f_blocks - Stat.f_bfree;
            BlocksPercentUsed = (double)(BlocksUsed * 100.0 / (BlocksUsed + Stat.f_bavail) + 0.5);
            if (strcmp(MountEntry->mnt_fsname, "/dev/root") == 0)
            {
              /* Adjusts l_mountEntry->mnt_fsname to be the real root l_mountEntry->mnt_fsname,
               * or leaves l_mountEntry->mnt_fsname alone if it can't find it */
              //find_real_root_l_mountEntry->mnt_fsname_name( l_mountEntry->mnt_fsname);
            }
            else
            {
              Free += Stat.f_bavail*(Stat.f_bsize);
              Used += (Stat.f_blocks - Stat.f_bfree)*(Stat.f_bsize);
              Total += Stat.f_blocks*(Stat.f_bsize);
            }
          }
        }
      }

      std::string Size;
      FormatSize(Free, Size);
      freespace += Size;
      Size.clear();
      FormatSize(Total, Size);
      total += Size;
      Size.clear();
      FormatSize(Used, Size);
      usedspace += Size;
      endmntent(MountTable);
    }

    return Ret;
  }

  bool CEngine::ScanDisk(IProgressbar* callback)
  {
    bool Ret = false;

    //First launch threadable plugin
    std::map<std::string, Plugins::IInPlugin*>* Input = GetSelectedInputPlugs(true);
    std::map<std::string, Plugins::IInPlugin*>::iterator It;
    for(It = Input->begin(); It != Input->end(); ++It)
    {
      if( (It->second->Type() == Plugins::IPlugin::eThreadableInput) ||
        (IsRoot() && It->second->Type() == Plugins::IPlugin::eRootThreadableInput))
      {
        Plugins::IThreadPlugin* ThreadablePlugin = (Plugins::IThreadPlugin*)It->second;
        std::cout << ROUGE << ThreadablePlugin->GetName() << '\n' << STOP;
        ThreadablePlugin->Start();
        //Threads infos :
        std::cout << VERT << "Thread : " << Tools::IThread::GetCount() << " / " << Tools::IThread::GetMax() << '\n' << STOP;
      }
    }

    Tools::CTimer Timer;
    PrepareFilesList(callback);
    Timer.Snap();

    std::cout << "After PrepareFilesList \n";

    int Total=0;
    //Then give each files to plugins
    std::list<std::string>::iterator It2;
    int Size = fFilesList.size();
    for(It2=fFilesList.begin(); It2!=fFilesList.end(); It2++)
    {
      //Update progress bar to show progression :
      if(fCount > 9)
      {
       if(callback)
       {
         bool Continue = callback->UpdateProgress(*It2, false, (Total++*100)/Size);
         if(!Continue)
           break;
       }
       fCount=0;
      }
      else
      {  
       fCount++;
       Total++;
      }

      //Give it to each plugins
      std::map<std::string, Plugins::IInPlugin*>* Input = fPFM->GetInputListPtr();
      std::map<std::string, Plugins::IInPlugin*>::iterator It;
      for(It = Input->begin(); It != Input->end(); ++It)
      {
        Plugins::IInputPlugin* Plug = (Plugins::IInputPlugin*)It->second;
        if( Plug->Type() == Plugins::IPlugin::eUserInput)
        {
          struct stat Info;
          //Try to stat file.
          if(stat(It2->c_str(), &Info) == -1)
            std::cout << i8n("[ERR] : Cannot stat ") << *It2 << '\n';
          else
          {
            if(!Info.st_size)
            {
              if(Plug->GrabNullFile())
                Plug->ProcessFile(*It2);
            }
            else
              Plug->ProcessFile(*It2);
          }
        }
      }
    }

    //Then launch eRootInput plugins 
    if(IsRoot())
    {
      std::map<std::string, Plugins::IInPlugin*>* Input = GetSelectedInputPlugs(true);
      std::map<std::string, Plugins::IInPlugin*>::iterator It;
      for(It = Input->begin(); It != Input->end(); ++It)
      {
        if(It->second->Type() == Plugins::IPlugin::eRootInput)
        {
          std::string Dir;
          Plugins::IInputPlugin* Plug = (Plugins::IInputPlugin*)It->second;
          Plug->GetDirectory(Dir);
          
          struct stat Stat;
          //Try to stat folder.
          if(stat(Dir.c_str(), &Stat) == -1)
            std::cout << i8n("[ERR] : Cannot stat ") << Dir << '\n';
          else
          {
             if(S_ISDIR(Stat.st_mode))
            {
              struct dirent** NameList;
              int Nb = scandir(Dir.c_str(), &NameList, 0, alphasort);
              if(Nb != -1)               //Fix Bug 4 : If no error append.
              {
                while (Nb-- > 0)
                {
                  std::string File(Dir);
                  File += NameList[Nb]->d_name;
                  std::cout << File << std::endl;
                  Plug->ProcessFile(File);
                  bool Continue = callback->UpdateProgress(Dir, true);
                  free(NameList[Nb]);
                }
                free(NameList);
              }
            }
          }
        }
      }
    }


    //Wait end of threadable plugins
    std::cout << ROUGE << "Waiting end of threadable plugins : \n" << STOP;
    for(It = Input->begin(); It != Input->end(); ++It)
    {
      if(It->second->Type() == Plugins::IPlugin::eThreadableInput)
      {
        Plugins::IThreadPlugin* ThreadablePlugin = (Plugins::IThreadPlugin*)It->second;
        std::cout << ThreadablePlugin->GetName() << ": ";
        ThreadablePlugin->Join();
        std::cout << VERT << "STOPPED" << '\n' << STOP;
      }
    }
    return Ret;
  }

  void CEngine::GetTimestamp(std::string& str)
  {
    time_t Tm;
    struct tm Time;

    time(&Tm);
    memcpy(&Time, localtime(&Tm), sizeof(Time));

    //Append date: YYYYMMDD
    std::stringstream Temp;

    //Append year
    Temp << 1900 + Time.tm_year;

    //Append month
    if(Time.tm_mon + 1 < 10)
      Temp << 0 << Time.tm_mon + 1;
    else
      Temp << Time.tm_mon + 1;

    //Append day
    if(Time.tm_mday < 10)
      Temp << 0 << Time.tm_mday;
    else
      Temp << Time.tm_mday;

    Temp << "_";

    //Append hour
    if(Time.tm_hour < 10)
      Temp << 0 << Time.tm_hour;
    else
      Temp << Time.tm_hour;

    //Append minute
    if(Time.tm_min < 10)
      Temp << 0 << Time.tm_min;
    else
      Temp << Time.tm_min;

    //Append second
    if(Time.tm_sec < 10)
      Temp << 0 << Time.tm_sec;
    else
      Temp << Time.tm_sec;

    str += Temp.str();

    #if defined DEBUG
    std::cout << i8n("[DBG] CEngine::getTimestamp Timestamp: ") << str << '\n';
    #endif
  }

  void CEngine::GetCRCTable(std::vector<unsigned long>& table)
  {
    unsigned long R;
    table.clear();
    for(int i=0; i<256; ++i)
    {
      R = i;
      for(int j=0; j<8; ++j)
      {
        if ( R & 1 )
          R = (R >> 1) ^ CRC_POLY_REV;
        else
          R >>= 1;
      }
      table.push_back(R);
    }
  }

  void CEngine::CalcCRC32(const std::string& filename, unsigned long& crc)
  {
    std::ifstream In(filename.c_str(), std::ios::in | std::ios::binary);

    //Push seed.
    crc = 0xffffffff;

    if(!In.good())
      std::cerr << i8n("[ERR] Error, cannot read ") << filename << " during calcCRC32" << '\n';
    else
    {
      char Char;
      std::vector<unsigned long> Table;
      GetCRCTable(Table);
      while(In.get(Char))
      {
        unsigned int Pos;
        Pos = (crc & 255) ^ Char;
        crc = Table[Pos] ^ (crc >> 8);
      }
    }
    In.close();
  }

  void CEngine::AddFileInfo(const std::string& file, unsigned long crc)
  {
    fInfos.insert(make_pair(file, crc));
  }

  int CEngine::DetectDuplicates()
  {
    int Ret = 0;

    #if defined DEBUG
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "detectDuplicates : Detect duplicate\n");
    #endif

    std::map<std::string, unsigned long>::iterator It;

    for(It = fInfos.begin(); It != fInfos.end(); ++It)
    {
      if(It->second)
      {
        std::map<std::string, unsigned long>::iterator It2 = It;
        for(++It2; It2 != fInfos.end(); ++It2)
        {
          if((It->second == It2->second))
          {
            fDuplicatesCRC.insert(It->second);
            Ret++;
          }
        }
      }
    }
    /*
    Display duplicates
    */
    //std::cout << "Founded " << fDuplicatesCRC.size() << " duplicates CRC" << '\n';
    //std::map<unsigned long, std::string>::iterator It3;
    /*std::set<unsigned long>::iterator It3;
    for(It3 = fDuplicatesCRC.begin(); It3 != fDuplicatesCRC.end(); ++It3)
      std::cout << *It3 << '\n';*/
    return Ret;
  }

  int CEngine::FindPackage(const std::string& name)
  {
    int Ret = 0;

    //struct pkginfo** l_p = 0;
    //pointerp= bins + (hash(name) % (BINS));
    //while (*pointerp && strcasecmp((*pointerp)->name,name))
    //  pointerp= &(*pointerp)->next;
    //if (*pointerp) { free(name); return *pointerp; }

    return Ret;
  }

  std::map<std::string, Plugins::IInPlugin*>* CEngine::GetSelectedInputPlugs(bool refresh)
  {
    if(refresh || !fSelInPlugins)
    {
      //First clear the map
      fSelectedInputPlugs.clear();

      //For each available plugin
      std::map<std::string, Plugins::IInPlugin*>::iterator It;
      for(It = fAvailableInputPlugs->begin(); It != fAvailableInputPlugs->end(); ++It)
      {
        bool Unsel = false;
        //If it is no unselected
        std::list<std::string>::iterator It2;
        for(It2 = fUnselectedInputPlugs.begin(); It2 != fUnselectedInputPlugs.end(); ++It2)
        {
          if((*It2) == (It->first))
          {
            Unsel = true;

            #if defined DEBUG && defined VERBOSE
            Log::CLog::Instance()->Log(__FILE__, __LINE__, *It2, " is unselected !!\n");
            #endif

            break;
          }
        }

        if(!Unsel)
          fSelectedInputPlugs.insert(make_pair(It->first, It->second));
      }
      fSelInPlugins = true;
    }
    return &fSelectedInputPlugs;
  }

  void CEngine::PROCInfo(const std::string& pattern, const std::string& file, std::string& str)
  {
    std::ifstream File(file.c_str(), std::ios::in);
    std::string Line;
    if(File.good())
    {
      while(1)
      {
        if(File.eof())
          break;
        getline(File, Line);
        unsigned int Pos = Line.find(pattern);
        if(Pos != std::string::npos)
        {
          Pos = Line.find(':');
          if(Pos != std::string::npos)
          {
            Pos += 2;
            str += Line.substr(Pos, Line.length());
            break;
          }
        }
      }
      File.close();
    }
  }

  bool CEngine::ScanDir(const std::string& filename, IProgressbar* callback)
  {
    bool Stop = false;
    struct dirent** NameList;
    int Nb = scandir(filename.c_str(), &NameList, 0, alphasort);
    if(Nb != -1) //Fix Bug 4 : If no error append.
    {
      while (Nb-- > 0)
      {
        if(!Stop)
        {
          struct stat Stat;
          std::string Temp(filename);
          Temp += "/";
          Temp += NameList[Nb]->d_name;
          std::string Dir(NameList[Nb]->d_name);
          if(Dir.length() <= 2)
              continue;
          if(stat(Temp.c_str(), &Stat) == -1)
              std::cout << "[ERR] : Cannot stat " << Temp << '\n';
          else
              if(S_ISDIR(Stat.st_mode))
              {      
                if(fSettings->GetRecursiveScan())
                {
                  std::list<std::string>* ExcludeFoldersList = fSettings->GetExcludedFoldersListPtr();
                  std::list<std::string>::iterator ItExcludeFolders;
                  
                  bool Ex = false;
                  for(ItExcludeFolders = ExcludeFoldersList->begin(); ItExcludeFolders != ExcludeFoldersList->end(); ++ItExcludeFolders)
                  {
                    if(Temp.find(*ItExcludeFolders) != std::string::npos)
                    {  
                      Ex = true;
                      break;
                    }
                  }

                  if(!Ex)
                  {
                    if(fSettings->GetSystemFiles()) //Scan all
                    {  
                      if(!ScanDir(Temp.c_str(), callback))
                        Stop = true;
                    }
                    else //Didn't scan folders
                    {
                      std::string Filename(Temp.substr(Temp.find_last_of('/')+1, Temp.length()));
                      if(Filename.find('.',0))
                        if(!ScanDir(Temp.c_str(), callback))
                          Stop = true;
                    }
                  }
                }
              }
              else
              {
                if(fSettings->GetSystemFiles()) //Add all
                  fFilesList.push_back(Temp);
                else //Exclude system files
                {
                  std::string Filename(Temp.substr(Temp.find_last_of('/')+1, Temp.length()));
                  if(Filename.find('.',0))
                    fFilesList.push_back(Temp);
                }
              }
          if(callback && !Stop)
          {  
            bool Continue = callback->UpdateProgress(Temp, true);
            if(!Continue)
              Stop = true;
          }
        }
        free(NameList[Nb]);
      }
      free(NameList);
    }
    if(Stop)
      return false;
    else
      return true;
  }

  void CEngine::PrepareFilesList(IProgressbar* callback)
  {
    //Prepare folders list
    fFilesList.clear();

    //First add users' folders
    std::list<std::string>* FoldersList = fSettings->GetFoldersListPtr();
    std::list<std::string>::iterator ItFolders;
    for(ItFolders = FoldersList->begin(); ItFolders != FoldersList->end(); ++ItFolders)
    {
      if(!ScanDir(*ItFolders, callback))
        break;
    } 
  }
}                                //namespace Engine
/* vi:set ts=4: */
