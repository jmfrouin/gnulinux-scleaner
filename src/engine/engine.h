/**
 * This file is part of scleaner project.

 * Copyright (C) 1995 Ian Jackson <ian@chiark.greenend.org.uk>
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

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <string>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <tools/smart_pointer.h>
#include <tools/singleton.h>
#include <plugins/plugin_manager.h>
#include <interface/maininterface.h>
#include <log/log.h>
#include "iprogress.h"
#include <def.h>

//forward declarations

namespace Plugins
{
  class IInPlugin;
  class IInputPlugin;
  class IOutPlugin;
}

class CSettingsManager;

/*!
 *@brief Contain all scleaner core related stuff.
 */
namespace Engine
{
  /*!
   *@brief Manage all operations
   *@version 22.06.2008
   *@author Jean-Michel Frouin (jmfrouin@gmail.com)
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
       *@brief Better size display.
       *@param size Size to format.
       *@param str String to fill.
       */
      static void FormatSize(double size, std::string& str);

      /*!
       *@brief Launch a scan and pass each file to input plugin, to allow them to build file list.
       *@param callback For progress bar.
       */
      bool ScanDisk(IProgressbar* callback);

      /*!
       *@brief Get a timestamp.
       *@param str The string to fill.
       */
      static void GetTimestamp(std::string& str);

      /*!
       *@brief Calc CRC32.
       *@note http://f-cpu.seul.org/whygee/lm-gdups/article_gdups.html
       *@param filename File name :D.
       *@param crc The computed CRC32 for _filename.
       */
      static void CalcCRC32(const std::string& filename, unsigned long& crc);

      /*!
       * @brief Get informations from /proc/
       * @param pattern The pattern to find.
       * @param file The file, where find.
       * @param str The string to fill.
       */
      static void PROCInfo(const std::string& pattern, const std::string& file, std::string& str);

      /*!
       *@brief Detect kernel version
       */
      static bool GetKernelVersion(std::string& version);

      /*!
       *@brief Retrieve username.
       *@param username The std::string to fill.
       *@return true on success, false otherwise.
       */
      static bool GetUsername(std::string& username);

      /*!
       *@brief Calc CRC32's table
       *@param table The CRC32's table to fill
       */
      static void GetCRCTable(std::vector<unsigned long>& table);

      /*!
       *@brief Add a file to files list
       *@param file File name
       *@param size File size
       */
      void AddFileInfo(const std::string& file, unsigned long crc);

      /*!
       *@brief Check for duplicates (and identicals) files
       *@return Number of duplicates files. (Count each once)
       */
      int DetectDuplicates();

      /*!
       *@brief Get free space on system (Using mount table : by default /etc/fstab).
       *@param path To get space from a path.
       *@param used Used space correctly formatted.
       *@param free Available space correctly formatted.
       *@param total Total space correctly formatted.
       *@return free space size in bytes.
       */
      static double GetFreeSpace(const std::string& path, std::string& usedspace, std::string& freespace, std::string& total);

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

      //Accessors
      std::map<std::string, Plugins::IInPlugin*>*  GetAvailableInputPlugs() { return fAvailableInputPlugs; }
      //unsigned int GetCount() { return fCount; }

      /*!
       *@brief Retrieve a pointer on selected plugins list.
       *@param refresh Did engine need to refresh the list ?
       */
      std::map<std::string, Plugins::IInPlugin*>* GetSelectedInputPlugs(bool refresh = false);

      //void SetCount(unsigned int nb) { fCount = nb; }
      void SetUnselectedInputPlugs(std::string name) { fUnselectedInputPlugs.push_back(name); }

      /*!
       * @brief Retrieve a pointer on duplicates CRC
       */
      std::set<unsigned long>* GetDuplicatesCRC() { return &fDuplicatesCRC; }

      /*! 
        *@brief Retrieve pointer on CRC infos.
       */
        std::map<std::string, unsigned long>* GetFileInfos() { return &fInfos; }

    private:
      /*!
       * @brief Use scandir to scan a directory.
       * @param filename Directory to scan.
       * @param callback Progress bar callback.
       * @return bool true on continue, false otherwise.
       */
      bool ScanDir(const std::string& filename, IProgressbar* callback);

      /*!
       * @brief Prepare folders list to scan.
       */
      void PrepareFilesList(IProgressbar* callback);

      /*!
       *@brief Find a package on system.
       *@note Come from database.c & dpkg-db.h from dpkg package.
       *@param name The package name to find.
      @return Error codes (to implement).
      */
      int FindPackage(const std::string& name);

    private:
      GUI::CMainInterface* fInterface;
      Tools::TSmartPtr<Plugins::CPluginManager>       fPFM;

      //Input plugins
      std::map<std::string, Plugins::IInPlugin*>*     fAvailableInputPlugs;
      std::map<std::string, Plugins::IInPlugin*>      fSelectedInputPlugs;
      std::list<std::string>                          fUnselectedInputPlugs;

      //Output plugins
      std::map<std::string, Plugins::IOutPlugin*>*    fOutputPlugs;

      //Faster progress bar.
      unsigned int fCount; 

      // Files infos 
      std::map<std::string, unsigned long>            fInfos;

      //Duplicates CRC
      std::set<unsigned long> fDuplicatesCRC;

      //Files list
      std::list<std::string>                          fFilesList;

      //Settings manager
      Tools::TSmartPtr<CSettingsManager>              fSettings;

      //Selected plugins up to date ?
      bool                                            fSelInPlugins;
  };
}                                //namespace Engine
#endif                           //__ENGINE_H__
