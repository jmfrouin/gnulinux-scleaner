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

#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <config.h>
#include <string>
#include <set>
#include <sstream>
#include <sys/stat.h>
#include <plugins/plugin_manager.h>
#include <plugins/plugin.h>
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
#include <wx/generic/aboutdlgg.h>
#include <wx/aboutdlg.h>

#include "maininterface.h"
#include "checklistctrl.h"
#include "result_checklistctrl.h"
#include "select_dialog.h"
#include "preferences.h"
#include "systeminfos.h"
#include "review.h"
#include  "notif.h"

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

    EVT_NOTEBOOK_PAGE_CHANGED(ID_MAININTERFACE_NOTEBOOK, CMainInterface::OnNotebook)

  //Menu
    EVT_MENU(ID_MENU_SCAN, CMainInterface::OnScan)
    EVT_MENU(ID_MENU_ABOUT, CMainInterface::OnAbout)
    EVT_MENU(ID_MENU_SYSTEM_INFOS, CMainInterface::OnSystemInfos)
    EVT_MENU(ID_MENU_PREFS, CMainInterface::OnPrefs)
    EVT_MENU(wxID_EXIT, CMainInterface::OnQuit)
    EVT_MENU(ID_MAININTERFACE_PROCESS, CMainInterface::OnProcess)
    EVT_MENU(ID_SELECT, CMainInterface::OnSelect)

  //ListBook
    EVT_BUTTON(ID_BUTTON_FOLDER_INC_ADD, CMainInterface::OnFolderIncAdd)
    EVT_BUTTON(ID_BUTTON_FOLDER_INC_DEL, CMainInterface::OnFolderIncDel)
    EVT_BUTTON(ID_BUTTON_FOLDER_EX_ADD, CMainInterface::OnFolderExAdd)
    EVT_BUTTON(ID_BUTTON_FOLDER_EX_DEL, CMainInterface::OnFolderExDel)

    END_EVENT_TABLE()

    CMainInterface::CMainInterface()
  {
    Init();
  }

  CMainInterface::CMainInterface(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style):
  fFoundFiles(0), fToolBar(0), fStatusBar(0), fAui(0), fFolders(0), fAddedFolders(0), fExcludedFolders(0), fInputPlugins(0), fOutputPlugins(0), fProgress(0), fSettings(0)
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
      delete fIcon;
    #if defined(__WXCOCOA__)
    if(fDockIcon)
      delete fDockIcon;
    #endif
    //Save perspective
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
      std::cout << i8n("[ERR] Could not set icon.\n");

    //Show splash
    if(fSettings->GetShowSplash())
      LaunchSplash(5000);
  }

  void CMainInterface::LaunchSplash(int delay)
  {
    //Splash
    wxBitmap bitmap;

    if(bitmap.LoadFile(_T("/usr/share/doc/scleaner/splash.png")), wxBITMAP_TYPE_PNG)
      new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, delay, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxSTAY_ON_TOP);
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
    wxMenuItem* Prefs = new wxMenuItem(Edit, ID_MENU_PREFS, wxString(i8n("Preferences\tCtrl-P"), wxConvUTF8));
    Prefs->SetBitmap(menu_prefs_xpm);
    Edit->Append(Prefs);

    //Misc menu
    MenuBar->Append(Misc, wxString(i8n("Misc"), wxConvUTF8));
    wxMenuItem* About = new wxMenuItem(Misc, ID_MENU_ABOUT, wxString(i8n("About"), wxConvUTF8));
    About->SetBitmap(menu_about_xpm);
    wxMenuItem* SystemInfos = new wxMenuItem(Misc, ID_MENU_SYSTEM_INFOS, wxString(i8n("System informations"), wxConvUTF8));
    Misc->Append(SystemInfos);
    Misc->Append(About);

    Frame->SetMenuBar(MenuBar);

    //Toolbar
    if(fSettings->GetShowToolbar() == true)
    {
      fToolBar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_MAININTERFACE_TOOLBAR );
      fToolBar->AddTool(ID_MENU_SCAN, wxString(i8n("Use input plugins to find files."), wxConvUTF8), scan_xpm, scan_xpm, wxITEM_NORMAL, wxString(i8n("Use input plugins to find files."), wxConvUTF8), wxEmptyString);
      fToolBar->AddTool(ID_MAININTERFACE_PROCESS, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8),run_xpm , run_xpm, wxITEM_NORMAL, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8), wxEmptyString);
      fToolBar->EnableTool(ID_MAININTERFACE_PROCESS, false);
      fToolBar->AddSeparator();
      fToolBar->AddTool(ID_MENU_PREFS, wxString(i8n("Preferences"), wxConvUTF8), prefs_xpm , prefs_xpm, wxITEM_NORMAL, wxString(i8n("Preferences"), wxConvUTF8), wxEmptyString);
      fToolBar->AddSeparator();
      fToolBar->AddTool(wxID_EXIT, wxString(i8n("Quit"), wxConvUTF8),exit_xpm , exit_xpm, wxITEM_NORMAL, wxString(i8n("Quit"), wxConvUTF8), wxEmptyString);
      fToolBar->Realize();
      Frame->SetToolBar(fToolBar);
    }

    //AuiNotebook
    fAui = new wxAuiNotebook(Frame, ID_MAININTERFACE_AUI, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE|wxAUI_NB_SCROLL_BUTTONS);

    //Folder AuiNotebook page
    int Flags = wxBK_TOP | wxNB_MULTILINE | wxDOUBLE_BORDER | wxNB_LEFT;
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

    fInputPlugins->Hide();

    int Counter=0;
    std::map<std::string, Plugins::IInPlugin*>::iterator It;
    for(It = fEngine->GetAvailableInputPlugs()->begin(); It != fEngine->GetAvailableInputPlugs()->end(); ++It)
    {
      wxString String(((*It).second)->GetName().c_str(), wxConvUTF8);
      wxString Description(((*It).second)->Description().c_str(), wxConvUTF8);
      long LongTmp = fInputPlugins->InsertItem(Counter++, String, 0);
      fInputPlugins->SetItem(LongTmp, 1, Description);
    }
    fInputPlugins->Show();
    fInputPlugins->SetColumnWidth(0, wxLIST_AUTOSIZE);
    fInputPlugins->SetColumnWidth(1, wxLIST_AUTOSIZE);

    fAui->AddPage(fInputPlugins, wxString(i8n("Input plugins"), wxConvUTF8), false);

    //Output plugins
    wxString Output[1];
    Output[0] = _("tbz");
    fOutputPlugins = new wxRadioBox(fAui, wxID_ANY, wxString(i8n("Output plugins :"), wxConvUTF8), wxDefaultPosition, wxDefaultSize, 1, Output);

    fAui->AddPage(fOutputPlugins, wxString(i8n("Output plugins"), wxConvUTF8), false);

    //Found files AuiNotebook page
    //FIXME: Display it only when "scan" has been launched
    fFoundFiles = new wxNotebook(fAui, ID_MAININTERFACE_NOTEBOOK, wxDefaultPosition, wxDefaultSize, Flags);
    fAui->AddPage(fFoundFiles, wxString(i8n("Founded files"), wxConvUTF8), false);
    
    if(fSettings->GetShowStatusbar() == true)
    {
      fStatusBar = new wxStatusBar(Frame, ID_MAININTERFACE_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
      fStatusBar->SetFieldsCount(6);
      Frame->SetStatusBar(fStatusBar);

      if(fEngine->IsRoot())
        SetStatusText(wxString(i8n("Launched as root/sudo"), wxConvUTF8), 2);
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

    //Load perspective
  }

  bool CMainInterface::ShowToolTips()
  {
    return true;
  }

  wxBitmap CMainInterface::GetBitmapResource(const wxString& name)
  {
    wxUnusedVar(name);
    return wxNullBitmap;
  }

  wxIcon CMainInterface::GetIconResource(const wxString& name)
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

      Interface::CNotif TotalNotif("scleaner", Total);
      TotalNotif.Display();
    }
  }

  //Menu
  void CMainInterface::OnAbout(wxCommandEvent& WXUNUSED(event))
  {
    wxAboutDialogInfo info;

    info.AddArtist(_T("Splash: Medina Bastien"));
    info.AddArtist(_T("Icons: Marco Martin (mart@notmart.org), www.notmart.org"));
    info.AddDeveloper(_T("Original & main developper: Jean-Michel Frouin"));
    info.AddDeveloper(_T("Website : Pierre Jacquier"));
    info.AddTranslator(_T("French: Jean-Michel Frouin"));
    info.AddTranslator(_T("German: Peer Voss"));
    info.AddTranslator(_T("Italian: David Paleino"));
    info.SetDescription(_T("simple GNU/Linux cleaner"));
    info.AddDeveloper(_T("Portion code (c) ... to finish"));
    info.SetName(_T(NAME));
    info.SetLicence(wxString::FromAscii(
      "scleaner a simple GNU/Linux cleaner\n\n"
      "Copyright (C) 2007, 2008 Jean-Michel Frouin\n\n"
      "This program is free software: you can redistribute it and/or modify\n"
      "it under the terms of the GNU General Public License as published by\n"
      "the Free Software Foundation, either version 3 of the License, or\n"
      "any later version.\n"
      "\n"
      "This program is distributed in the hope that it will be useful,\n"
      "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
      "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
      "GNU General Public License for more details.\n"
      "\n"
      "You should have received a copy of the GNU General Public License\n"
      "along with this program.  If not, see http://www.gnu.org/licenses/.\n"));
    info.SetWebSite(_T("http://www.scleaner.org/"), _T("scleaner website"));

    wxAboutBox(info);
  }

  void CMainInterface::OnSystemInfos(wxCommandEvent& WXUNUSED(event))
  {
    CSystemInfos SystemInfos(this, wxID_ANY, wxString(i8n("System Informations"), wxConvUTF8), SYMBOL_POSITION, SYMBOL_DIALOG_SIZE);
    SystemInfos.ShowModal();
  }

  void CMainInterface::OnQuit(wxCommandEvent& WXUNUSED(event))
  {
    Close(true);
  }

  //Toolbar
  void CMainInterface::OnScan(wxCommandEvent& WXUNUSED(event))
  {
    fFoundFiles->DeleteAllPages();
    fProgress = new wxProgressDialog(wxString(i8n("scleaner scan your disk ..."), wxConvUTF8),
      wxString(i8n("this is a information"), wxConvUTF8), 100, this,
                                 // - makes indeterminate mode bar on WinXP very small
      wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME | wxPD_SMOOTH
      );

    fEngine->ScanDisk(this);

    fToolBar->EnableTool(ID_MAININTERFACE_PROCESS, true);
    delete fProgress;
    fProgress = 0;

    //Build files list
    fProgress = new wxProgressDialog(wxString(i8n("scleaner construct files' list"), wxConvUTF8),
      wxString(i8n("this is a information"), wxConvUTF8), 100, this,
                                 // - makes indeterminate mode bar on WinXP very small
      wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME | wxPD_SMOOTH
      );

    double Totalsize = 0;
    // Happend plugins' name available
    std::map<std::string, Plugins::IInPlugin*>* SelInpPlug = fEngine->GetSelectedInputPlugs(true);
    std::map<std::string, Plugins::IInPlugin*>::iterator It = SelInpPlug->begin();
    for(; It != SelInpPlug->end(); ++It)
    {
      wxString String((It->second)->GetName().c_str(), wxConvUTF8);

      std::list<std::string> List;
      It->second->GetFileList(List);
      std::cout << "List : " << List.size() << '\n';
      List.sort();
      std::cout << "List : " << List.size() << '\n';

      #if defined DEBUG && defined VERBOSE
      //std::cout << CYAN << "For plugin : " << It->second->GetName() << " size = " << List.size() << STOP << '\n';
      #endif
      ResultCheckListCtrl* FilesList = new ResultCheckListCtrl(fFoundFiles, ID_RESCHECKLIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxSUNKEN_BORDER | wxLC_VRULES | wxLC_HRULES);

      //Setting header:
      wxListItem ItemCol;
      ItemCol.SetText(wxString(i8n("File location"), wxConvUTF8));
      ItemCol.SetImage(-1);
      FilesList->InsertColumn(0, ItemCol);

      ItemCol.SetText(wxString(i8n("Size (bytes)"), wxConvUTF8));
      ItemCol.SetAlign(wxLIST_FORMAT_CENTRE);
      FilesList->InsertColumn(1, ItemCol);

      ItemCol.SetText(wxString(i8n("Folders"), wxConvUTF8));
      ItemCol.SetAlign(wxLIST_FORMAT_RIGHT);
      FilesList->InsertColumn(2, ItemCol);

      ItemCol.SetText(wxString(i8n("CRC32"), wxConvUTF8));
      ItemCol.SetAlign(wxLIST_FORMAT_RIGHT);
      FilesList->InsertColumn(3, ItemCol);

      // to speed up inserting, we hide the control temporarily
      FilesList->Hide();
      int Counter = 0;
      std::list<std::string>::iterator It2;
      for(It2 = List.begin(); It2 != List.end(); ++It2)
      {
        std::string FileName(*It2);
        wxString String2(FileName.c_str(), wxConvUTF8);
        long LongTmp = FilesList->InsertItem(Counter, String2, 0);
        FilesList->SetItemData(LongTmp, Counter);

        //Insert file size.
        struct stat Info;

        //Insert folder
        std::string FolderName = FileName.substr(0, FileName.find_last_of('/'));
        wxString Folder(FolderName.c_str(), wxConvUTF8);

        FilesList->SetItem(LongTmp, 2, Folder);

        //Try to stat file.
        if(stat(FileName.c_str(), &Info) == -1)
          std::cout << i8n("[ERR] : Cannot stat ") << FileName << '\n';
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
            FilesList->SetItem(LongTmp, 3, wxString(std::string(CRC2.str()).c_str(), wxConvUTF8));
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

      static int Count = 0;
      bool Continue = UpdateProgress(It->first, false, ((++Count)*100)/SelInpPlug->size());
      if(!Continue)
        break;
      FilesList->SetColumnWidth(0, wxLIST_AUTOSIZE);
      FilesList->SetColumnWidth(1, wxLIST_AUTOSIZE);
      FilesList->SetColumnWidth(2, wxLIST_AUTOSIZE);
      FilesList->SetColumnWidth(3, wxLIST_AUTOSIZE);
      FilesList->SetColumnWidth(4, wxLIST_AUTOSIZE);
      std::cout << "List : " << List.size() << '\n';

      FilesList->Show();
      fFoundFiles->AddPage(FilesList, String, true);
      fTotalSizes.push_back(Totalsize);
    }

    fEngine->DetectDuplicates();
    MarkDuplicatesFiles();
    fFoundFiles->AdvanceSelection();    
    delete fProgress;
    fProgress = 0;
  }

  void CMainInterface::MarkDuplicatesFiles()
  {
    std::set<unsigned long>* DupCRC = fEngine->GetDuplicatesCRC();
    std::set<unsigned long>::iterator It;
    //For each dup CRC
    for(It=DupCRC->begin(); It!=DupCRC->end(); ++It)
    {
      //For each Notebooks' page 
      // 
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
            if(!Item.GetImage())
            {
              wxString Temp = Item.m_text;
              std::string File(Temp.ToAscii());
              std::map<std::string, unsigned long>* FI = fEngine->GetFileInfos();
              if((*FI)[File] == *It)
              {
                Item.SetBackgroundColour(0xCCCCFF);
                List->SetItem(Item);
              }
            }
          }
          else
            std::cerr << i8n("[ERR] CMainInterface::GetSelectedFiles GetItem !!") << '\n';
        }
      }
    }
  }

  void CMainInterface::OnProcess(wxCommandEvent& WXUNUSED(event))
  {
    std::list<std::string> SelectionectedFiles;
    GetSelectedFiles(SelectionectedFiles);

    CReview Review(&SelectionectedFiles, this, wxID_ANY, wxString(i8n("Review your choice"), wxConvUTF8), wxDefaultPosition, wxSize(600,600));
    Review.ShowModal();

    #if defined DEBUG && defined VERBOSE
    Log::CLog::Instance()->Log(__FILE__, __LINE__, "[DBG] You have selected: ", true);
    std::list<std::string>::iterator It;
    for(It = SelectionectedFiles.begin(); It != SelectionectedFiles.end(); ++It)
      Log::CLog::Instance()->Log(__FILE__, __LINE__, *It, true);
    #endif

    fProgress = new wxProgressDialog(wxString(i8n("scleaner process your files ..."), wxConvUTF8),
      wxString(i8n("this is an information"), wxConvUTF8),
      100,                       // range
      this,                      // parent
      wxPD_CAN_ABORT |
    // wxPD_CAN_SKIP |
      wxPD_APP_MODAL |
    //wxPD_AUTO_HIDE | -- try this as well
      wxPD_ELAPSED_TIME |
      wxPD_ESTIMATED_TIME |
      wxPD_REMAINING_TIME
      | wxPD_SMOOTH              // - makes indeterminate mode bar on WinXP very small
      );

    std::string Name;
    wxString NameWX;
    NameWX = fOutputPlugins->GetStringSelection();
    Name = NameWX.char_str();

    #if defined DEBUG
    std::cout << i8n("[DBG] CMainInterface : Get selection : ") << Name << '\n';
    #endif

    wxString Message;
    if(Engine::CEngine::IsRoot())
      Message = _T("/root/");
    else
    {
      std::string Path("/home");
      std::string UserName;
      Engine::CEngine::GetUsername(UserName);
      Path += "/" + UserName;
      Message.FromUTF8(Path.c_str());
    }

    wxDirDialog OutputFileDlg(this, wxString(i8n("Select a folder"), wxConvUTF8)/* + NameWX + wxString(i8n(" plugin:"), wxConvUTF8)*/, Message, wxDD_DIR_MUST_EXIST);

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
      Sizer2->Add(new wxButton(fFolders, ID_BUTTON_FOLDER_INC_ADD, _T("Add")), 0, wxALIGN_CENTER | wxALL, 2);
      Sizer2->Add(new wxButton(fFolders, ID_BUTTON_FOLDER_INC_DEL, _T("Remove")), 0, wxALIGN_CENTER | wxALL, 2);

      Sizer->Add(Sizer2, 0, wxGROW | wxALL, 5);

      if(fSettings->GetRecursiveScan())
      {
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
        Sizer2->Add(new wxButton(fFolders, ID_BUTTON_FOLDER_EX_ADD, _T("Add")), 0, wxALIGN_CENTER | wxALL, 2);
        Sizer2->Add(new wxButton(fFolders, ID_BUTTON_FOLDER_EX_DEL, _T("Remove")), 0, wxALIGN_CENTER | wxALL, 2);
  
        Sizer->Add(Sizer2, 0, wxGROW | wxALL, 5);
      }
    }

    //First clear lists
    if(fAddedFolders)
      fAddedFolders->DeleteAllItems();

    if(fSettings->GetRecursiveScan())
      if(fExcludedFolders)
        fExcludedFolders->DeleteAllItems();

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

    if(fSettings->GetRecursiveScan())
    {
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
  }

  void CMainInterface::OnFolderIncAdd(wxCommandEvent& WXUNUSED(event))
  {
    wxString Message;
    wxDirDialog AddDlg(this, wxString(i8n("Select a folder to add to scan"), wxConvUTF8), Message, wxDD_DIR_MUST_EXIST);
    if(AddDlg.ShowModal() == wxID_OK)
    {
      std::string SelectionPath(AddDlg.GetPath().char_str());
      std::string Parent;
      //std::cout << SelectionPath << '\n';
      if(!fSettings->AddFolder(SelectionPath, Parent, Engine::CSettingsManager::eFoldersInc))
      {
        wxString Text(i8n("I cannot add \""), wxConvUTF8);
        Text += wxString(SelectionPath.c_str(), wxConvUTF8);
        Text += wxString(i8n("\" since \""), wxConvUTF8);
        Text += wxString(Parent.c_str(), wxConvUTF8);
        Text += wxString(i8n("\" is already in the folders list."), wxConvUTF8);

        wxMessageBox(Text, wxString(i8n("scleaner information"), wxConvUTF8), wxICON_INFORMATION);
      }
      else
        UpdateFolderList();
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
      UpdateFolderList();
  }

  void CMainInterface::OnFolderExAdd(wxCommandEvent& WXUNUSED(event))
  {
    wxString Message;
    wxDirDialog AddDlg(this, wxString(i8n("Select a folder to add to scan"), wxConvUTF8), Message, wxDD_DIR_MUST_EXIST);
    if(AddDlg.ShowModal() == wxID_OK)
    {
      std::string SelectionPath(AddDlg.GetPath().char_str());
      std::string Parent;
      if(!fSettings->AddFolder(SelectionPath, Parent, Engine::CSettingsManager::eFoldersEx))
      {
        wxString Text(i8n("I cannot add \""), wxConvUTF8);
        Text += wxString(SelectionPath.c_str(), wxConvUTF8);
        Text += wxString(i8n("\" since \""), wxConvUTF8);
        Text += wxString(Parent.c_str(), wxConvUTF8);
        Text += wxString(i8n("\" is already in the folders list."), wxConvUTF8);

        wxMessageBox(Text, wxString(i8n("scleaner information"), wxConvUTF8), wxICON_INFORMATION);
      }
      else
        UpdateFolderList();
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
      UpdateFolderList();
  }

  void CMainInterface::OnPrefs(wxCommandEvent& WXUNUSED(event))
  {
    CPreferences(this, wxID_ANY, wxString(i8n("Preferences"), wxConvUTF8), wxDefaultPosition, wxSize(600,300)).ShowModal();
  }

  bool CMainInterface::UpdateProgress(const std::string& mess, bool pulse, int nb)
  {
    wxString Message(mess.c_str(), wxConvUTF8);
    bool Continue;
    if(pulse)
      Continue = fProgress->Pulse(Message, 0);
    else
      Continue = fProgress->Update(nb, Message, 0);

    if(!Continue)
    {
      if ( wxMessageBox(_T("Do you really want to cancel?"), _T("scleaner question"), wxYES_NO | wxICON_QUESTION) == wxNO)
      {
        Continue = true;
        fProgress->Resume();
        return true;
      }
      else
        return false;
    }
    else
      return true;
  }

  void CMainInterface::OnSelect(wxCommandEvent& WXUNUSED(event))
  {
    //GetToolBar()->SetToolShortHelp(wxID_NEW, _T("New toolbar button"));
    wxMessageDialog(this, wxString(i8n("Since for this alpha version, there are only 3 input plugins (and 2 that run only in root mode), the dialog for selecting input plugins is not yet ready :D but will be available soon !!"), wxConvUTF8), _T("scleaner"), wxOK | wxICON_EXCLAMATION).ShowModal();

    std::list<std::string> PluginList;

    std::map<std::string, Plugins::IInPlugin*>::iterator It;
    for(It = fEngine->GetAvailableInputPlugs()->begin(); It != fEngine->GetAvailableInputPlugs()->end(); ++It)
    PluginList.push_back((*It).first);

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
          std::cerr << i8n("[ERR] CMainInterface::GetSelectedFiles GetItem !!") << '\n';
      }
    }
  }
}

