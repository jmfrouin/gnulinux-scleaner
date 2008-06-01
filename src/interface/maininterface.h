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

#ifndef __MAININTERFACE_H__
#define __MAININTERFACE_H__

#include <config.h>
#include <list>
#include <string>
#include <vector>
#include <wx/frame.h>
#include <wx/toolbar.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <engine/iprogress.h>
#include <tools/smart_pointer.h>
#include "tray.h"

namespace Engine
{
    class CEngine;
    class CSettingsManager;
}

class wxRadioBox;
class wxHtmlWindow;
class wxProgressDialog;
class wxAuiNotebook;
class wxPanel;

namespace GUI
{
    class wxCheckListCtrl;
    class wxCheckTreeCtrl;
}

class wxTreeMultiCtrl;

/*!
*@brief All GUI related stuff
*/
namespace GUI
{
    /*!
     * CMainInterface class declaration
     * @version 15.11.2007
     * @author Jean-Michel Frouin (jmfrouin@gmail.com)
     */
    class CMainInterface: public wxFrame, public IProgressbar
    {
        DECLARE_CLASS( CMainInterface )
            DECLARE_EVENT_TABLE()

            public:
            /// Constructors
            CMainInterface();
            CMainInterface(wxWindow* parent, wxWindowID id = SYMBOL_MAININTERFACE_IDNAME, const wxString& caption = SYMBOL_MAININTERFACE_TITLE, const wxPoint& pos = SYMBOL_MAININTERFACE_POSITION, const wxSize& size = SYMBOL_MAININTERFACE_SIZE, long style = SYMBOL_MAININTERFACE_STYLE);

            bool Create(wxWindow* parent, wxWindowID id = SYMBOL_MAININTERFACE_IDNAME, const wxString& caption = SYMBOL_MAININTERFACE_TITLE, const wxPoint& pos = SYMBOL_MAININTERFACE_POSITION, const wxSize& size = SYMBOL_MAININTERFACE_SIZE, long style = SYMBOL_MAININTERFACE_STYLE );

            virtual ~CMainInterface();

            void Init();
            void CreateControls();
            wxBitmap GetBitmapResource( const wxString& name );
            wxIcon GetIconResource( const wxString& name );
            static bool ShowToolTips();

            //Callbacks
            void OnAbout(wxCommandEvent& WXUNUSED(event));
            void OnQuit(wxCommandEvent& WXUNUSED(event));
            void OnProcess(wxCommandEvent& WXUNUSED(event));
            void OnScan(wxCommandEvent& WXUNUSED(event));
            void OnSelect(wxCommandEvent& WXUNUSED(event));
            void OnNotebook(wxNotebookEvent& event);
            void OnPrefs(wxCommandEvent& WXUNUSED(event));
            void OnFolderIncAdd(wxCommandEvent& WXUNUSED(event));
            void OnFolderIncDel(wxCommandEvent& WXUNUSED(event));
            void OnFolderExAdd(wxCommandEvent& WXUNUSED(event));
            void OnFolderExDel(wxCommandEvent& WXUNUSED(event));

            /*!
             *@brief Call splash screen
             *@param delay Delay, before splash will gone.
             */
            void LaunchSplash(int delay);

            /*!
             *@brief Retrieve list of selected files to process.
             *@param fl Files list to fill.
             */
            void GetSelectedFiles(std::list<std::string>& fl);

            /*!
            *@brief Update folder view :)
            */
            void UpdateFolderList();

            //From IProgressbar
            bool UpdateProgress(const std::string& mess, bool pulse, int nb);

        protected:
            CTrayIcon*                          fIcon;
        #if defined(__WXCOCOA__)
            CTrayIcon*                          fDockIcon;
        #endif
            //Engine
            Tools::TSmartPtr<Engine::CEngine>   fEngine;

            //GUI tree list which display input plugins and file list.
            wxNotebook*                         fFoundFiles;
            wxToolBar*                          fToolBar;

            //Informations GUI panel
            wxCheckTreeCtrl*                    fTree;

            //GUI checkbox which display output plugins
            wxStatusBar*                        fStatusBar;
            wxAuiNotebook*                      fAui;
            wxPanel*                            fFolders;
            wxCheckListCtrl*                    fAddedFolders;
            wxCheckListCtrl*                    fExcludedFolders;
            wxCheckListCtrl*                    fInputPlugins;
            wxRadioBox*                         fOutputPlugins;

            //Progress bar for process part.
            wxProgressDialog*                   fProgress;

            //Total sizes
            std::vector<double>                 fTotalSizes;

            //Settings manager
            Engine::CSettingsManager*           fSettings;
    };
}
#endif
// __MAININTERFACE_H__
