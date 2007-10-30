/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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
#include "select_dialog.h"
#include "preferences.h"

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
	EVT_MENU(ID_FOLDER_ADD, CMainInterface::OnFolderAdd)
	EVT_MENU(ID_FOLDER_DEL, CMainInterface::OnFolderDel)
	EVT_MENU(ID_PREFS, CMainInterface::OnPrefs)
	EVT_MENU(wxID_EXIT, CMainInterface::OnQuit)
	EVT_MENU(ID_PROCESS, CMainInterface::OnProcess)
	EVT_MENU(ID_SELECT, CMainInterface::OnSelect)
	END_EVENT_TABLE()
	
	CMainInterface::CMainInterface()
	{
		Init();
	}
	
	
	CMainInterface::CMainInterface(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style):
	m_Input(0), m_StatusBar(0), m_Aui(0), m_Folders(0), m_AddedFolders(0), m_ExcludedFolders(0), m_Progress(0)
	{
		Init();
		Create(parent, id, caption, pos, size, style);
	}
	
	
	bool CMainInterface::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
	{
		wxFrame::Create( parent, id, caption, pos, size, style );
	
		//Retrieve Engine::CEngine instance pointer.
		m_Engine = Engine::CEngine::Instance();
	
		CreateControls();
		Centre();
	
	  	SetIcon(wxICON(scleaner));
		return true;
	}
	
	
	CMainInterface::~CMainInterface()
	{
		delete m_Icon;
		#if defined(__WXCOCOA__)
		delete m_DockIcon;
		#endif
	}
	
	
	void CMainInterface::Init()
	{
		//Tray icon !!
		m_Icon = new CTrayIcon();
		#if defined(__WXCOCOA__)
		m_DockIcon = new CTrayIcon(wxTaskBarIcon::DOCK);
		#endif
	
		m_Icon->setParent(this);
	
		if (!m_Icon->SetIcon(scleaner_xpm, wxT(NAME)))
		{
			std::cout << i8n("[ERR] Could not set icon.\n");
		}
		launchSplash(1000);
	}
	
	
	void CMainInterface::launchSplash(int _delay)
	{
		#if defined(SPLASH)
		//Splash
		wxBitmap bitmap;
	
		if(bitmap.LoadFile(_T("/usr/share/doc/scleaner/splash.png")), wxBITMAP_TYPE_PNG)
		{
			//Bitmap successfully loaded
			new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, _delay, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxSTAY_ON_TOP);
		}
		#endif
	}
	
	
	void CMainInterface::CreateControls()
	{
		CMainInterface* l_Frame = this;
	
		//MENU
		wxMenuBar* l_MenuBar = new wxMenuBar;
		wxMenu* l_File = new wxMenu;
		wxMenu* l_Edit = new wxMenu;
		wxMenu* l_Misc = new wxMenu;
	
		//File menu
		l_MenuBar->Append(l_File, wxString(i8n("File"), wxConvUTF8));
		wxMenuItem* l_Add = new wxMenuItem(l_File, ID_FOLDER_ADD, wxString(i8n("&Add a folder to scan\tCtrl-A"), wxConvUTF8));
	    l_Add->SetBitmap(menu_add_folder_xpm);
		wxMenuItem* l_Del = new wxMenuItem(l_File, ID_FOLDER_DEL, wxString(i8n("&Remove selected folders from scan\tCtrl-D"), wxConvUTF8));
	    l_Del->SetBitmap(menu_del_folder_xpm);
		l_File->Append(l_Add);
		l_File->Append(l_Del);
		l_File->AppendSeparator();
		wxMenuItem* l_Quit = new wxMenuItem(l_File, wxID_EXIT, wxString(i8n("Quit"), wxConvUTF8));
		l_File->Append(l_Quit);
	
		//Folders menu
		l_MenuBar->Append(l_Edit, wxString(i8n("Edit"), wxConvUTF8));
		wxMenuItem* l_Prefs = new wxMenuItem(l_Edit, ID_PREFS, wxString(i8n("Preferences\tCtrl-P"), wxConvUTF8));
	    l_Prefs->SetBitmap(menu_prefs_xpm);
		l_Edit->Append(l_Prefs);
	
		//Misc menu
		l_MenuBar->Append(l_Misc, wxString(i8n("Misc"), wxConvUTF8));
		wxMenuItem* l_About = new wxMenuItem(l_Misc, ID_ABOUT, wxString(i8n("About"), wxConvUTF8));
	    l_About->SetBitmap(menu_about_xpm);
		l_Misc->Append(l_About);
	
		l_Frame->SetMenuBar(l_MenuBar);
	
		//TOOLBAR
		//l_ToolBar->SetMargins(4, 4);
	
		//l_Frame->SetToolBar(l_ToolBar);
		wxToolBar* l_ToolBar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR1 );
		l_ToolBar->AddTool(ID_SELECT, wxString(i8n("Select input plugins to use."), wxConvUTF8), select_xpm, select_xpm, wxITEM_NORMAL, wxString(i8n("Select input plugins to use."), wxConvUTF8), wxEmptyString);
		l_ToolBar->AddTool(ID_SCAN, wxString(i8n("Use input plugins to find files."), wxConvUTF8), scan_xpm, scan_xpm, wxITEM_NORMAL, wxString(i8n("Use input plugins to find files."), wxConvUTF8), wxEmptyString);
		l_ToolBar->AddTool(ID_PROCESS, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8),run_xpm , run_xpm, wxITEM_NORMAL, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8), wxEmptyString);
		l_ToolBar->AddSeparator();
		l_ToolBar->AddTool(ID_PREFS, wxString(i8n("Preferences"), wxConvUTF8), prefs_xpm , prefs_xpm, wxITEM_NORMAL, wxString(i8n("Preferences"), wxConvUTF8), wxEmptyString);
		l_ToolBar->AddSeparator();
		l_ToolBar->AddTool(wxID_EXIT, wxString(i8n("Quit"), wxConvUTF8),exit_xpm , exit_xpm, wxITEM_NORMAL, wxString(i8n("Quit"), wxConvUTF8), wxEmptyString);
		l_ToolBar->Realize();
		l_Frame->SetToolBar(l_ToolBar);
	
    	m_Aui = new wxAuiNotebook(l_Frame, ID_AUI, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE|wxAUI_NB_SCROLL_BUTTONS);
	
		//Input plugins
		int l_flags = wxBK_TOP | wxNB_MULTILINE | wxDOUBLE_BORDER;
		
		UpdateFolderList();

    	m_Aui->AddPage(m_Folders, wxString(i8n("Folders"), wxConvUTF8), false);

		m_Input = new wxNotebook(m_Aui, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, l_flags);
    	m_Aui->AddPage(m_Input, wxString(i8n("Found files"), wxConvUTF8), false);
	
		m_StatusBar = new wxStatusBar(l_Frame, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
		m_StatusBar->SetFieldsCount(6);
		l_Frame->SetStatusBar(m_StatusBar);
	
		if(m_Engine->isRoot())
		{
			SetStatusText(wxString(i8n("Launched as root/sudo"), wxConvUTF8), 2);
		}
		else
		{
			std::string l_username;
			m_Engine->getUsername(l_username);
			wxString l_uusername(l_username.c_str(), wxConvUTF8);
			SetStatusText(wxString(i8n("Launched as "), wxConvUTF8) + l_uusername, 2);
		}
	
		std::string l_version = i8n("Kernel : v");
		m_Engine->getKernelVersion(l_version);
		wxString l_uversion(l_version.c_str(), wxConvUTF8);
		SetStatusText(l_uversion, 1);
		std::string l_path, l_used(i8n("Used: ")), l_free(i8n("Free: ")), l_total(i8n("Total: "));
		m_Engine->getFreeSpace(l_path, l_used, l_free, l_total);
		wxString l_utotal(l_total.c_str(), wxConvUTF8);
		SetStatusText(l_utotal, 3);
		wxString l_uused(l_used.c_str(), wxConvUTF8);
		SetStatusText(l_uused, 4);
		wxString l_ufree(l_free.c_str(), wxConvUTF8);
		SetStatusText(l_ufree, 5);
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
		wxString l_name;
		int l_sel = event.GetSelection();
		l_name  = m_Input->GetPageText(l_sel);
		std::stringstream l_tot;
		if(m_TotalSizes.size() > 0)
		{
			std::string l_total(i8n("Total size : "));
			Engine::CEngine::Instance()->formatSize(m_TotalSizes[l_sel], l_total);
			wxString l_totalsize(l_total.c_str(), wxConvUTF8);
			SetStatusText(l_totalsize, 0);
		}
	}
	
	
	//Menu
	void CMainInterface::OnAbout(wxCommandEvent& WXUNUSED(event))
	{
		launchSplash(3000);
	}
	
	
	void CMainInterface::OnQuit(wxCommandEvent& WXUNUSED(event))
	{
		Close(true);
	}
	
	
	//Toolbar
	void CMainInterface::OnScan(wxCommandEvent& WXUNUSED(event))
	{
		m_Input->DeleteAllPages();
		m_Progress = new wxProgressDialog(wxString(i8n("scleaner scan your disk ..."), wxConvUTF8),
			wxString(i8n("this is a information"), wxConvUTF8),
			100,					 // range
			this,					 // parent
			//wxPD_CAN_ABORT |
			// wxPD_CAN_SKIP |
			wxPD_APP_MODAL |
		 	wxPD_AUTO_HIDE | 
			wxPD_ELAPSED_TIME |
			wxPD_ESTIMATED_TIME |
			wxPD_REMAINING_TIME
			| wxPD_SMOOTH			 // - makes indeterminate mode bar on WinXP very small
			);
	
		m_Engine->scanDisk(this);
	
		delete m_Progress;
		m_Progress = 0;
	
		double l_totalsize = 0;
		// Happend plugins' name available
		std::map<std::string, Plugins::IInPlugin*>::iterator _it;
		for(_it = m_Engine->getAvailableInputPlugs()->begin(); _it != m_Engine->getAvailableInputPlugs()->end(); ++_it)
		{
			wxString l_str(((*_it).second)->getName().c_str(), wxConvUTF8);
	
			std::list<std::string> l_list;
			((*_it).second)->getFileList(l_list);
			l_list.sort();
			std::list<std::string>::iterator _it2;
	
			
			#if defined DEBUG
			std::cout << i8n("[DBG] Size = ") << l_list.size() << '\n';
			#endif
			wxCheckListCtrl* l_fileslist = new wxCheckListCtrl(m_Input, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxSUNKEN_BORDER | wxLC_VRULES | wxLC_HRULES);
	
			//Setting header:
			wxListItem l_itemCol;
			l_itemCol.SetText(wxString(i8n("File location"), wxConvUTF8));
			l_itemCol.SetImage(-1);
			l_fileslist->InsertColumn(0, l_itemCol);
	
			l_itemCol.SetText(wxString(i8n("Size (bytes)"), wxConvUTF8));
			l_itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
			l_fileslist->InsertColumn(1, l_itemCol);
	
			l_itemCol.SetText(wxString(i8n("CRC32"), wxConvUTF8));
			l_itemCol.SetAlign(wxLIST_FORMAT_RIGHT);
			l_fileslist->InsertColumn(2, l_itemCol);
	
			// to speed up inserting we hide the control temporarily
			l_fileslist->Hide();
	
			int l_counter = 0;
			for(_it2 = l_list.begin(); _it2 != l_list.end(); ++_it2)
			{
				std::string l_filename(*_it2);
				wxString l_str2(l_filename.c_str(), wxConvUTF8);
				long l_tmp = l_fileslist->InsertItem(l_counter, l_str2, 0);
				l_fileslist->SetItemData(l_tmp, l_counter);
	
				//Insert file size.
				struct stat l_info;
	
				//Try to stat file.
				if(stat(l_filename.c_str(), &l_info) == -1)
				{
					std::cout << i8n("[ERR] : Cannot stat ") << l_filename << '\n';
				}
				else
				{
					
					l_totalsize += l_info.st_size;
					std::string l_size;
					m_Engine->formatSize(l_info.st_size, l_size);
					wxString l_usize(l_size.c_str(), wxConvUTF8);
					l_fileslist->SetItem(l_tmp, 1, l_usize);
	
					if(l_info.st_size != 0)
					{
						unsigned long l_crc;
						Engine::CEngine::calcCRC32(l_filename, l_crc);
						std::stringstream l_crc2;
						l_crc2 << l_crc;
						l_fileslist->SetItem(l_tmp, 2, wxString(std::string(l_crc2.str()).c_str(), wxConvUTF8));
						m_Engine->addFileInfo(l_filename, l_crc);
					}
					else
					{
						l_fileslist->SetItem(l_tmp, 2, wxString(_T("No CRC32")));
						m_Engine->addFileInfo(l_filename, 0);
					}
				}
				++l_counter;
			}
	
			l_fileslist->SetColumnWidth(0, wxLIST_AUTOSIZE);
			l_fileslist->SetColumnWidth(1, wxLIST_AUTOSIZE);
			l_fileslist->SetColumnWidth(2, wxLIST_AUTOSIZE);
	
			l_fileslist->Show();
			m_Input->AddPage(l_fileslist, l_str, true);
			m_TotalSizes.push_back(l_totalsize);
		}
	
		m_Input->AdvanceSelection();
		m_Engine->detectDuplicates();
	}
	
	
	void CMainInterface::OnProcess(wxCommandEvent& WXUNUSED(event))
	{
		//GetToolBar()->SetToolShortHelp(wxID_NEW, _T("New toolbar button"));
		#if defined DEBUG
		std::cout << i8n("[DBG] Process !!! ") << '\n';
		#endif
		std::list<std::string> l_selected_files;
		//GetSelectedFilesRecursively(m_Input->GetRootItem(), l_selected_files);
		GetSelectedFiles(l_selected_files);
	
		#if defined DEBUG
		std::cout << i8n("[DBG] You have selected: ") << '\n';
		std::list<std::string>::iterator l_it;
		for(l_it = l_selected_files.begin(); l_it != l_selected_files.end(); ++l_it)
		{
			std::cout << "[DBG] " << *l_it << '\n';
		}
		#endif
	
		m_Progress = new wxProgressDialog(wxString(i8n("scleaner process your files ..."), wxConvUTF8),
			wxString(i8n("this is a information"), wxConvUTF8),
			100,					 // range
			this,					 // parent
			//wxPD_CAN_ABORT |
			// wxPD_CAN_SKIP |
			wxPD_APP_MODAL |
			//wxPD_AUTO_HIDE | -- try this as well
			wxPD_ELAPSED_TIME |
			wxPD_ESTIMATED_TIME |
			wxPD_REMAINING_TIME
			| wxPD_SMOOTH			 // - makes indeterminate mode bar on WinXP very small
			);
	
		std::string l_name;
		wxString l_nameWX;
		//l_nameWX = m_Output->GetStringSelection();
		l_name = l_nameWX.char_str();
	
		#if defined DEBUG
		std::cout << i8n("[DBG] CMainInterface : Get selection : ") << l_name << '\n';
		#endif
	
		wxString l_msg;
		if(Engine::CEngine::isRoot())
		{
			l_msg = _T("/root/");
		}
		else
		{
			std::string l_path("/home");
			std::string l_username;
			Engine::CEngine::getUsername(l_username);
			l_path += "/" + l_username;
			l_msg.FromUTF8(l_path.c_str());
		}
	
		wxDirDialog l_outputFileDlg(this, wxString(i8n("Select an output folder for "), wxConvUTF8) + l_nameWX + wxString(i8n(" plugin:"), wxConvUTF8), l_msg, wxDD_DIR_MUST_EXIST);
	
		if (l_outputFileDlg.ShowModal() == wxID_OK)
		{
			std::string l_selPath(l_outputFileDlg.GetPath().char_str()); 
			m_Engine->callOutputPlugin(l_selected_files, l_name, l_selPath, this);
		}
	
		delete m_Progress;
		m_Progress = 0;
	}
	
	void CMainInterface::UpdateFolderList()
	{
		wxSizer* l_Sizer = new wxBoxSizer(wxVERTICAL);

	    if(!m_Folders)
		{
			m_Folders = new wxPanel(m_Aui, -1);
		}
		else
		{

		}
	
		m_Folders->SetSizer(l_Sizer);

		l_Sizer->Add(new wxStaticText(m_Folders, -1, _T("Folders added to scan :")), 0, wxALIGN_LEFT | wxALL, 5);

	    if(!m_AddedFolders)
		{
			m_AddedFolders = new GUI::wxCheckListCtrl(m_Folders, wxID_ANY, wxDefaultPosition, wxDefaultSize);
			//Setting header:
			wxListItem l_itemCol;
			l_itemCol.SetText(wxString(i8n("Name"), wxConvUTF8));
			l_itemCol.SetImage(-1);
			m_AddedFolders->InsertColumn(0, l_itemCol);
		}
		
		std::list<std::string>* l_fl = m_Engine->getFoldersListPtr();
		std::list<std::string>::iterator l_it;
		for(l_it = l_fl->begin(); l_it !=l_fl->end(); ++l_it)
		{
			//Maybe an alphabetic sort will be need here : algorithms :D
			long l_tmp = m_AddedFolders->InsertItem(l_fl->size(), wxString((*l_it).c_str(), wxConvUTF8), 0);
			m_AddedFolders->SetItemImage(l_tmp, 2);
			m_AddedFolders->SetItemData(l_tmp, 0);
			m_AddedFolders->SetColumnWidth(0, wxLIST_AUTOSIZE);
		}

		l_Sizer->Add(m_AddedFolders, 1, wxGROW | wxALL, 5);

		wxSizer* l_Sizer2 = new wxBoxSizer(wxHORIZONTAL);
		l_Sizer2->Add(new wxButton(m_Folders, ID_FOLDER_ADD, _T("Add")), 0, wxALIGN_CENTER | wxALL, 2);
		l_Sizer2->Add(new wxButton(m_Folders, ID_FOLDER_DEL, _T("Remove")), 0, wxALIGN_CENTER | wxALL, 2);

		l_Sizer->Add(l_Sizer2, 0, wxGROW | wxALL, 5);

		wxStaticLine* l_Line = new wxStaticLine(m_Folders, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    	l_Sizer->Add(l_Line, 0, wxGROW|wxALL, 5);

		l_Sizer->Add(new wxStaticText(m_Folders, -1, _T("Folders excluded from scan :")), 0, wxALIGN_LEFT | wxALL, 5);

	    if(!m_ExcludedFolders)
		{
			m_ExcludedFolders = new GUI::wxCheckListCtrl(m_Folders, wxID_ANY, wxDefaultPosition, wxDefaultSize);
			//Setting header:
			wxListItem l_itemCol;
			l_itemCol.SetText(wxString(i8n("Name"), wxConvUTF8));
			l_itemCol.SetImage(-1);
			m_ExcludedFolders->InsertColumn(0, l_itemCol);
		}
		
		l_fl = m_Engine->getExcludedFoldersListPtr();
		for(l_it = l_fl->begin(); l_it !=l_fl->end(); ++l_it)
		{
			//Maybe an alphabetic sort will be need here : algorithms :D
			long l_tmp = m_ExcludedFolders->InsertItem(l_fl->size(), wxString((*l_it).c_str(), wxConvUTF8), 0);
			m_ExcludedFolders->SetItemImage(l_tmp, 2);
			m_ExcludedFolders->SetItemData(l_tmp, 0);
			m_ExcludedFolders->SetColumnWidth(0, wxLIST_AUTOSIZE);
		}

		l_Sizer->Add(m_ExcludedFolders, 1, wxGROW | wxALL, 5);

		l_Sizer2 = new wxBoxSizer(wxHORIZONTAL);
		l_Sizer2->Add(new wxButton(m_Folders, ID_FOLDER_ADD, _T("Add")), 0, wxALIGN_CENTER | wxALL, 2);
		l_Sizer2->Add(new wxButton(m_Folders, ID_FOLDER_DEL, _T("Remove")), 0, wxALIGN_CENTER | wxALL, 2);

		l_Sizer->Add(l_Sizer2, 0, wxGROW | wxALL, 5);
	}
	
	
	void CMainInterface::OnFolderAdd(wxCommandEvent& WXUNUSED(event))
	{
		wxString l_msg(_T("coucou"));
		wxDirDialog l_addDlg(this, wxString(i8n("Select a folder to add to scan"), wxConvUTF8), l_msg, wxDD_DIR_MUST_EXIST);
		if(l_addDlg.ShowModal() == wxID_OK)
		{
			std::string l_selPath(l_addDlg.GetPath().char_str()); 
			std::string l_Parent;
			if(!m_Engine->addFolder(l_selPath, l_Parent))
			{
				wxString l_text(i8n("I cannot add "), wxConvUTF8);
				l_text += wxString(l_selPath.c_str(), wxConvUTF8);
				l_text += wxString(i8n(" since "), wxConvUTF8);
				l_text += wxString(l_Parent.c_str(), wxConvUTF8);
				l_text += wxString(i8n(" is already in the folders list."), wxConvUTF8);
				
				wxMessageBox(l_text, wxString(i8n("scleaner information"), wxConvUTF8), wxICON_INFORMATION);
			}
		}
		UpdateFolderList();
	}
	
	
	void CMainInterface::OnFolderDel(wxCommandEvent& WXUNUSED(event))
	{
		for(int i = 0; i != m_AddedFolders->GetItemCount(); ++i)
		{
			long l_Mask;
			l_Mask = wxLIST_STATE_SELECTED;
			if(m_AddedFolders->GetItemState(i, l_Mask) == wxLIST_STATE_SELECTED)
			{
				wxListItem l_item;
				l_item.SetId(i);
				m_AddedFolders->GetItem(l_item);
				wxString l_text = l_item.GetText();
				m_Engine->delFolder(std::string(l_text.ToAscii()));
			}
		}
		UpdateFolderList();
	}
	
	
	void CMainInterface::OnPrefs(wxCommandEvent& WXUNUSED(event))
	{
		CPreferences(this, wxID_ANY, wxString(i8n("Preferences"), wxConvUTF8), wxDefaultPosition, wxDefaultSize).ShowModal();
	}
	
	
	void CMainInterface::updateProgress(const std::string& _mess, bool _pulse, int _nb)
	{
		wxString l_msg(_mess.c_str(), wxConvUTF8);
		bool l_continue;
		if(_pulse)
		{
			l_continue = m_Progress->Pulse(l_msg, 0);
		}
		else
		{
			l_continue = m_Progress->Update(_nb, l_msg, 0);
		}
	
		//if(!l_continue)
		//{
		//	if ( wxMessageBox(_T("Do you really want to cancel?"), _T("scleaner question"), wxYES_NO | wxICON_QUESTION) == wxNO)
		//	{
		//		l_continue = true;
		//		m_Progress->Resume();
		//	}
		//}
	}
	
	
	void CMainInterface::OnSelect(wxCommandEvent& WXUNUSED(event))
	{
		//GetToolBar()->SetToolShortHelp(wxID_NEW, _T("New toolbar button"));
		wxMessageDialog(this, wxString(i8n("Since for this alpha version, there are only 3 input plugins (and 2 that run only in root mode), the dialog for selecting input plugins is not yet ready :D but will be available soon !!"), wxConvUTF8), _T("scleaner"), wxOK | wxICON_EXCLAMATION).ShowModal();
	
		std::list<std::string> l_pluginList;
	
		std::map<std::string, Plugins::IInPlugin*>::iterator l_it;
		for(l_it = m_Engine->getAvailableInputPlugs()->begin(); l_it != m_Engine->getAvailableInputPlugs()->end(); ++l_it)
		{
			l_pluginList.push_back((*l_it).first);
		}
	
	    CSelectDialog l_selDlg(wxString(i8n("Select input plugins to use"), wxConvUTF8), l_pluginList);
	    l_selDlg.Show(true);
	}
	
	
	void CMainInterface::GetSelectedFiles(std::list<std::string>& _fl)
	{
		unsigned int l_pagesNb = m_Input->GetPageCount();
	
		for(unsigned int i = 0; i < l_pagesNb; ++i)
		{
			wxWindow* l_win = m_Input->GetPage(i);
			wxCheckListCtrl* l_list = (wxCheckListCtrl*) l_win;
			int l_itemsNb = l_list->GetItemCount();
	
			for(int j = 0; j < l_itemsNb; ++j)
			{
				wxListItem l_item;
				l_item.SetId(j);
				if(l_list->GetItem(l_item))
				{
					if(l_item.GetImage() == 0)
					{
						wxString l_temp = l_item.m_text;
						std::string l_file(l_temp.ToAscii());
						_fl.push_back(l_file);
					}
				}
				else
				{
					std::cerr << i8n("[ERR] CMainInterface::GetSelectedFiles GetItem !!") << '\n';
				}
			}
		}
	}
	
	
	/*void CMainInterface::OnSelRadio(wxCommandEvent& event)
	{
		wxString l_name = event.GetString();
		m_Html -> LoadPage(wxT("/usr/share/doc/scleaner/") + l_name + wxString(i8n(".html"), wxConvUTF8));
	}*/
}
