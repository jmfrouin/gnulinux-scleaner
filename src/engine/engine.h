/**
 * This file is part of scleaner project.

 * Copyright (C) 1995 Ian Jackson <ian@chiark.greenend.org.uk>
 * Copyright (C) 2000 Yann Guidon <whygee@f-cpu.org>
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

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <string>
#include <list>
#include <map>
#include <vector>
#include <tools/smart_pointer.h>
#include <tools/singleton.h>
#include <plugins/plugin_manager.h>
#include "iprogress.h"

namespace Plugins
{
	class IInPlugin;
	class IOutPlugin;
	class IRootPlugin;
}

class CSettingsManager;

#define FSTAB "/etc/fstab"
#define ROUND(x) ((x-(int)x>0)?(int)x+1:(int)x) //Mainly wrote for formatSize

/*!
*@brief Contain all scleaner core related stuff.
*/
namespace Engine
{
	/*!
	 *@brief Manage all operations
	 *@version 15.11.2007
	 *@author Jean-Michel Frouin (jmfrouin@gnu.org)
	 */
	class CEngine: public Tools::CSmartCpt, public Tools::TSingleton<CEngine>
	{
		public:
			/*!
			 *@brief ctor
			 */
			CEngine();
	
			/*!
			 *@brief dtor
			 */
			~CEngine();
	
		public:
			/*!
			 *@brief Call load plugins in PluginManager.
			 *@param path The folder location.
			 *@return Number of plugins founded.
			 */
			int LoadPlugins (const std::string& path);
	
			/*!
			 *@brief Load GFX interface build on wxWidgets
			 *@return true is everything is OK, false otherwise.
			 */
			bool LoadInterface();
	
			/*!
			 *@brief Detect if launch as root
			 */
			static bool IsRoot();
	
			/*!
			 *@brief Detect kernel version
			 */
			static bool GetKernelVersion(std::string& version);
	
			/*!
			 *@brief callOutputPlugins with a list of files
			 *@param list A files list.
			 *@param name Name of plugin.
			 *@param path Path to save (if applicable) the output file.
			 *@param callback For progress bar.
			 *@return true on success, false otherwise.
			 *@todo Implement errors code.
			 */
			bool CallOutputPlugin(std::list<std::string>& list, std::string& name, const std::string& path, IProgressbar* callback);
	
			/*!
			 *@brief Replace wxDir usage.
			 *@param _path Where retrieve file list.
			 *@param _asRoot Scan in root mode.
			 *@param _rootPlugin Root plugin.
			 *@param _recursive If true, enter subfolders.
			 *@return true on success, false otherwise.
			 */
			bool scanDirectory(const std::string& _path, bool _asRoot = false, Plugins::IInPlugin* _rootPlugin = 0, bool _recursive = true);
	
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
			static bool getUsername(std::string& _username);
	
			/*!
			 *@brief Better size display.
			 *@param _size Size to format.
			 *@param _str String to fill.
			 */
			static void formatSize(double _size, std::string& _str);
	
			/*!
			 *@brief Get free space on system (Using mount table : by default /etc/fstab).
			 *@param _path To get space from a path.
			 *@param _used Used space correctly formatted.
			 *@param _free Available space correctly formatted.
			 *@param _total Total space correctly formatted.
			 *@return free space size in bytes.
			 */
			static double getFreeSpace(const std::string& _path, std::string& _used, std::string& _free, std::string& _total);
	
			/*!
			*@brief Launch a scan and pass each file to input plugin, to allow them to build file list.
			 *@param _callback For progress bar.
			*/
			bool scanDisk(IProgressbar* _callback = 0);
			
			/*!
			*@brief Get a timestamp.
			*@param _str The str to fill.
			*/
			static void getTimestamp(std::string& _str);
		
			/*!
			*@brief Calc CRC32.
			*@note http://f-cpu.seul.org/whygee/lm-gdups/article_gdups.html
			*@param _filename File name :D.
			*@param _crc The computed CRC32 for _filename.
			*/
			static void calcCRC32(const std::string& _filename, unsigned long& _crc);
	
		private:
			/*!
			*@brief Calc CRC32's table
			*@param _table The CRC32's table to fill
			*/
			static void getCRCTable(std::vector<unsigned long>& _table);
	
		public:
			/*!
			*@brief Add a file to files list
			*@param _file File name
			*@param _size File size
			*/
			void addFileInfo(const std::string& _file, unsigned long _crc);
	
			/*!
			*@brief Check for duplicates (and identicals) files
			*@return Number of duplicates files. (Count each once)
			*/
			int detectDuplicates();
	
		public:
			/*!
			*@brief Find a package on system.
			*@note Come from database.c & dpkg-db.h from dpkg package.
			*@param _name The package name to find.
			@return Error codes (to implement).
			*/
			int findPackage(const std::string& _name);

			/*!
			*@brief Retrieve a pointer on selected plugins list.
			*@param _refresh Did engine need to refresh the list ?
			*/
			std::map<std::string, Plugins::IInPlugin*>* getSelectedInputPlugs(bool _refresh = false);
	
		public:
			//For the FTW callback ... it sucks !!!
			Plugins::CPluginManager*	getPluginManager()
			{
				return m_pfm;
			}
	
			bool asRoot()
			{
				return m_asRoot;
			}
	
			Plugins::IInPlugin* rootPlugin()
			{
				return m_rootPlugin;
			}
	
			IProgressbar* getCallback()
			{
				return m_callback;
			}
	
			//Accessors
			std::map<std::string, Plugins::IInPlugin*>*  getAvailableInputPlugs()
			{
				return m_AvailableInputPlugs;
			}
	
			void setUnselectedInputPlugs(std::string _name)
			{
				m_UnselectedInputPlugs.push_back(_name);
			}

			unsigned int getCount()
			{
				return m_Count;
			}

			void setCount(unsigned int _Nb)
			{
				m_Count = _Nb;
			}
			
		private:
			Tools::TSmartPtr<Plugins::CPluginManager>  		m_pfm;
	
			//Input plugins
			std::map<std::string, Plugins::IInPlugin*>*  	m_AvailableInputPlugs;
			std::map<std::string, Plugins::IInPlugin*>  	m_SelectedInputPlugs;
			std::list<std::string>  						m_UnselectedInputPlugs;
	
			//Output plugins
			std::map<std::string, Plugins::IOutPlugin*>* 	m_OutputPlugs;
	
			//Due to this fuck*** callback
			Plugins::IInPlugin*								m_rootPlugin;
			bool											m_asRoot;
			IProgressbar*									m_callback;
			unsigned int									m_Count;
	
			//Files infos
			std::map<std::string, unsigned long>			m_Infos;
	
			//Duplicates files list
			std::map<unsigned long, std::string>			m_DuplicatesFilesList;

			//Settings manager
			Tools::TSmartPtr<CSettingsManager>   			m_Settings;

			//Selected plugins up to date ?
			bool											m_SelInPlugins;
	};
} //namespace Engine
#endif							 //_ENGINE_H_
