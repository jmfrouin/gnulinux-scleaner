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
#include <sys/utsname.h>
#include <string>
#include <regex.h>
#include <apt-pkg/pkgcache.h>       //For pkgCache
#include <apt-pkg/sourcelist.h>     //For pkgSourceList
#include <apt-pkg/pkgcachegen.h>    //For pkgMakeStatusCache
#include <apt-pkg/progress.h>       //OpProgress
#include <apt-pkg/init.h>           //For configuration
#include <apt-pkg/error.h>          //_error
#include <inplugin_initializer.h>
#include <leak/leak_detector.h>
#include "kernels.h"

Plugins::CPluginInitializerIn<CkernelsPlugin> gKernels;

CkernelsPlugin::CkernelsPlugin():
fCache(0), fSrcList(0), fMap(0)
{
    SetName("kernels");

    if (!pkgInitConfig(*_config) || !pkgInitSystem(*_config,_system))
        std::cerr << "[ERR] CkernelsPlugin() pkgInitConfig || pkgInitSystem\n";

    if (!(_config->FindB("APT::Cache::Generate",true)))
        fMap = new MMap(*new FileFd(_config->FindFile("Dir::Cache::pkgcache"), FileFd::ReadOnly),MMap::Public|MMap::ReadOnly);
    else
    {
        // Open the cache file
        fSrcList = new pkgSourceList;
        fSrcList->ReadMainList();

        // Generate it and map it
        OpProgress Prog;
        pkgMakeStatusCache(*fSrcList, Prog, &fMap, true);
    }

    if (!_error->PendingError())
        fCache = new pkgCache(fMap);
    else
        std::cerr << "[ERR] CkernelsPlugin(): Errors occured\n";
}


CkernelsPlugin::~CkernelsPlugin()
{
    if(fMap)
        delete fMap;
    if(fCache)
        delete fCache;
}


void CkernelsPlugin::GetDirectory(std::string& path)
{
    path = "/boot/";
}


void CkernelsPlugin::ProcessFile(const std::string& filename)
{
    if(filename.find("vmlinuz", 0) != std::string::npos)
    {
        std::string Res;
        if(Search(filename, Res))
            fFL.push_back(Res);
    }
}

bool CkernelsPlugin::Search(const std::string& Name, std::string& Result)
{
    bool Ret = false;

    regex_t* Pattern = new regex_t;

    std::string Version = Name.substr(Name.find_first_of('-')+1, Name.length());
    std::string Filename = "linux-image-" + Version;

    if(regcomp(Pattern, Filename.c_str(), REG_EXTENDED | REG_ICASE | REG_NOSUB))
    {
        std::cerr << "Regex error !\n";
        regfree(Pattern);
    }

    for (pkgCache::PkgIterator It = fCache->PkgBegin(); It.end() == false; ++It)
    {
        #if defined DEBUG
        std::cout << It.Name() << "=" << Filename << '\n';
        #endif
        if (!regexec(Pattern,It.Name(),0,0,0))
        {
            Result = It.Name();
            #if defined DEBUG
            std::cout << Result << '\n';
            #endif
            Ret = true;
            break;
        }
    }

    //Did not add current kernel or computer won't works anymore ;)
    std::string CurrentKernelVersion;
    Engine::CEngine::GetKernelVersion(CurrentKernelVersion);

    if(CurrentKernelVersion == Version)
        Ret = false;

    regfree(Pattern);
    return Ret;
}


std::string CkernelsPlugin::Description()
{
    return "Find unused installed kernels";
}
/* vi:set ts=4: */