/*
wxString wxAuiNotebook::SavePerspective() {
   // Build list of panes/tabs
   wxString tabs;
   wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    const size_t pane_count = all_panes.GetCount();

    for (size_t i = 0; i < pane_count; ++i)
    {
      wxAuiPaneInfo& pane = all_panes.Item(i);
      if (pane.name == wxT("dummy"))
            continue;

        wxTabFrame* tabframe = (wxTabFrame*)pane.window;
      
      if (!tabs.empty()) tabs += wxT("|");
      tabs += pane.name;
      tabs += wxT("=");
      
      // add tab id's
      size_t page_count = tabframe->m_tabs->GetPageCount();
      for (size_t p = 0; p < page_count; ++p)
      {
         wxAuiNotebookPage& page = tabframe->m_tabs->GetPage(p);
         const size_t page_idx = m_tabs.GetIdxFromWindow(page.window);
         
         if (p) tabs += wxT(",");

         if ((int)page_idx == m_curpage) tabs += wxT("*");
         else if ((int)p == tabframe->m_tabs->GetActivePage()) tabs += wxT("+");
         tabs += wxString::Format(wxT("%u"), page_idx);
      }
   }
   tabs += wxT("@");

   // Add frame perspective
   tabs += m_mgr.SavePerspective();

   return tabs;
}

bool wxAuiNotebook::LoadPerspective(const wxString& layout) {
   // Remove all tab ctrls (but still keep them in main index)
   const size_t tab_count = m_tabs.GetPageCount();
   for (size_t i = 0; i < tab_count; ++i) {
      wxWindow* wnd = m_tabs.GetWindowFromIdx(i);

      // find out which onscreen tab ctrl owns this tab
      wxAuiTabCtrl* ctrl;
      int ctrl_idx;
      if (!FindTab(wnd, &ctrl, &ctrl_idx))
         return false;

      // remove the tab from ctrl
      if (!ctrl->RemovePage(wnd))
         return false;
   }
   RemoveEmptyTabFrames();

   size_t sel_page = 0;
   
   wxString tabs = layout.BeforeFirst(wxT('@'));
   while (1)
    {
      const wxString tab_part = tabs.BeforeFirst(wxT('|'));
      
      // if the string is empty, we're done parsing
        if (tab_part.empty())
            break;

      // Get pane name
      const wxString pane_name = tab_part.BeforeFirst(wxT('='));

      // create a new tab frame
      wxTabFrame* new_tabs = new wxTabFrame;
      new_tabs->m_tabs = new wxAuiTabCtrl(this,
                                 m_tab_id_counter++,
                                 wxDefaultPosition,
                                 wxDefaultSize,
                                 wxNO_BORDER|wxWANTS_CHARS);
      new_tabs->m_tabs->SetArtProvider(m_tabs.GetArtProvider()->Clone());
      new_tabs->SetTabCtrlHeight(m_tab_ctrl_height);
      new_tabs->m_tabs->SetFlags(m_flags);
      wxAuiTabCtrl *dest_tabs = new_tabs->m_tabs;

      // create a pane info structure with the information
      // about where the pane should be added
      wxAuiPaneInfo pane_info = wxAuiPaneInfo().Name(pane_name).Bottom().CaptionVisible(false);
      m_mgr.AddPane(new_tabs, pane_info);

      // Get list of tab id's and move them to pane
      wxString tab_list = tab_part.AfterFirst(wxT('='));
      while(1) {
         wxString tab = tab_list.BeforeFirst(wxT(','));
         if (tab.empty()) break;
         tab_list = tab_list.AfterFirst(wxT(','));

         // Check if this page has an 'active' marker
         const wxChar c = tab[0];
         if (c == wxT('+') || c == wxT('*')) {
            tab = tab.Mid(1);
         }

         const size_t tab_idx = wxAtoi(tab.c_str());
         if (tab_idx >= GetPageCount()) continue;

         // Move tab to pane
         wxAuiNotebookPage& page = m_tabs.GetPage(tab_idx);
         const size_t newpage_idx = dest_tabs->GetPageCount();
         dest_tabs->InsertPage(page.window, page, newpage_idx);

         if (c == wxT('+')) dest_tabs->SetActivePage(newpage_idx);
         else if ( c == wxT('*')) sel_page = tab_idx;
      }
      dest_tabs->DoShowHide();

      tabs = tabs.AfterFirst(wxT('|'));
   }
   
   // Load the frame perspective
   const wxString frames = layout.AfterFirst(wxT('@'));
   m_mgr.LoadPerspective(frames);

   // Force refresh of selection
   m_curpage = -1;
   SetSelection(sel_page);

   return true;
}

*/
