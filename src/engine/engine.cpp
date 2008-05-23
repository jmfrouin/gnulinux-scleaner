/**
 * This file is part of scleaner project.

 * Visit scleaner website : http://www.scleaner.fr
 * Copyright (C) 2000 Yann Guidon <whygee@f-cpu.org>
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

#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for lstat() */
#include <stdlib.h> /* for malloc() */
#include <sstream>
#include <fstream>
#include <pwd.h>
#include <dirent.h>
#include <mntent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <sys/utsname.h>
#include "interface/maininterface.h"
#include "settings_manager.h"
#include "dpkg-db.h"
#include "engine.h"

namespace Engine
{
    CEngine::CEngine():
    fAvailableInputPlugs(0), fOutputPlugs(0), fRootPlugin(0), fAsRoot(false),
    fCallback(0), fCount(0), fSelInPlugins(false)
    {
        //Initialisation
        fAvailableInputPlugs = Plugins::CPluginManager::Instance()->GetInputListPtr();
        fOutputPlugs = Plugins::CPluginManager::Instance()->GetOutputListPtr();
        fSettings = CSettingsManager::Instance();
    }

    CEngine::~CEngine()
    {
        #if defined DEBUG
        std::cout << "[DBG] ~CEngine\n";
        std::list<std::string>::iterator It;
        std::cout << "[DBG] fUnselectedInputPlugs : \n";
        for(It = fUnselectedInputPlugs.begin(); It != fUnselectedInputPlugs.end(); ++It)
            std::cout << "[DBG]" << *It << '\n';
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

        GUI::CMainInterface* Main = 0;
        Main = new GUI::CMainInterface(NULL, wxID_ANY, wxT(NAME), SYMBOL_MAININTERFACE_POSITION, SYMBOL_MAININTERFACE_SIZE);
        if(Main)
        {
            Main->Show(true);
            Ret = true;
        }

        return Ret;
    }


