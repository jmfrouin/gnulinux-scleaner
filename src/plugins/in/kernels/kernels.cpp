/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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
#include <apt-pkg/pkgcache.h>		//For pkgCache
#include <apt-pkg/sourcelist.h> 	//For pkgSourceList
#include <apt-pkg/pkgcachegen.h>	//For pkgMakeStatusCache
#include <apt-pkg/progress.h>		//OpProgress
#include <apt-pkg/init.h>			//For configuration
#include <apt-pkg/error.h>			//_error
#include <plugins/inplugin_initializer.h>
#include <leak/leak_detector.h>
#include "kernels.h"

Plugins::CPluginInitializerIn<CkernelsPlugin> g_kernels;

CkernelsPlugin::CkernelsPlugin():
m_Cache(0), m_SrcList(0), m_Map(0)
{
	setName("kernels");

   	if (pkgInitConfig(*_config) == false || pkgInitSystem(*_config,_system) == false)
   	{
		std::cerr << "[ERR] CkernelsPlugin() pkgInitConfig || pkgInitSystem\n";
	}

	if (_config->FindB("APT::Cache::Generate",true) == false)
    {
		m_Map = new MMap(*new FileFd(_config->FindFile("Dir::Cache::pkgcache"), FileFd::ReadOnly),MMap::Public|MMap::ReadOnly);
	}
	else
	{
		// Open the cache file
		m_SrcList = new pkgSourceList;
		m_SrcList->ReadMainList();
	
		// Generate it and map it
		OpProgress l_Prog;
		pkgMakeStatusCache(*m_SrcList, l_Prog, &m_Map, true);
	}

	if (_error->PendingError() == false)
    {
		m_Cache = new pkgCache(m_Map);
	}
	else
	{
		std::cerr << "[ERR] CkernelsPlugin(): Errors occured\n";
	}
}


CkernelsPlugin::~CkernelsPlugin()
{
	if(m_Map != 0)
	{
		delete m_Map;
	}
	if(m_Cache != 0)
	{
		delete m_Cache;
	}
}


void CkernelsPlugin::getDirectory(std::string& _path)
{
	_path = "/boot/";
}


void CkernelsPlugin::processFile(const std::string& _filename)
{
	if(_filename.find("vmlinuz", 0) != std::string::npos)
	{
		std::string l_res;
		if(Search(_filename, l_res))
		{
			m_fl.push_back(l_res);
		}
	}
}

bool CkernelsPlugin::Search(const std::string& _name, std::string& _result)
{
	bool l_ret = false;

	regex_t* l_pattern = new regex_t;

	std::string l_version = _name.substr(_name.find_first_of('-')+1, _name.length());
	std::string l_filename = "linux-image-" + l_version;

	if(regcomp(l_pattern, l_filename.c_str(), REG_EXTENDED | REG_ICASE | REG_NOSUB) != 0)
	{
		std::cerr << "Regex error !\n";
		regfree(l_pattern);
	}

   	for (pkgCache::PkgIterator l_it = m_Cache->PkgBegin(); l_it.end() == false; ++l_it)
   	{
		#if defined DEBUG
		std::cout << l_it.Name() << "=" << l_filename << '\n';
		#endif
	 	if (regexec(l_pattern,l_it.Name(),0,0,0) == 0)
		{
			_result = l_it.Name();
			#if defined DEBUG
			std::cout << _result << '\n';
			#endif
			l_ret = true;
			break;
		}
   	}

	//Did not add current kernel or computer won't works anymore ;)
	std::string l_currentKernelVersion;
	Engine::CEngine::getKernelVersion(l_currentKernelVersion);
      
	if(l_currentKernelVersion == l_version)
	{
		l_ret = false;
	}

	regfree(l_pattern);
   	return l_ret;
}


std::string CkernelsPlugin::Description()
{
	return "Find unused installed kernels";
}
/* vi:set ts=4: */
