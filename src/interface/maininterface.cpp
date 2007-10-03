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
#include <tools/crc.h>
#include <wx/radiobox.h>
#include <wx/progdlg.h>
#include <wx/dirdlg.h>
#include <wx/splash.h>
#include <wx/wxhtml.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include "maininterface.h"
#include "checklistctrl.h"
#include "select_dialog.h"

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

#include <gfx/checked.xpm>
#include <gfx/unchecked.xpm>

IMPLEMENT_CLASS( CMainInterface, wxFrame )

BEGIN_EVENT_TABLE( CMainInterface, wxFrame )
EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, CMainInterface::OnNotebook)
EVT_RADIOBOX(ID_RADIOBOX, CMainInterface::OnSelRadio)
EVT_MENU(ID_SCAN, CMainInterface::OnScan)
EVT_MENU(ID_ABOUT, CMainInterface::OnAbout)
EVT_MENU(wxID_EXIT, CMainInterface::OnQuit)
EVT_MENU(ID_PROCESS, CMainInterface::OnProcess)
EVT_MENU(ID_SELECT, CMainInterface::OnSelect)
END_EVENT_TABLE()

CMainInterface::CMainInterface()
{
	Init();
}


CMainInterface::CMainInterface(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style):
m_AvailableInputPlugs(0), m_SelectedInputPlugs(0), m_OutputPlugs(0), m_Input(0), m_Html(0), m_Output(0), m_StatusBar(0), m_Split(0), m_Split2(0), m_Split3(0), m_Progress(0)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}


