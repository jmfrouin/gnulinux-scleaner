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
#include <sstream>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <mntent.h>
#include <sys/utsname.h>
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


bool CEngine::callOutputPlugin(std::list<std::string>& _list, std::string& _name, IProgressbar* _callback)
{
	bool l_ret = false;
	std::map<std::string, IOutPlugin*>* l_OutputPlugs;
	l_OutputPlugs = m_pfm->getOutputListPtr();
	IOutPlugin* l_plug = (*l_OutputPlugs)[_name];
	if(l_plug != 0)
	{
		l_plug->processFileList(_list, _callback);
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
	std::string l_path(_fpath);

	//Check if it is a folder ?
	if (_stat->st_mode > 23420)
	{
		//Pattern matching
		if(l_path.find(CEngine::Instance()->getPattern(), 0) != std::string::npos)
		{
			#if defined DEBUG
			std::cout << "[DBG] FTW_callback : " << l_path << '\n';
			#endif
			CEngine::Instance()->getList()->push_back(l_path);
		}
	}

	return l_ret;				 // To tell nftw() to continue
}


bool CEngine::getFileList(std::list<std::string>& _fl, const std::string& _path, const std::string& _pattern, bool _recursive)
{
	bool l_ret = false;

	int l_flags = FTW_PHYS;
	m_fl = &_fl;

	m_pattern = _pattern;

	if( nftw(_path.c_str(), FTW_callback, 20, l_flags) == 0)
	{
		l_ret = true;
	}

	m_fl = 0;
	return l_ret;
}


bool CEngine::getUsername(std::string& _username)
{
	bool l_ret = false;

	uid_t l_uid = geteuid();

	struct passwd* l_passwd = 0;
	l_passwd = getpwuid(l_uid);

	#if defined DEBUG
	std::cout << "[DBG] CEngine::getUsername UID: " << l_uid << '\n';
	#endif

	if (l_passwd)
	{
		_username = l_passwd->pw_name;
		#if defined DEBUG
		std::cout << "[DBG] CEngine::getUsername Username: " << _username << '\n';
		#endif
		l_ret = true;
	}
	else
	{
		l_ret = false;
	}

	return l_ret;
}


void CEngine::formatSize(double _size, std::string& _str)
{
	std::stringstream l_temp;

	if(_size > (1024*1024*1024))
	{
		l_temp << ROUND((_size / (1024*1024*1024))) << "G";
	}
	else
	{
		if(_size > (1024*1024))
		{
			l_temp << ROUND(_size / (1024*1024)) << "M";
		}
		else
		{
			if(_size > 1024)
			{
				l_temp << ROUND(_size / 1024) << "K";
			}
			else
			{
				if(_size == 0)
				{
					l_temp << "null size";
				}
				else
				{
					l_temp << _size;
				}
			}
		}
	}
	_str += l_temp.str();
}


double CEngine::getFreeSpace(const std::string& _path, std::string& _used, std::string& _free, std::string& _total)
{
	double l_ret = 0;
	
	FILE* l_mountTable;
	struct mntent* l_mountEntry;

	l_mountTable = setmntent(FSTAB, "r");

	if (l_mountTable == 0) 
	{
		perror(FSTAB);
	}
	else
	{
		double l_free, l_used, l_total;
		l_free = l_used = l_total = 0;

		while ((l_mountEntry = getmntent(l_mountTable))) 
		{
			struct statfs l_stat;
			double l_blocks_used;
			double l_blocks_percent_used;

			if (statfs(l_mountEntry->mnt_dir, &l_stat) != 0) 
			{
				perror(l_mountEntry->mnt_dir);
			}
			else
			{
				if (l_stat.f_blocks > 0) 
				{
					l_blocks_used = l_stat.f_blocks - l_stat.f_bfree;
					l_blocks_percent_used = (double)(l_blocks_used * 100.0 / (l_blocks_used + l_stat.f_bavail) + 0.5);
					if (strcmp(l_mountEntry->mnt_fsname, "/dev/root") == 0) 
					{
						/* Adjusts l_mountEntry->mnt_fsname to be the real root l_mountEntry->mnt_fsname,
						 * or leaves l_mountEntry->mnt_fsname alone if it can't find it */
						//find_real_root_l_mountEntry->mnt_fsname_name( l_mountEntry->mnt_fsname);
					}
					else
					{
						l_free += l_stat.f_bavail*(l_stat.f_bsize);
						l_used += (l_stat.f_blocks - l_stat.f_bfree)*(l_stat.f_bsize);
						l_total += l_stat.f_blocks*(l_stat.f_bsize); 
					}
				}
			}
		}

			std::string l_size;
			formatSize(l_free, l_size);
			_free += l_size;
			l_size.clear();
			formatSize(l_total, l_size);
			_total += l_size;
			l_size.clear();
			formatSize(l_used, l_size);
			_used += l_size;
			endmntent(l_mountTable);
	}

	return l_ret;
}

/* vi:set ts=4: */