    bool CEngine::IsRoot()
    {
        bool Ret;
        if(getuid() || geteuid())
            Ret = false;
        else
            Ret = true;
        return Ret;
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
        std::cout << i8n("[DBG] CEngine::getUsername UID: ") << Uid << '\n';
        #endif

        if (Passwd)
        {
            username = Passwd->pw_name;
            #if defined DEBUG
            std::cout << i8n("[DBG] CEngine::getUsername Username: ") << username << '\n';
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
                        Temp << i8n("null size");
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

        fCallback = callback;


        //If launch as root
        if(IsRoot())
        {
            std::map<std::string, Plugins::IInPlugin*>* Input = GetSelectedInputPlugs(true);
            std::map<std::string, Plugins::IInPlugin*>::iterator It;
            for(It = Input->begin(); It != Input->end(); ++It)
            {
                if(It->second->Type() == Plugins::IPlugin::eRootByFolderInput)
                {
                    std::string Dir;
                    (It->second)->GetDirectory(Dir);
                    bool Continue = callback->UpdateProgress(Dir, true);
                    if(!Continue)
                      break;
                    ScanDirectory(Dir, true, It->second);
                }
            }
        }

        //In both case
        std::list<std::string>* FoldersList = fSettings->GetFoldersListPtr();
        std::list<std::string>::iterator ItFolders;
        for(ItFolders = FoldersList->begin(); ItFolders != FoldersList->end(); ++ItFolders)
        {
            //#if defined DEBUG
            std::cout << i8n("[DBG] CEngine::scanDisk Path : ") << *ItFolders << '\n';
            //#endif
            if(callback != 0)
            {
                bool Continue = callback->UpdateProgress(*ItFolders, true);
                if(!Continue)
                  break;
            }
            ScanDirectory(*ItFolders);
        }
        return Ret;
    }

    int CEngine::FTWCallback(const char* fpath, const struct stat* statp, int tflag, struct FTW* ftwbuf)
    {
        int Ret = 0;
        std::string Path(fpath);

        CEngine* Engine = CEngine::Instance();

        std::list<std::string>* ExcludeFoldersList = Engine->fSettings->GetExcludedFoldersListPtr();
        std::list<std::string>::iterator ItExcludeFolders;

        for(ItExcludeFolders = ExcludeFoldersList->begin(); ItExcludeFolders != ExcludeFoldersList->end(); ++ItExcludeFolders)
        {
            if(Path.find(*ItExcludeFolders) != std::string::npos)
            {
                #if defined DEBUG && defined VERBOSE
                std::cout << "Skip " << Path << " because I found " << *ItExcludeFolders << '\n';
                #endif
                return Ret;                // To tell nftw() to continue
            }
        }

        IProgressbar* Prog = Engine->GetCallback();

        //Update progress bar to show progression :
        if(Prog)
        {
            if(Engine->GetCount() > 9)
            {
                bool Continue = Prog->UpdateProgress(Path, true);
                if(!Continue)
                    return !Ret;
                Engine->SetCount(0);
            }
            else
                Engine->SetCount(Engine->GetCount()+1);
        }

        #if defined DEBUG && defined VERBOSE
        std::cout << i8n("[DBG] FTW_callback : ") << Path << '\n';
        #endif

        if(Engine->AsRoot())
        {
            Plugins::IInPlugin* Root = 0;
            Root = Engine->RootPlugin();
            if(Root)
            {
                struct stat Info;
                //Try to stat file.
                if(stat(Path.c_str(), &Info) == -1)
                    std::cout << i8n("[ERR] : Cannot stat ") << Path << '\n';
                else
                    if(Info.st_size != 0)
                        Root->ProcessFile(Path);
            }
        }
        else
        {
            std::map<std::string, Plugins::IInPlugin*>* Input = CEngine::Instance()->GetPluginManager()->GetInputListPtr();
            std::map<std::string, Plugins::IInPlugin*>::iterator It;
            for(It = Input->begin(); It != Input->end(); ++It)
            {
                if( (((*It).second)->Type() != Plugins::IPlugin::eRootInput) && (((*It).second)->Type() != Plugins::IPlugin::eRootByFolderInput))
                {
                    struct stat Info;
                    //Try to stat file.
                    if(stat(Path.c_str(), &Info) == -1)
                        std::cout << i8n("[ERR] : Cannot stat ") << Path << '\n';
                    else
                        if(Info.st_size == 0)
                            if(It->second->GrabNullFile())
                                It->second->ProcessFile(Path);
                        else
                            if(!It->second->GrabNullFile())
                                It->second->ProcessFile(Path);
                }
            }
        }
        return Ret;                // To tell nftw() to continue
    }

    bool CEngine::ScanDirectory(const std::string& path, bool asroot, Plugins::IInPlugin* rootplugin, bool recursive)
    {
        bool Ret = false;

        int Flags = FTW_PHYS;

        if(asroot)
        {
            fAsRoot = true;
            fRootPlugin = rootplugin;
        }

        if( nftw(path.c_str(), FTWCallback, 20, Flags) == 0)
            Ret = true;

        fAsRoot = false;

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
        #if defined DEBUG && defined VERBOSE
        std::cout << "[DBG] calcCRC32 : CRC32 for " << filename << " = " << crc << '\n';
        #endif
    }


    void CEngine::AddFileInfo(const std::string& file, unsigned long crc)
    {
        #if defined DEBUG && defined VERBOSE
        std::cout << "[DBG] addFileInfo : " << file << " " << crc << '\n';
        #endif
        fInfos.insert(make_pair(file, crc));
    }


    int CEngine::DetectDuplicates()
    {
        int Ret = 0;

        #if defined DEBUG
        std::cout << "[DBG] detectDuplicates : Detect duplicate " << std::endl;
        #endif

        std::map<std::string, unsigned long>::iterator It;

        for(It = fInfos.begin(); It != fInfos.end(); ++It)
        {
            if(It->second != 0)
            {
                std::map<std::string, unsigned long>::iterator It2 = It;
                for(++It2; It2 != fInfos.end(); ++It2)
                {
                    if(It->second == It2->second)
                        if(fDuplicatesFilesList[It->second] == "")
                        {
                            fDuplicatesFilesList.insert(make_pair(It->second, It->first));
                            Ret++;
                        }
                }
            }
        }
        std::cout << "Founded " << Ret << " duplicates files" << std::endl;

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
                        std::cout << "[DBG] " << *It2 << " is unselected !!\n";
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

} //namespace Engine
/* vi:set ts=4: */