bool CMainInterface::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	wxFrame::Create( parent, id, caption, pos, size, style );

	CreateControls();
	Centre();

	//Retrieve CEngine instance pointer.
	m_Engine = CEngine::Instance();

	if (FindWindow(ID_SPLITTERWINDOW1))
	{
		((wxSplitterWindow*) FindWindow(ID_SPLITTERWINDOW1))->SetSashPosition(SYMBOL_MAININTERFACE_SASH1_POS);
	}
	if (FindWindow(ID_SPLITTERWINDOW2))
	{
		((wxSplitterWindow*) FindWindow(ID_SPLITTERWINDOW2))->SetSashPosition(SYMBOL_MAININTERFACE_SASH2_POS);
	}
	if (FindWindow(ID_SPLITTERWINDOW3))
	{
		((wxSplitterWindow*) FindWindow(ID_SPLITTERWINDOW3))->SetSashPosition(SYMBOL_MAININTERFACE_SASH3_POS);
	}

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
	//Initialisation
	m_AvailableInputPlugs = CPluginManager::Instance()->getInputListPtr();
	m_OutputPlugs = CPluginManager::Instance()->getOutputListPtr();
	if(!m_AvailableInputPlugs || !m_OutputPlugs)
	{
		return;
	}

	//Tray icon !!
	m_Icon = new CTrayIcon();
	#if defined(__WXCOCOA__)
	m_DockIcon = new CTrayIcon(wxTaskBarIcon::DOCK);
	#endif

	m_Icon->setParent(this);

	if (!m_Icon->SetIcon(full_xpm, wxT(NAME)))
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

	//________________________________________________________________
	//MENU
	wxMenuBar* l_MenuBar = new wxMenuBar;
	wxMenu* l_File = new wxMenu;
	wxMenu* l_Misc = new wxMenu;

	//File menu
	l_MenuBar->Append(l_File, wxString(i8n("File"), wxConvUTF8));
	wxMenuItem* l_Quit = new wxMenuItem(l_File, wxID_EXIT, wxString(i8n("Quit"), wxConvUTF8));
	l_File->Append(l_Quit);

	//Misc menu
	l_MenuBar->Append(l_Misc, wxString(i8n("Misc"), wxConvUTF8));
	wxMenuItem* l_About = new wxMenuItem(l_Misc, ID_ABOUT, wxString(i8n("About"), wxConvUTF8));
	l_Misc->Append(l_About);

	l_Frame->SetMenuBar(l_MenuBar);
	//________________________________________________________________
	//TOOLBAR
	//l_ToolBar->SetMargins(4, 4);

	//l_Frame->SetToolBar(l_ToolBar);
	wxToolBar* l_ToolBar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR1 );
	l_ToolBar->AddTool(ID_SELECT, wxString(i8n("Select input plugins to use."), wxConvUTF8), select_xpm, select_xpm, wxITEM_NORMAL, wxString(i8n("Select input plugins to use."), wxConvUTF8), wxEmptyString);
	l_ToolBar->AddTool(ID_SCAN, wxString(i8n("Use input plugins to find files."), wxConvUTF8), scan_xpm, scan_xpm, wxITEM_NORMAL, wxString(i8n("Use input plugins to find files."), wxConvUTF8), wxEmptyString);
	l_ToolBar->AddTool(ID_PROCESS, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8),run_xpm , run_xpm, wxITEM_NORMAL, wxString(i8n("Apply output plugin on selected files."), wxConvUTF8), wxEmptyString);
	l_ToolBar->AddSeparator();
	//l_ToolBar->AddTool(ID_CONFIG, wxString(i8n("Configuration"), wxConvUTF8), config_xpm , config_xpm, wxITEM_NORMAL, wxString(i8n("Configuration"), wxConvUTF8), wxEmptyString);
	//l_ToolBar->AddSeparator();
	l_ToolBar->AddTool(wxID_EXIT, wxString(i8n("Quit"), wxConvUTF8),exit_xpm , exit_xpm, wxITEM_NORMAL, wxString(i8n("Quit"), wxConvUTF8), wxEmptyString);
	l_ToolBar->Realize();
	l_Frame->SetToolBar(l_ToolBar);
	//________________________________________________________________

	m_Split = new wxSplitterWindow( l_Frame, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
	m_Split->SetMinimumPaneSize(0);

	m_Split2 = new wxSplitterWindow(m_Split, ID_SPLITTERWINDOW2, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
	m_Split2->SetMinimumPaneSize(0);

	//Input plugins
	int l_flags = wxBK_TOP | wxNB_MULTILINE | wxDOUBLE_BORDER;
	m_Input = new wxNotebook(m_Split2, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, l_flags);
	
	wxArrayString itemCheckListBox12Strings;
    itemCheckListBox12Strings.Add(_("Users can select "));
    itemCheckListBox12Strings.Add(_("Folder"));
    itemCheckListBox12Strings.Add(_("Soon"));

    wxCheckListBox* itemCheckListBox12 = new wxCheckListBox( m_Split2,wxID_ANY, wxDefaultPosition, wxDefaultSize, itemCheckListBox12Strings, wxLB_SINGLE );

	//Add the "File selected view" and the "Folders selected view" to a split.
	m_Split2->SplitHorizontally(itemCheckListBox12, m_Input, 200);

	m_Split3 = new wxSplitterWindow(m_Split, ID_SPLITTERWINDOW3, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
	m_Split3->SetMinimumPaneSize(0);

	//Output plugins
	wxArrayString l_out;
	std::map<std::string, IOutPlugin*>::iterator _it2;
	for(_it2 = m_OutputPlugs->begin(); _it2 != m_OutputPlugs->end(); ++_it2)
	{
		wxString l_name( ((*_it2).second)->getName().c_str(), wxConvUTF8);
		l_out.Add(l_name);
	}

	wxString l_title(wxString(i8n("Output plugins"), wxConvUTF8));
	m_Output = new wxRadioBox(m_Split3, ID_RADIOBOX, l_title, wxDefaultPosition, wxDefaultSize, l_out, 1, wxRA_SPECIFY_COLS);
	m_Output->SetSelection(0);

	m_Html = new wxHtmlWindow(m_Split3, wxID_ANY, wxDefaultPosition, wxSize(380, 160), wxHW_SCROLLBAR_NEVER);
	m_Html->SetBorders(0);
	m_Html->LoadPage(wxString(i8n("/usr/share/doc/scleaner/about.html"), wxConvUTF8));
	m_Html->SetSize(m_Html->GetInternalRepresentation()->GetWidth(), m_Html->GetInternalRepresentation()->GetHeight());

	//Add the "Output plugin view and the "HTML Help view" to another split.
	m_Split3->SplitHorizontally(m_Output, m_Html, 50);

	//Finally split these splits :D (Now you entered the dark side of the split ...)
	m_Split->SplitVertically(m_Split2, m_Split3, 200);

	m_StatusBar = new wxStatusBar( l_Frame, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
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
	if(m_Html != 0 && !l_name.empty())
	{
		m_Html->LoadPage(wxT("/usr/share/doc/scleaner/") + l_name + wxString(i8n(".html"), wxConvUTF8));
	}
	std::stringstream l_tot;
	if(m_TotalSizes.size() > 0)
	{
		std::string l_total(i8n("Total size : "));
		CEngine::Instance()->formatSize(m_TotalSizes[l_sel], l_total);
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
	std::map<std::string, IInPlugin*>::iterator _it;
	for(_it = m_AvailableInputPlugs->begin(); _it != m_AvailableInputPlugs->end(); ++_it)
	{
		wxString l_str(((*_it).second)->getName().c_str(), wxConvUTF8);

		std::list<std::string> l_list;
		((*_it).second)->getFileList(l_list);
		l_list.sort();
		std::list<std::string>::iterator _it2;

		#if defined DEBUG
		std::cout << i8n("[DBG] Size = ") << l_list.size() << '\n';
		#endif
		//FIXME : Manual delete need
		wxImageList* l_imageListSmall = new wxImageList(16, 16, true);
		l_imageListSmall->Add(wxIcon(checked_xpm));
		l_imageListSmall->Add(wxIcon(unchecked_xpm));

		wxCheckListCtrl* l_fileslist = new wxCheckListCtrl(m_Input, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxSUNKEN_BORDER | wxLC_VRULES | wxLC_HRULES);

		l_fileslist->SetImageList(l_imageListSmall, wxIMAGE_LIST_SMALL);

		//Setting header:
		wxListItem l_itemCol;
		l_itemCol.SetText(wxString(i8n("File location"), wxConvUTF8));
		l_itemCol.SetImage(-1);
		l_fileslist->InsertColumn(0, l_itemCol);

		l_itemCol.SetText(wxString(i8n("Size (bytes)"), wxConvUTF8));
		l_itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
		l_fileslist->InsertColumn(1, l_itemCol);

		l_itemCol.SetText(wxString(i8n("TODO"), wxConvUTF8));
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

				//if(l_info.st_size != 0)
				//{
				//	std::ifstream l_file(l_filename.c_str());
				//	char l_buf[4096];
				//	l_file.get(l_buf, 4096);
				//	unsigned int l_read = l_file.gcount();

				//	unsigned short l_crc  = 0;
    			//	CCRC::calc_UDF_CRC((unsigned int*)l_buf, l_read, l_crc);
				//	l_file.close();
				//	
				//	std::stringstream l_crc2;
				//	l_crc2 << l_crc;
				//	l_fileslist->SetItem(l_tmp, 2, wxString(std::string(l_crc2.str()).c_str(), wxConvUTF8));
				//}
				//else
				//{
				//	l_fileslist->SetItem(l_tmp, 2, wxString(_T("No CRC on null size")));
				//}
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
	l_nameWX = m_Output->GetStringSelection();
	l_name = l_nameWX.char_str();

	#if defined DEBUG
	std::cout << i8n("[DBG] CMainInterface : Get selection : ") << l_name << '\n';
	#endif

	wxString l_msg;
	if(CEngine::isRoot())
	{
		l_msg = _T("/root/");
	}
	else
	{
		std::string l_path("/home");
		std::string l_username;
		CEngine::getUsername(l_username);
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

	std::map<std::string, IInPlugin*>::iterator l_it;
	for(l_it = m_AvailableInputPlugs->begin(); l_it != m_AvailableInputPlugs->end(); ++l_it)
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


void CMainInterface::OnSelRadio(wxCommandEvent& event)
{
	wxString l_name = event.GetString();
	m_Html -> LoadPage(wxT("/usr/share/doc/scleaner/") + l_name + wxString(i8n(".html"), wxConvUTF8));
}
