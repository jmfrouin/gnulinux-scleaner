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

#ifndef __SETTINGS_MANAGER_H__
#define __SETTINGS_MANAGER_H__

#include <tools/smart_pointer.h>
#include <tools/singleton.h>
#include <string>
#include <list>

#define PREFFILE "~/.scleaner/prefs.conf"

namespace Engine
{
  /*!
   * @brief Manage all settings.
   * Load them on creation
   * Save them on destruction (or Apply)
   * @version 29.03.2008
   * @author Jean-Michel Frouin (jmfrouin@gmail.com)
   */
  class CSettingsManager: public Tools::CSmartCpt, public Tools::TSingleton<CSettingsManager>
  {
    public:
      enum eSettings
      {
        eShowSplash = 10,
        eFolderInc,
        eFolderEx,
        eShowToolbar,
        eShowStatusbar,
        eDelete,
        eSystemFiles,
        eRecursiveScan,
        ePerspective
      };

      enum eFoldersType
      {
        eNone = 0,
        eFoldersInc,
        eFoldersEx
      };

    public:
      /*!
       * Construstor : Load preferences.
       */
      CSettingsManager();

      /*!
       * Destructor : Save preferences.
       * @todo Remove duplicate code
       */
      ~CSettingsManager();

      //Kind of accessors
      /*!
       *@brief Add a folder to m_FoldersList.
       *@param dir The directory to add (selected by user using wxDirDialog).
       *@param parent The parent directory.
       *@param type We add a folder to include or exclude ?.
       *@return true if folder added, false otherwise.
       */
      bool AddFolder(const std::string dir, std::string& parent, eFoldersType type = eNone);

      /*!
       *@brief Remove a folder to m_FoldersList
       *@param dir The directory to delete (selected by user using wxDirDialog)
       *@param type We remove a folder to include or exclude ?.
       */
      void DelFolder(const std::string dir, eFoldersType type = eNone);

      /*!
       * Accessors
       */
      bool GetShowSplash() { return fShowSplash; }

      std::list<std::string>* GetFoldersListPtr() { return &fFoldersList; }

      std::list<std::string>* GetExcludedFoldersListPtr() { return &fExcludedFoldersList; }

      bool GetShowToolbar() { return fShowToolbar; }

      bool GetShowStatusbar() { return fShowStatusbar; }

      bool GetDelete() { return fDelete; }

      bool GetSystemFiles() { return fSystemFiles; }

      bool GetRecursiveScan() { return fRecursiveScan; }

      std::string GetPerspective() { return fPerspective; }
      
      /*!
       * Mutators
       */
      void SetShowSplash(bool val) { fShowSplash = val; }

      void SetShowToolbar(bool val) { fShowToolbar = val; }

      void SetShowStatusbar(bool val) { fShowStatusbar = val; }

      void SetDelete(bool val) { fDelete = val; }

      void SetSystemFiles(bool val) { fSystemFiles = val; }

      void SetRecursiveScan(bool val) { fRecursiveScan = val; }

      void SetPerspective(const std::string& str) { fPerspective = str; }

    private:
                                 ///Display splash (only in GUI) ?
      bool                    fShowSplash;

      //Folders infos
      std::list<std::string>  fFoldersList;
      std::list<std::string>  fExcludedFoldersList;

                                 ///Display toolbar (only in GUI) ?
      bool                    fShowToolbar;
                                 ///Display statusbar (only in GUI) ?
      bool                    fShowStatusbar;
                                 ///Delete files after applying the ouput plugin ?
      bool                    fDelete;
                                 ///Include system file and folders (.*) ?
      bool                    fSystemFiles;
                                 ///Recursive scan ?
      bool                    fRecursiveScan;

      std::string         fPerspective;
  };
}                                //namespace Engine
#endif                           //__SETTINGS_MANAGER_H__
