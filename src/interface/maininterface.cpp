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

#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <config.h>
#include <string>
#include <sstream>
#include <sys/stat.h>
#include <plugins/plugin_manager.h>
#include <plugins/iplugin.h>
#include <engine/engine.h>
#include <engine/settings_manager.h>
#include <wx/radiobox.h>
#include <wx/progdlg.h>
#include <wx/dirdlg.h>
#include <wx/splash.h>
#include <wx/wxhtml.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/aui/auibook.h>
#include <wx/statline.h>
#include "maininterface.h"
#include "checklistctrl.h"
#include "checktreectrl.h"
#include "select_dialog.h"
#include "preferences.h"
#include "aboutdialog.h"

//App icon
#include <gfx/scleaner.xpm>

//Tray icons
#include <gfx/empty.xpm>
#include <gfx/full.xpm>

//Toolbar icons
#include <gfx/exit.xpm>
#include <gfx/run.xpm>
#include <gfx/select.xpm>
#include <gfx/scan.xpm>
#include <gfx/config.xpm>

#include <gfx/folder-add.xpm>
#include <gfx/folder-del.xpm>

#include <gfx/prefs.xpm>

//Menu icons
#include <gfx/menu_add_folder.xpm>
#include <gfx/menu_del_folder.xpm>
#include <gfx/menu_prefs.xpm>
#include <gfx/menu_about.xpm>

namespace GUI
{
    IMPLEMENT_CLASS( CMainInterface, wxFrame )

    BEGIN_EVENT_TABLE( CMainInterface, wxFrame )

    EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, CMainInterface::OnNotebook)
    EVT_MENU(ID_SCAN, CMainInterface::OnScan)
    EVT_MENU(ID_ABOUT, CMainInterface::OnAbout)
    EVT_MENU(ID_PREFS, CMainInterface::OnPrefs)
    EVT_MENU(wxID_EXIT, CMainInterface::OnQuit)
    EVT_MENU(ID_PROCESS, CMainInterface::OnProcess)
    EVT_MENU(ID_SELECT, CMainInterface::OnSelect)
    //ListBook
    EVT_BUTTON(ID_FOLDER_INC_ADD, CMainInterface::OnFolderIncAdd)
    EVT_BUTTON(ID_FOLDER_INC_DEL, CMainInterface::OnFolderIncDel)
    EVT_BUTTON(ID_FOLDER_EX_ADD, CMainInterface::OnFolderExAdd)
    EVT_BUTTON(ID_FOLDER_EX_DEL, CMainInterface::OnFolderExDel)

    END_EVENT_TABLE()

    CMainInterface::CMainInterface()
    {
        Init();
    }


    CMainInterface::CMainInterface(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style):
    fFoundFiles(0), fStatusBar(0), fAui(0), fFolders(0), fAddedFolders(0), fExcludedFolders(0), fInputPlugins(0), fOutputPlugins(0), fProgress(0), fSettings(0)
    {
        Init();
        Create(parent, id, caption, pos, size, style);
    }


    bool CMainInterface::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
    {
        wxFrame::Create( parent, id, caption, pos, size, style );

        CreateControls();
        Centre();

        SetIcon(wxICON(scleaner));
        return true;
    }


    CMainInterface::~CMainInterface()
    {
        if(fIcon)
        {
            delete fIcon;
        }
        #if defined(__WXCOCOA__)
        if(fDockIcon)
        {
            delete fDockIcon;
        }
        #endif
    }


    void CMainInterface::Init()
    {
        //Retrieve Engine::CEngine instance pointer.
        fEngine = Engine::CEngine::Instance();

        //Retrieve settings manager pointer
        fSettings = Engine::CSettingsManager::Instance();

        //Tray icon !!
        fIcon = new CTrayIcon();
        #if defined(__WXCOCOA__)
        fDockIcon = new CTrayIcon(wxTaskBarIcon::DOCK);
        #endif

        fIcon->setParent(this);

        if (!fIcon->SetIcon(scleaner_xpm, wxT(NAME)))
        {
            std::cout << i8n("[ERR] Could not set icon.\n");
        }

        //Show splash
        if(fSettings->GetShowSplash() == true)
        {
            LaunchSplash(1000);
        }
    }


    void CMainInterface::LaunchSplash(int delay)
    {
        #if defined(SPLASH)
        //Splash
        wxBitmap bitmap;

        if(bitmap.LoadFile(_T("/usr/share/doc/scleaner/splash.png")), wxBITMAP_TYPE_PNG)
        {
            //Bitmap successfully loaded
            new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, delay, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxSTAY_ON_TOP);
        }
        #endif
    }


    void CMainInterface::CreateControls()
    {
        CMainInterface* Frame = this;

        //MENU
        wxMenuBar* MenuBar = new wxMenuBar;
        wxMenu* File = new wxMenu;
        wxMenu* Edit = new wxMenu;
        wxMenu* Misc = new wxMenu;

        //File menu
        MenuBar->Append(File, wxString(i8n("File"), wxConvUTF8));
        wxMenuItem* Quit = new wxMenuItem(File, wxID_EXIT, wxString(i8n("Quit"), wxConvUTF8));
        File->Append(Quit);

        //Folders menu
        MenuBar->Append(Edit, wxString(i8n("Edit"), wxConvUTF8));
        wxMenuItem* Prefs = new wxMenuItem(Edit, ID_PREFS, wxString(i8n("Preferences\tCtrl-P"), wxConvUTF8));
        Prefs->SetBitmap(menu_prefs_xpm);
        Edit->Append(Prefs);

        //Misc menu
        MenuBar->Append(Misc, wxString(i8n("Misc"), wxConvUTF8));
        wxMenuItem* About = new wxMenuItem(Misc, ID_ABOUT, wxString(i8n("About"), wxConvUTF8));
        About->SetBitmap(menu_about_xpm);
        Misc->Append(About);

        Frame->SetMenuBar(MenuBar);

        //Toolbar
        if(fSettings->GetShowToolbar() == true)
        {
            wxToolBar* ToolBar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR1 );
            ToolBar->AddTool(ID_SCAN, wxString(i8n("Use input plugins to find files."), wxConvUTF8), scan_xpm, scan_xpm, wxITEM_NORMAL, wxString(i8n("Use input plugins to find files."), wxConvUTF8), wxEmptyString);
            ToolBar->AddTool(ID_PROCESS, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8),run_xpm , run_xpm, wxITEM_NORMAL, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8), wxEmptyString);
            ToolBar->AddSeparator();
            ToolBar->AddTool(ID_PREFS, wxString(i8n("Preferences"), wxConvUTF8), prefs_xpm , prefs_xpm, wxITEM_NORMAL, wxString(i8n("Preferences"), wxConvUTF8), wxEmptyString);
            ToolBar->AddSeparator();
            ToolBar->AddTool(wxID_EXIT, wxString(i8n("Quit"), wxConvUTF8),exit_xpm , exit_xpm, wxITEM_NORMAL, wxString(i8n("Quit"), wxConvUTF8), wxEmptyString);
            ToolBar->Realize();
            Frame->SetToolBar(ToolBar);
        }

        //AuiNotebook
        fAui = new wxAuiNotebook(Frame, ID_AUI, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE|wxAUI_NB_SCROLL_BUTTONS);

        //Folder AuiNotebook page
        int Flags = wxBK_TOP | wxNB_MULTILINE | wxDOUBLE_BORDER;
        UpdateFolderList();

        fAui->AddPage(fFolders, wxString(i8n("Folders"), wxConvUTF8), false);

        //Input plugins
        fInputPlugins = new wxCheckListCtrl(fAui, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxSUNKEN_BORDER | wxLC_VRULES | wxLC_HRULES);

        wxListItem ItemCol;
        ItemCol.SetText(wxString(i8n("Plugin name"), wxConvUTF8));
        ItemCol.SetImage(-1);
        fInputPlugins->InsertColumn(0, ItemCol);

        ItemCol.SetText(wxString(i8n("Description"), wxConvUTF8));
        ItemCol.SetAlign(wxLIST_FORMAT_CENTRE);
        fInputPlugins->InsertColumn(1, ItemCol);

        int Counter=0;
        std::map<std::string, Plugins::IInPlugin*>::iterator It;
        for(It = fEngine->GetAvailableInputPlugs()->begin(); It != fEngine->GetAvailableInputPlugs()->end(); ++It)
        {
            fInputPlugins->Hide();

            wxString String(((*It).second)->GetName().c_str(), wxConvUTF8);
            wxString Description(((*It).second)->Description().c_str(), wxConvUTF8);
            long LongTmp = fInputPlugins->InsertItem(Counter++, String, 0);
            fInputPlugins->SetItem(LongTmp, 1, Description);
        }
        fInputPlugins->Show();
        fInputPlugins->SetColumnWidth(0, wxLIST_AUTOSIZE);
        fInputPlugins->SetColumnWidth(1, wxLIST_AUTOSIZE);

        fAui->AddPage(fInputPlugins, wxString(i8n("Input plugins"), wxConvUTF8), false);

        wxSplitterWindow* itemSplitterWindow9 = new wxSplitterWindow(fAui, 0, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow9->SetMinimumPaneSize(0);

    wxCheckTreeCtrl* fTest = new wxCheckTreeCtrl(itemSplitterWindow9, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxSUNKEN_BORDER | wxLC_VRULES | wxLC_HRULES);
    wxString text;
    wxTreeItemId temp = fTest->GetRootItem();
      wxTreeItemId rootId = fTest->AddRoot(wxT("/home/snoogie/"),
                              0, 0);
    for(int i=10; --i;)
    {
        text.Printf(wxT("test#%d.txt, 0B, located by null files size plugin"), i);
        std::cout << i << "\n";
        wxTreeItemId temp2 = fTest->AddCheckedItem(rootId, text, true);
        for(int j=10; --j;)
        {
            text.Printf(wxT("Item #%d"), i);
            std::cout << i << "\n";
            wxTreeItemId temp2 = fTest->AddCheckedItem(rootId, text, true);
            for(int j=10; --j;)
            {
                //temp.AddCheckedItem(temp2, text, true);
            }
        }
    }

    wxPanel* itemPanel11 = new wxPanel( itemSplitterWindow9, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemPanel11->SetSizer(itemBoxSizer12);

    wxButton* itemButton13 = new wxButton( itemPanel11, 0, _("Order by input plugins"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton14 = new wxButton( itemPanel11, 0, _("Order by size"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton15 = new wxButton( itemPanel11, 0, _("Order by ... what else ?"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton15, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemSplitterWindow9->SplitVertically(fTest, itemPanel11, 50);
    fAui->AddPage(itemSplitterWindow9, _("Tab"), false);

        //Output plugins
        wxString Output[1];
        Output[0] = _("tbz");
        fOutputPlugins = new wxRadioBox(fAui, wxID_ANY, wxString(i8n("Output plugins :"), wxConvUTF8), wxDefaultPosition, wxDefaultSize, 1, Output);

        fAui->AddPage(fOutputPlugins, wxString(i8n("Output plugins"), wxConvUTF8), false);

        //Found files AuiNotebook page
        //FIXME: Display it only when "scan" has been launched
        fFoundFiles = new wxNotebook(fAui, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, Flags);
        fAui->AddPage(fFoundFiles, wxString(i8n("Found files"), wxConvUTF8), false);

        if(fSettings->GetShowStatusbar() == true)
        {
            fStatusBar = new wxStatusBar(Frame, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
            fStatusBar->SetFieldsCount(6);
            Frame->SetStatusBar(fStatusBar);

            if(fEngine->IsRoot())
            {
                SetStatusText(wxString(i8n("Launched as root/sudo"), wxConvUTF8), 2);
            }
            else
            {
                std::string UserName;
                fEngine->GetUsername(UserName);
                wxString UUserName(UserName.c_str(), wxConvUTF8);
                SetStatusText(wxString(i8n("Launched as "), wxConvUTF8) + UUserName, 2);
            }

            std::string Version = i8n("Kernel : v");
            fEngine->GetKernelVersion(Version);
            wxString UVersion(Version.c_str(), wxConvUTF8);
            SetStatusText(UVersion, 1);
            std::string Path, UsedSpace(i8n("Used: ")), FreeSpace(i8n("Free: ")), Total(i8n("Total: "));
            fEngine->GetFreeSpace(Path, UsedSpace, FreeSpace, Total);
            wxString UTotal(Total.c_str(), wxConvUTF8);
            SetStatusText(UTotal, 3);
            wxString UUsedSpace(UsedSpace.c_str(), wxConvUTF8);
            SetStatusText(UUsedSpace, 4);
            wxString UFreeSpace(FreeSpace.c_str(), wxConvUTF8);
            SetStatusText(UFreeSpace, 5);
        }
    }


    bool CMainInterface::ShowToolTips()
    {
        return true;
    }


    wxBitmap CMainInterface::GetBitmapResource( const wxString& name )
    {
        wxUnusedVar(name);
        return wxNullBitmap;
    }


    wxIcon CMainInterface::GetIconResource( const wxString& name )
    {
        wxUnusedVar(name);
        return wxNullIcon;
    }


    //Callbacks
    //NoteBook
    void CMainInterface::OnNotebook(wxNotebookEvent& event)
    {
        wxString Name;
        int Selection = event.GetSelection();
        Name  = fFoundFiles->GetPageText(Selection);
        std::stringstream Total;
        if(fTotalSizes.size() > 0)
        {
            std::string Total(i8n("Total size : "));
            Engine::CEngine::Instance()->FormatSize(fTotalSizes[Selection], Total);
            wxString Totalsize(Total.c_str(), wxConvUTF8);
            SetStatusText(Totalsize, 0);
        }
    }


    //Menu
    void CMainInterface::OnAbout(wxCommandEvent& WXUNUSED(event))
    {
        //LaunchSplash(3000);
        CAboutDialog *Dial = new CAboutDialog(NULL, -1, _T("About"), wxDefaultPosition, wxSize(250, 230));
        Dial->Show(true);
    }


    void CMainInterface::OnQuit(wxCommandEvent& WXUNUSED(event))
    {
        Close(true);
    }


    //Toolbar
    void CMainInterface::OnScan(wxCommandEvent& WXUNUSED(event))
    {
        std::cout << "OnScan\n";
        fFoundFiles->DeleteAllPages();
        fProgress = new wxProgressDialog(wxString(i8n("scleaner scan your disk ..."), wxConvUTF8),
            wxString(i8n("this is a information"), wxConvUTF8), 100, this,
            wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME | wxPD_SMOOTH           // - makes indeterminate mode bar on WinXP very small
            );

        fEngine->ScanDisk(this);
        std::cout << "ScanDisk\n";

        delete fProgress;
        fProgress = 0;

        double Totalsize = 0;
        // Happend plugins' name available
        std::map<std::string, Plugins::IInPlugin*>::iterator It = fEngine->GetSelectedInputPlugs(true)->begin();
        for(; It != fEngine->GetSelectedInputPlugs()->end(); ++It)
        {
            wxString String(((*It).second)->GetName().c_str(), wxConvUTF8);

            std::list<std::string> List;
            ((*It).second)->GetFileList(List);
            List.sort();
            std::list<std::string>::iterator It2;


            #if defined DEBUG
            std::cout << i8n("[DBG] Size = ") << List.size() << '\n';
            #endif
            wxCheckListCtrl* FilesList = new wxCheckListCtrl(fFoundFiles, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxSUNKEN_BORDER | wxLC_VRULES | wxLC_HRULES);

            //Setting header:
            wxListItem ItemCol;
            ItemCol.SetText(wxString(i8n("File location"), wxConvUTF8));
            ItemCol.SetImage(-1);
            FilesList->InsertColumn(0, ItemCol);

            ItemCol.SetText(wxString(i8n("Size (bytes)"), wxConvUTF8));
            ItemCol.SetAlign(wxLIST_FORMAT_CENTRE);
            FilesList->InsertColumn(1, ItemCol);

            ItemCol.SetText(wxString(i8n("CRC32"), wxConvUTF8));
            ItemCol.SetAlign(wxLIST_FORMAT_RIGHT);
            FilesList->InsertColumn(2, ItemCol);

            // to speed up inserting, we hide the control temporarily
            FilesList->Hide();

            int Counter = 0;
            for(It2 = List.begin(); It2 != List.end(); ++It2)
            {
                std::string FileName(*It2);
                wxString String2(FileName.c_str(), wxConvUTF8);
                long LongTmp = FilesList->InsertItem(Counter, String2, 0);
                FilesList->SetItemData(LongTmp, Counter);

                //Insert file size.
                struct stat Info;

                //Try to stat file.
                if(stat(FileName.c_str(), &Info) == -1)
                {
                    std::cout << i8n("[ERR] : Cannot stat ") << FileName << '\n';
                }
                else
                {

                    Totalsize += Info.st_size;
                    std::string Size;
                    fEngine->FormatSize(Info.st_size, Size);
                    wxString USize(Size.c_str(), wxConvUTF8);
                    FilesList->SetItem(LongTmp, 1, USize);

                    if(Info.st_size != 0)
                    {
                        unsigned long CRC;
                        Engine::CEngine::CalcCRC32(FileName, CRC);
                        std::stringstream CRC2;
                        CRC2 << CRC;
                        FilesList->SetItem(LongTmp, 2, wxString(std::string(CRC2.str()).c_str(), wxConvUTF8));
                        fEngine->AddFileInfo(FileName, CRC);
                    }
                    else
                    {
                        FilesList->SetItem(LongTmp, 2, wxString(_T("No CRC32")));
                        fEngine->AddFileInfo(FileName, 0);
                    }
                }
                ++Counter;
            }

            FilesList->SetColumnWidth(0, wxLIST_AUTOSIZE);
            FilesList->SetColumnWidth(1, wxLIST_AUTOSIZE);
            FilesList->SetColumnWidth(2, wxLIST_AUTOSIZE);

            FilesList->Show();
            fFoundFiles->AddPage(FilesList, String, true);
            fTotalSizes.push_back(Totalsize);
        }

        fFoundFiles->AdvanceSelection();
        fEngine->DetectDuplicates();
    }


    void CMainInterface::OnProcess(wxCommandEvent& WXUNUSED(event))
    {
        //GetToolBar()->SetToolShortHelp(wxID_NEW, _T("New toolbar button"));
        #if defined DEBUG
        std::cout << i8n("[DBG] Process !!! ") << '\n';
        #endif
        std::list<std::string> SelectionectedFiles;
        //GetSelectedFilesRecursively(fFoundFiles->GetRootItem(), SelectionectedFiles);
        GetSelectedFiles(SelectionectedFiles);

        #if defined DEBUG
        std::cout << i8n("[DBG] You have selected: ") << '\n';
        std::list<std::string>::iterator It;
        for(It = SelectionectedFiles.begin(); It != SelectionectedFiles.end(); ++It)
        {
            std::cout << "[DBG] " << *It << '\n';
        }
        #endif

        fProgress = new wxProgressDialog(wxString(i8n("scleaner process your files ..."), wxConvUTF8),
            wxString(i8n("this is a information"), wxConvUTF8),
            100,                     // range
            this,                    // parent
            wxPD_CAN_ABORT |
            // wxPD_CAN_SKIP |
            wxPD_APP_MODAL |
            //wxPD_AUTO_HIDE | -- try this as well
            wxPD_ELAPSED_TIME |
            wxPD_ESTIMATED_TIME |
            wxPD_REMAINING_TIME
            | wxPD_SMOOTH            // - makes indeterminate mode bar on WinXP very small
            );

        std::string Name;
        wxString NameWX;
        //NameWX = fOutput->GetStringSelection();
        Name = NameWX.char_str();

        #if defined DEBUG
        std::cout << i8n("[DBG] CMainInterface : Get selection : ") << Name << '\n';
        #endif

        wxString Message;
        if(Engine::CEngine::IsRoot())
        {
            Message = _T("/root/");
        }
        else
        {
            std::string Path("/home");
            std::string UserName;
            Engine::CEngine::GetUsername(UserName);
            Path += "/" + UserName;
            Message.FromUTF8(Path.c_str());
        }

        wxDirDialog OutputFileDlg(this, wxString(i8n("Select an output folder for "), wxConvUTF8) + NameWX + wxString(i8n(" plugin:"), wxConvUTF8), Message, wxDD_DIR_MUST_EXIST);

        if (OutputFileDlg.ShowModal() == wxID_OK)
        {
            std::string SelectionPath(OutputFileDlg.GetPath().char_str());
            fEngine->CallOutputPlugin(SelectionectedFiles, Name, SelectionPath, this);
        }

        delete fProgress;
        fProgress = 0;
    }

    void CMainInterface::UpdateFolderList()
    {
        //If folders panel not created, we created it here !
        if(!fFolders)
        {
            fFolders = new wxPanel(fAui, -1);
            wxSizer* Sizer = new wxBoxSizer(wxVERTICAL);
            fFolders->SetSizer(Sizer);

            Sizer->Add(new wxStaticText(fFolders, -1, _T("Folders added to scan :")), 0, wxALIGN_LEFT | wxALL, 5);

            if(!fAddedFolders)
            {
                fAddedFolders = new GUI::wxCheckListCtrl(fFolders, wxID_ANY, wxDefaultPosition, wxDefaultSize);
                //Setting header:
                wxListItem ItemCol;
                ItemCol.SetText(wxString(i8n("Name"), wxConvUTF8));
                ItemCol.SetImage(-1);
                fAddedFolders->InsertColumn(0, ItemCol);
            }

            Sizer->Add(fAddedFolders, 1, wxGROW | wxALL, 5);

            wxSizer* Sizer2 = new wxBoxSizer(wxHORIZONTAL);
            Sizer2->Add(new wxButton(fFolders, ID_FOLDER_INC_ADD, _T("Add")), 0, wxALIGN_CENTER | wxALL, 2);
            Sizer2->Add(new wxButton(fFolders, ID_FOLDER_INC_DEL, _T("Remove")), 0, wxALIGN_CENTER | wxALL, 2);

            Sizer->Add(Sizer2, 0, wxGROW | wxALL, 5);

            wxStaticLine* Line = new wxStaticLine(fFolders, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
            Sizer->Add(Line, 0, wxGROW|wxALL, 5);

            Sizer->Add(new wxStaticText(fFolders, -1, _T("Folders excluded from scan :")), 0, wxALIGN_LEFT | wxALL, 5);

            if(!fExcludedFolders)
            {
                fExcludedFolders = new GUI::wxCheckListCtrl(fFolders, wxID_ANY, wxDefaultPosition, wxDefaultSize);
                //Setting header:
                wxListItem ItemCol;
                ItemCol.SetText(wxString(i8n("Name"), wxConvUTF8));
                ItemCol.SetImage(-1);
                fExcludedFolders->InsertColumn(0, ItemCol);
            }

            Sizer->Add(fExcludedFolders, 1, wxGROW | wxALL, 5);

            Sizer2 = new wxBoxSizer(wxHORIZONTAL);
            Sizer2->Add(new wxButton(fFolders, ID_FOLDER_EX_ADD, _T("Add")), 0, wxALIGN_CENTER | wxALL, 2);
            Sizer2->Add(new wxButton(fFolders, ID_FOLDER_EX_DEL, _T("Remove")), 0, wxALIGN_CENTER | wxALL, 2);

            Sizer->Add(Sizer2, 0, wxGROW | wxALL, 5);
        }

        //First clear lists
        if(fAddedFolders != 0)
        {
            fAddedFolders->DeleteAllItems();
        }

        if(fExcludedFolders != 0)
        {
            fExcludedFolders->DeleteAllItems();
        }

        //The, fill panel

        //Declare common iterator
        std::list<std::string>::iterator It;

        std::list<std::string>* FL = fSettings->GetFoldersListPtr();
        for(It = FL->begin(); It !=FL->end(); ++It)
        {
            //Maybe an alphabetic sort will be need here : algorithms :D
            long LongTmp = fAddedFolders->InsertItem(FL->size(), wxString((*It).c_str(), wxConvUTF8), 0);
            fAddedFolders->SetItemImage(LongTmp, 2);
            fAddedFolders->SetItemData(LongTmp, 0);
            fAddedFolders->SetColumnWidth(0, wxLIST_AUTOSIZE);
        }

        FL = fSettings->GetExcludedFoldersListPtr();
        for(It = FL->begin(); It !=FL->end(); ++It)
        {
            //Maybe an alphabetic sort will be need here : algorithms :D
            long LongTmp = fExcludedFolders->InsertItem(FL->size(), wxString((*It).c_str(), wxConvUTF8), 0);
            fExcludedFolders->SetItemImage(LongTmp, 2);
            fExcludedFolders->SetItemData(LongTmp, 0);
            fExcludedFolders->SetColumnWidth(0, wxLIST_AUTOSIZE);
        }
    }


    void CMainInterface::OnFolderIncAdd(wxCommandEvent& WXUNUSED(event))
    {
        wxString Message(_T("coucou"));
        wxDirDialog AddDlg(this, wxString(i8n("Select a folder to add to scan"), wxConvUTF8), Message, wxDD_DIR_MUST_EXIST);
        if(AddDlg.ShowModal() == wxID_OK)
        {
            std::string SelectionPath(AddDlg.GetPath().char_str());
            std::string Parent;
            //std::cout << SelectionPath << '\n';
            if(!fSettings->AddFolder(SelectionPath, Parent, Engine::CSettingsManager::eFoldersInc))
            {
                wxString Text(i8n("I cannot add "), wxConvUTF8);
                Text += wxString(SelectionPath.c_str(), wxConvUTF8);
                Text += wxString(i8n(" since "), wxConvUTF8);
                Text += wxString(Parent.c_str(), wxConvUTF8);
                Text += wxString(i8n(" is already in the folders list."), wxConvUTF8);

                wxMessageBox(Text, wxString(i8n("scleaner information"), wxConvUTF8), wxICON_INFORMATION);
            }
            else
            {
                UpdateFolderList();
            }
        }
    }


    void CMainInterface::OnFolderIncDel(wxCommandEvent& WXUNUSED(event))
    {
        bool Refresh = false;

        for(int i = 0; i != fAddedFolders->GetItemCount(); ++i)
        {
            long Mask;
            Mask = wxLIST_STATE_SELECTED;
            if(fAddedFolders->GetItemState(i, Mask) == Mask)
            {
                wxListItem Item;
                Item.SetId(i);
                fAddedFolders->GetItem(Item);
                wxString Text = Item.GetText();
                fSettings->DelFolder(std::string(Text.ToAscii()), Engine::CSettingsManager::eFoldersInc);
                Refresh = true;
            }
        }

        if(Refresh)
        {
            UpdateFolderList();
        }
    }


    void CMainInterface::OnFolderExAdd(wxCommandEvent& WXUNUSED(event))
    {
        wxString Message(_T("coucou"));
        wxDirDialog AddDlg(this, wxString(i8n("Select a folder to add to scan"), wxConvUTF8), Message, wxDD_DIR_MUST_EXIST);
        if(AddDlg.ShowModal() == wxID_OK)
        {
            std::string SelectionPath(AddDlg.GetPath().char_str());
            std::string Parent;
            if(!fSettings->AddFolder(SelectionPath, Parent, Engine::CSettingsManager::eFoldersEx))
            {
                wxString Text(i8n("I cannot add "), wxConvUTF8);
                Text += wxString(SelectionPath.c_str(), wxConvUTF8);
                Text += wxString(i8n(" since "), wxConvUTF8);
                Text += wxString(Parent.c_str(), wxConvUTF8);
                Text += wxString(i8n(" is already in the folders list."), wxConvUTF8);

                wxMessageBox(Text, wxString(i8n("scleaner information"), wxConvUTF8), wxICON_INFORMATION);
            }
            else
            {
                UpdateFolderList();
            }
        }
    }


    void CMainInterface::OnFolderExDel(wxCommandEvent& WXUNUSED(event))
    {
        bool Refresh = false;

        for(int i = 0; i != fExcludedFolders->GetItemCount(); ++i)
        {
            long Mask;
            Mask = wxLIST_STATE_SELECTED;
            if(fExcludedFolders->GetItemState(i, Mask) == Mask)
            {
                wxListItem Item;
                Item.SetId(i);
                fExcludedFolders->GetItem(Item);
                wxString Text = Item.GetText();
                fSettings->DelFolder(std::string(Text.ToAscii()), Engine::CSettingsManager::eFoldersEx);
                Refresh = true;
            }
        }

        if(Refresh)
        {
            UpdateFolderList();
        }
    }


    void CMainInterface::OnPrefs(wxCommandEvent& WXUNUSED(event))
    {
        CPreferences(this, wxID_ANY, wxString(i8n("Preferences"), wxConvUTF8), wxDefaultPosition, wxDefaultSize).ShowModal();
    }


    void CMainInterface::UpdateProgress(const std::string& mess, bool pulse, int nb)
    {
        wxString Message(mess.c_str(), wxConvUTF8);
        bool Continue;
        if(pulse)
        {
            Continue = fProgress->Pulse(Message, 0);
        }
        else
        {
            Continue = fProgress->Update(nb, Message, 0);
        }

        //if(!Continue)
        //{
        //  if ( wxMessageBox(_T("Do you really want to cancel?"), _T("scleaner question"), wxYES_NO | wxICON_QUESTION) == wxNO)
        //  {
        //      Continue = true;
        //      fProgress->Resume();
        //  }
        //}
    }


    void CMainInterface::OnSelect(wxCommandEvent& WXUNUSED(event))
    {
        //GetToolBar()->SetToolShortHelp(wxID_NEW, _T("New toolbar button"));
        wxMessageDialog(this, wxString(i8n("Since for this alpha version, there are only 3 input plugins (and 2 that run only in root mode), the dialog for selecting input plugins is not yet ready :D but will be available soon !!"), wxConvUTF8), _T("scleaner"), wxOK | wxICON_EXCLAMATION).ShowModal();

        std::list<std::string> PluginList;

        std::map<std::string, Plugins::IInPlugin*>::iterator It;
        for(It = fEngine->GetAvailableInputPlugs()->begin(); It != fEngine->GetAvailableInputPlugs()->end(); ++It)
        {
            PluginList.push_back((*It).first);
        }

        CSelectDialog SelectionDlg(wxString(i8n("Select input plugins to use"), wxConvUTF8), PluginList);
        SelectionDlg.Show(true);
    }


    void CMainInterface::GetSelectedFiles(std::list<std::string>& fl)
    {
        unsigned int PagesNb = fFoundFiles->GetPageCount();

        for(unsigned int i = 0; i < PagesNb; ++i)
        {
            wxWindow* Win = fFoundFiles->GetPage(i);
            wxCheckListCtrl* List = (wxCheckListCtrl*) Win;
            int ItemsNb = List->GetItemCount();

            for(int j = 0; j < ItemsNb; ++j)
            {
                wxListItem Item;
                Item.SetId(j);
                if(List->GetItem(Item))
                {
                    if(Item.GetImage() == 0)
                    {
                        wxString Temp = Item.m_text;
                        std::string File(Temp.ToAscii());
                        fl.push_back(File);
                    }
                }
                else
                {
                    std::cerr << i8n("[ERR] CMainInterface::GetSelectedFiles GetItem !!") << '\n';
                }
            }
        }
    }
}
