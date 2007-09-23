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
#include <wx/splash.h>
#include <wx/wxhtml.h>
#include <plugins/plugin_manager.h>
#include <plugins/iplugin.h>
#include <engine/engine.h>
#include "maininterface.h"
#include <wx/treectrl.h>
#include <wx/radiobox.h>
#include <wx/progdlg.h>
#include <wx/filedlg.h>

//GFX Elements
#include <gfx/empty.xpm>
#include <gfx/full.xpm>
#include <gfx/smile.xpm>
#include <gfx/run.xpm>
#include <gfx/stop.xpm>

IMPLEMENT_CLASS( CMainInterface, wxFrame )

BEGIN_EVENT_TABLE( CMainInterface, wxFrame )
	EVT_TREE_SEL_CHANGED(ID_TREECTRL1, CMainInterface::OnSelChanged)
    EVT_MENU(ID_ABOUT, CMainInterface::OnAbout)
    EVT_MENU(wxID_EXIT, CMainInterface::OnQuit)
    EVT_MENU(ID_PROCESS, CMainInterface::OnProcess)
    EVT_MENU(ID_STOP, CMainInterface::OnStop)
END_EVENT_TABLE()

CMainInterface::CMainInterface()
{
    Init();
}

CMainInterface::CMainInterface(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style):
m_Input(0), m_Title(0), m_Html(0), m_Output(0), m_Progress(0)
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
	m_InputPlugs = CPluginManager::Instance()->getInputListPtr();
	m_OutputPlugs = CPluginManager::Instance()->getOutputListPtr();
	if(!m_InputPlugs || !m_OutputPlugs)
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
		std::cout << "[ERR] Could not set icon.";
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
    l_MenuBar->Append(l_File, _T("File"));
	wxMenuItem* l_Quit = new wxMenuItem(l_File, wxID_EXIT, _T("Quit"));
	l_File->Append(l_Quit);
    
	//Misc menu
	l_MenuBar->Append(l_Misc, _T("Misc"));
	wxMenuItem* l_About = new wxMenuItem(l_Misc, ID_ABOUT, _T("About"));
	l_Misc->Append(l_About);

    l_Frame->SetMenuBar(l_MenuBar);
	//________________________________________________________________
	//TOOLBAR
    //l_ToolBar->SetMargins(4, 4);

	//l_Frame->SetToolBar(l_ToolBar);
    wxToolBar* l_ToolBar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR1 );
    l_ToolBar->AddTool(ID_PROCESS, _T("Apply output plugin on selected files"),run_xpm , run_xpm, wxITEM_NORMAL, _T("Apply output plugin on selected files"), wxEmptyString);
    l_ToolBar->AddTool(ID_STOP, _T("Stop"), stop_xpm, stop_xpm, wxITEM_NORMAL, _T("Stop"), wxEmptyString);
    l_ToolBar->AddSeparator();
    l_ToolBar->AddTool(ID_TOOL3, _T(""), smile_xpm, smile_xpm, wxITEM_NORMAL, _T(""), wxEmptyString);
    l_ToolBar->AddTool(ID_TOOL4, _T(""), smile_xpm, smile_xpm, wxITEM_NORMAL, _T(""), wxEmptyString);
    l_ToolBar->Realize();
    l_Frame->SetToolBar(l_ToolBar);
	//________________________________________________________________

    wxSplitterWindow* itemSplitterWindow10 = new wxSplitterWindow( l_Frame, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow10->SetMinimumPaneSize(0);

	//Input plugins
    m_Input = new wxCheckTreeCtrl( itemSplitterWindow10, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT);

	// Happend plugins' name available
	wxTreeItemId l_root = m_Input->AddRoot(wxT("Input plugins"), wxTreeItemIcon_Expanded, wxTreeItemIcon_Expanded);
    std::map<std::string, IInPlugin*>::iterator _it;
    for(_it = m_InputPlugs->begin(); _it != m_InputPlugs->end(); ++_it)
    {
		wxString l_str(((*_it).second)->getName().c_str(), wxConvUTF8);
    	wxTreeItemId l_plug = m_Input->AddCheckedItem(l_root, l_str, false);

		std::list<std::string> l_list;
		((*_it).second)->getFileList(l_list);
		std::list<std::string>::iterator _it2;

#if defined DEBUG
		std::cout << "[DBG] Size = " << l_list.size() << '\n';
#endif

		for(_it2 = l_list.begin(); _it2 != l_list.end(); ++_it2)
		{
			wxString l_str2((*_it2).c_str(), wxConvUTF8);
			wxTreeItemId l_file = m_Input->AddCheckedItem(l_plug, l_str2, true);

			//This plugin need root access ?
			if(((*_it).second)->needRoot())
			{
				//If yes, did it have it ?
				if(!m_Engine->isRoot())
				{
					//If not disable founded files.
					m_Input->EnableItem(l_file, false);
					m_Input->CheckItem(l_file, false);
				}
			}
		}
    }
	//

    wxSplitterWindow* itemSplitterWindow12 = new wxSplitterWindow( itemSplitterWindow10, ID_SPLITTERWINDOW2, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow12->SetMinimumPaneSize(0);

	//Output plugins
    wxArrayString l_out;
    std::map<std::string, IOutPlugin*>::iterator _it2;
    for(_it2 = m_OutputPlugs->begin(); _it2 != m_OutputPlugs->end(); ++_it2)
    {
		wxString l_name( ((*_it2).second)->getName().c_str(), wxConvUTF8);
    	l_out.Add(l_name);
	}

    //m_Output = new wxCheckListBox( itemSplitterWindow12, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, l_out, wxLB_SINGLE);
	wxString l_title(_T("Output plugins"));
    m_Output = new wxRadioBox(itemSplitterWindow12, ID_RADIOBOX, l_title, wxDefaultPosition, wxDefaultSize, l_out, 1, wxRA_SPECIFY_COLS);
	m_Output->SetSelection(0);


    m_Html = new wxHtmlWindow(itemSplitterWindow12, wxID_ANY, wxDefaultPosition, wxSize(380, 160), wxHW_SCROLLBAR_NEVER);
    m_Html -> SetBorders(0);
    m_Html -> LoadPage(wxT("/usr/share/doc/scleaner/about.html"));
    m_Html -> SetSize(m_Html -> GetInternalRepresentation() -> GetWidth(), m_Html -> GetInternalRepresentation() -> GetHeight());

    /*wxPanel* itemPanel14 = new wxPanel( itemSplitterWindow12, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxVERTICAL);
    itemPanel14->SetSizer(itemBoxSizer15);

    m_Title = new wxStaticText( itemPanel14, ID_TITLE, _(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(m_Title, 0, wxALIGN_LEFT|wxALL, 5);

    m_Line1 = new wxStaticText( itemPanel14, wxID_STATIC, _(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(m_Line1, 0, wxALIGN_CENTER|wxALL, 5);

    m_Line2 = new wxStaticText( itemPanel14, wxID_STATIC, _(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(m_Line2, 0, wxALIGN_CENTER|wxALL, 5);

    m_Line3 = new wxStaticText( itemPanel14, wxID_STATIC, _(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(m_Line3, 0, wxALIGN_CENTER|wxALL, 5);

    itemBoxSizer15->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);*/

    /*wxStdDialogButtonSizer* itemStdDialogButtonSizer21 = new wxStdDialogButtonSizer;

    itemBoxSizer15->Add(itemStdDialogButtonSizer21, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton22 = new wxButton( itemPanel14, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer21->AddButton(itemButton22);

    wxButton* itemButton23 = new wxButton( itemPanel14, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer21->AddButton(itemButton23);

    itemStdDialogButtonSizer21->Realize();*/

    //itemSplitterWindow12->SplitHorizontally(m_Output, itemPanel14, 50);
    itemSplitterWindow12->SplitHorizontally(m_Output, m_Html, 50);
    itemSplitterWindow10->SplitVertically(m_Input, itemSplitterWindow12, 200);

    m_StatusBar = new wxStatusBar( l_Frame, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
    m_StatusBar->SetFieldsCount(3);
    l_Frame->SetStatusBar(m_StatusBar);

	if(m_Engine->isRoot())
	{
	 	SetStatusText(_T("Launched as root/sudo"), 2);
	}
	else
	{
	 	SetStatusText(_T("Launched as standard user"), 2);
	}

	std::string l_version = "Kernel : v";
	m_Engine->getKernelVersion(l_version);
	wxString l_uversion(l_version.c_str(), wxConvUTF8);
	SetStatusText(l_uversion, 1);

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
//Treeview
void CMainInterface::OnSelChanged(wxTreeEvent& event)
{
    wxTreeItemId l_item = m_Input->GetSelection();
	
	if(l_item == m_Input->GetRootItem())
	{
    	m_Html -> LoadPage(wxT("/usr/share/doc/scleaner/about.html"));
	}
	else
	{
    	m_Html -> LoadPage(wxT("/usr/share/doc/scleaner/kernels.html"));
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
void CMainInterface::OnProcess(wxCommandEvent& WXUNUSED(event))
{
    //GetToolBar()->SetToolShortHelp(wxID_NEW, _T("New toolbar button"));
#if defined DEBUG
	std::cout << "[DBG] Process !!! " << '\n';
#endif
	std::list<std::string> l_selected_files;
	GetSelectedFilesRecursively(m_Input->GetRootItem(), l_selected_files);

#if defined DEBUG
	std::cout << "[DBG] You have selected: " << '\n';
    std::list<std::string>::iterator l_it;
    for(l_it = l_selected_files.begin(); l_it != l_selected_files.end(); ++l_it)
	{
		std::cout << "[DBG] " << *l_it << '\n';
	}
#endif

    m_Progress = new wxProgressDialog(_T("scleaner process your files ..."),
                            _T("this is a information"),
                            100,    // range
                            this,   // parent
                            wxPD_CAN_ABORT |
                            // wxPD_CAN_SKIP |
                            wxPD_APP_MODAL |
                            // wxPD_AUTO_HIDE | -- try this as well
                            wxPD_ELAPSED_TIME |
                            wxPD_ESTIMATED_TIME |
                            wxPD_REMAINING_TIME
                            | wxPD_SMOOTH // - makes indeterminate mode bar on WinXP very small
                            );

	std::string l_name;
	wxString l_nameWX;
	l_nameWX = m_Output->GetStringSelection();
	l_name = l_nameWX.char_str();

#if defined DEBUG
	std::cout << "[DBG] CMainInterface : Get selection : " << l_name << '\n';
#endif

    wxFileDialog l_outputFileDlg(this, _T("Select an output folder"));
    if (l_outputFileDlg.ShowModal() != wxID_OK)
	{
        return;
	}

//    wxFFile file(filedlg.GetFilename(), _T("r"));

	m_Engine->callOutputPlugin(l_selected_files, l_name, this);

	delete m_Progress;
	m_Progress = 0;
}

void CMainInterface::updateProgress(const std::string& _mess, int _nb)
{
		wxString l_msg(_mess.c_str(), wxConvUTF8);
		bool l_continue = m_Progress->Update(_nb, l_msg, 0);
		if(!l_continue)
		{
            if ( wxMessageBox(_T("Do you really want to cancel?"), _T("scleaner question"), wxYES_NO | wxICON_QUESTION) == wxNO)
			{
				l_continue = true;
				m_Progress->Resume();
			}
		}
}

void CMainInterface::OnStop(wxCommandEvent& WXUNUSED(event))
{
    //GetToolBar()->SetToolShortHelp(wxID_NEW, _T("New toolbar button"));
}

void CMainInterface::GetSelectedFilesRecursively(const wxTreeItemId& _idParent, std::list<std::string>& _fl, wxTreeItemIdValue _cookie)
{
    wxTreeItemId l_id;

    if (!_cookie)
	{
        l_id = m_Input->GetFirstChild(_idParent, _cookie);
	}
    else
	{
        l_id = m_Input->GetNextChild(_idParent, _cookie);
	}

    if (!l_id.IsOk())
	{
        return;
	}

    wxString l_text = m_Input->GetItemText(l_id);
	std::string l_temp(l_text.ToAscii());
	wxCheckTreeItemData* l_data = m_Input->GetData(l_id);
	if(/*l_data->GetEnabled() &&*/ l_data->GetChecked())
	{
		_fl.push_back(l_temp);
	}

    if (m_Input->ItemHasChildren(l_id))
	{
        GetSelectedFilesRecursively(l_id, _fl);
	}

    GetSelectedFilesRecursively(_idParent, _fl, _cookie);
}
