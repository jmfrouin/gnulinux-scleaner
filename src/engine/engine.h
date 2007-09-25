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

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <string>
#include <tools/smart_pointer.h>
#include <tools/singleton.h>
#include <plugins/plugin_manager.h>
#include "iprogress.h"

/*!
*@brief Manage all operations
*/
class CEngine: public CSmartCpt, public TSingleton<CEngine>
{
	public:
		/*!
		*@brief ctor
		*/
		CEngine();
	
		/*!
		*@brief dtor
		*/
		~CEngine(){}
	
	public:
        /*!
         *@brief Call load plugins in PluginManager.
         *@param path The folder location.
         *@return Number of plugins founded.
         */
        int loadPlugins (const std::string& path);

		/*!
		*@brief Load GFX interface build on wxWidgets
		*@return true is everything is OK, false otherwise.
		*/
		bool loadInterface();

		/*!
		*@brief Detect if launch as root
		*/
		bool isRoot();

		/*!
		*@brief Detect kernel version
		*/
		bool getKernelVersion(std::string& _version);

		/*!
		*@brief callOutputPlugins with a list of files
		*@param _list A files list.
		*@param _name Name of plugin.
		*@param _callback For progress bar.
		*@return true on success, false otherwise.
		*@todo Implement errors code.
		*/
		bool callOutputPlugin(std::list<std::string>& _list, std::string& _name, IProgressbar* _callback);
	
		/*!
		*@brief Replace wxDir usage.
		*@param _fl The files list to fill.
		*@param _path Where retrieve file list.
		*@param _pattern Apply _pattern before adding file to the files list.
		*@param _recursive If true, enter subfolders.
		*@return true on success, false otherwise.
		*/
		bool getFileList(std::list<std::string>& _fl, const std::string& _path, const std::string& _pattern, bool _recursive = true);

		/*!
		*@brief Callback : man ftw.
		*@param _fpath Directory.
		*@param _stat Where retrieve file list.
		*@param _tflag Flags.
		*@param _ftwbuf the TFW buffer.
		*@return true on success, false otherwise.
		*/
		static int FTW_callback(const char* _fpath, const struct stat* _stat, int _tflag, struct FTW* _ftwbuf);

		/*!
		*@brief Retrieve username.
		*@param _username The std::string to fill.
		*@return true on success, false otherwise.
		*/
		bool getUsername(std::string& _username);

		/*!
		*@brief Better size display.
		*@param _size Size to format.
		*@param _str String to fill.
		*/
		static void formatSize(double _size, std::string& _str);

		//Accessors
		std::list<std::string>* getList()
		{
			return m_fl;
		}

		std::string getPattern()
		{
			return m_pattern;
		}

	private:
		TSmartPtr<CPluginManager> 	m_pfm;
		std::list<std::string>* 	m_fl; 		//For FTW_callback
		std::string					m_pattern;	//For pattern matching
	
};
#endif //_ENGINE_H_
