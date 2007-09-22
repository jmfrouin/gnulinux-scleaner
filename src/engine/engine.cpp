/*
Copyright (C) 2007 FROUIN Jean-Michel
------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------
Project : scleaner
------------------------------------------------------
$Date$
$Rev$
$Author$
------------------------------------------------------
*/

#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <interface/maininterface.h>
#include "engine.h"

CEngine::CEngine():
m_fl(0)
{
}

int CEngine::loadPlugins(const std::string& _path)
{
	int l_ret=0;
	//Plugins manager
	m_pfm = CPluginManager::Instance();
    l_ret = m_pfm->loadPlugins(_path);
	return l_ret;
}

bool CEngine::loadInterface()
{
	bool l_ret = false;

	CMainInterface* l_Main = 0;
	l_Main = new CMainInterface(NULL, wxID_ANY, wxT(NAME), SYMBOL_MAININTERFACE_POSITION, SYMBOL_MAININTERFACE_SIZE);
	if(l_Main)
    {
		l_Main->Show(true);
		l_ret = true;
	}

	return l_ret;
}

bool CEngine::isRoot()
{
	bool l_ret;
	if((getuid() != 0) || (geteuid() != 0))
	{
		l_ret = false;
	}
	else
	{
		l_ret = true;
	}
	return l_ret;
}

bool CEngine::getKernelVersion(std::string& _version)
{
	bool l_ret = false;
	utsname l_temp;
	if(uname(&l_temp) != 0)
	{
		std::cerr << "[ERR] CEngine::getKernelVersion error !\n";
	}
	else
	{
		_version += l_temp.release;
		
		l_ret = true;
	}

	return l_ret;
}

bool CEngine::callOutputPlugin(std::list<std::string>& _list, std::string& _name)
{
	bool l_ret = false;
	std::map<std::string, IOutPlugin*>* l_OutputPlugs;
	l_OutputPlugs = m_pfm->getOutputListPtr();
	IOutPlugin* l_plug = (*l_OutputPlugs)[_name];
	if(l_plug != 0)
	{
		l_plug->processFileList(_list);
		l_ret = true;
	}
	else
	{
		std::cout << "[WNG] : null" << '\n';
	}
	return l_ret;
}

int CEngine::FTW_callback(const char* _fpath, const struct stat* _stat, int _tflag, struct FTW* _ftwbuf)
{
	int l_ret = 0;

	//std::cout << (long long) _stat->st_size;
	//Check if it is a folder ?
	if (_stat->st_mode > 23420) 
	{
#if defined DEBUG
		std::cout << _fpath << '\n';
#endif
		CEngine::Instance()->GetList()->push_back(_fpath);
	}

    return l_ret;	// To tell nftw() to continue
}

bool CEngine::getFileList(std::list<std::string>& _fl, std::string _path, bool _recursive)
{
	bool l_ret = false;

	int l_flags = FTW_PHYS;
	m_fl = &_fl;

    nftw(_path.c_str(), FTW_callback, 20, l_flags);
	
	m_fl = 0;
	return l_ret;
}
/* vi:set ts=4: */
