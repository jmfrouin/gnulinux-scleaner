/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <config.h>
#include <string>
#include <plugins/plugin_manager.h>
#include <plugins/iplugin.h>
#include "maininterface.h"

//GFX Elements
#include <gfx/empty.xpm>
#include <gfx/full.xpm>
#include <gfx/smile.xpm>

IMPLEMENT_CLASS( CMainInterface, wxFrame )

BEGIN_EVENT_TABLE( CMainInterface, wxFrame )
EVT_TREE_SEL_CHANGED(ID_TREECTRL1, CMainInterface::OnSelChanged)
END_EVENT_TABLE()

CMainInterface::CMainInterface()
{
    Init();
}

CMainInterface::CMainInterface(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style):
m_Input(0), m_Title(0), m_Output(0)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool CMainInterface::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();

    if (FindWindow(ID_SPLITTERWINDOW1))
        ((wxSplitterWindow*) FindWindow(ID_SPLITTERWINDOW1))->SetSashPosition(200);
    if (FindWindow(ID_SPLITTERWINDOW2))
        ((wxSplitterWindow*) FindWindow(ID_SPLITTERWINDOW2))->SetSashPosition(200);

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
		std::cout << "Could not set icon.";
	}
}

void CMainInterface::CreateControls()
{    
    CMainInterface* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* itemMenu3 = new wxMenu;
    menuBar->Append(itemMenu3, _("Menu"));
    itemFrame1->SetMenuBar(menuBar);

    wxToolBar* itemToolBar4 = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR1 );
    wxBitmap itemtool5Bitmap(wxNullBitmap);
    wxBitmap itemtool5BitmapDisabled;
    itemToolBar4->AddTool(ID_TOOL1, _T(""), itemtool5Bitmap, itemtool5BitmapDisabled, wxITEM_NORMAL, _T(""), wxEmptyString);
    wxBitmap itemtool6Bitmap(wxNullBitmap);
    wxBitmap itemtool6BitmapDisabled;
    itemToolBar4->AddTool(ID_TOOL2, _T(""), itemtool6Bitmap, itemtool6BitmapDisabled, wxITEM_NORMAL, _T(""), wxEmptyString);
    itemToolBar4->AddSeparator();
    wxBitmap itemtool8Bitmap(wxNullBitmap);
    wxBitmap itemtool8BitmapDisabled;
    itemToolBar4->AddTool(ID_TOOL3, _T(""), itemtool8Bitmap, itemtool8BitmapDisabled, wxITEM_NORMAL, _T(""), wxEmptyString);
    wxBitmap itemtool9Bitmap(wxNullBitmap);
    wxBitmap itemtool9BitmapDisabled;
    itemToolBar4->AddTool(ID_TOOL4, _T(""), itemtool9Bitmap, itemtool9BitmapDisabled, wxITEM_NORMAL, _T(""), wxEmptyString);
    itemToolBar4->Realize();
    itemFrame1->SetToolBar(itemToolBar4);

    wxSplitterWindow* itemSplitterWindow10 = new wxSplitterWindow( itemFrame1, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow10->SetMinimumPaneSize(0);

	//Input plugins
    //wxTreeCtrl* itemTreeCtrl11 = new wxTreeCtrl( itemSplitterWindow10, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );
    m_Input = new wxCheckTreeCtrl( itemSplitterWindow10, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT);

	// Happend plugins' name available
	wxTreeItemId l_root = m_Input->AddRoot(wxT("Input plugins"), wxTreeItemIcon_Expanded, wxTreeItemIcon_Expanded);
    std::map<std::string, IInPlugin*>::iterator _it;
    for(_it = m_InputPlugs->begin(); _it != m_InputPlugs->end(); ++_it)
    {
		std::cout << ":" << ((*_it).second)->getName() << '\n';
    	//itemTreeCtrl11->AppendItem(l_root, _(((*_it).second)->getName().c_str()), 2, 2 );
    	wxTreeItemId l_plug = m_Input->AddCheckedItem(l_root, _(((*_it).second)->getName().c_str()), false );

		std::list<std::string> l_list;
		((*_it).second)->getFileList(l_list);
		std::list<std::string>::iterator _it2;
		std::cout << "Taille : " << l_list.size() << '\n';

		for(_it2 = l_list.begin(); _it2 != l_list.end(); ++_it2)
		{
			m_Input->AddCheckedItem(l_plug, _((*_it2).c_str()), true );
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
    	l_out.Add(((*_it2).second)->getName());
	}
    m_Output = new wxCheckListBox( itemSplitterWindow12, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, l_out, wxLB_SINGLE );
    //m_Output->InsertItems(l_out, m_Output->GetCount());
	//

    wxPanel* itemPanel14 = new wxPanel( itemSplitterWindow12, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
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

    itemBoxSizer15->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer21 = new wxStdDialogButtonSizer;

    itemBoxSizer15->Add(itemStdDialogButtonSizer21, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton22 = new wxButton( itemPanel14, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer21->AddButton(itemButton22);

    wxButton* itemButton23 = new wxButton( itemPanel14, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer21->AddButton(itemButton23);

    itemStdDialogButtonSizer21->Realize();

    itemSplitterWindow12->SplitHorizontally(m_Output, itemPanel14, 50);
    itemSplitterWindow10->SplitVertically(m_Input, itemSplitterWindow12, 200);

    wxStatusBar* itemStatusBar24 = new wxStatusBar( itemFrame1, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar24->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar24);
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
void CMainInterface::OnSelChanged(wxTreeEvent& event)
{
    wxTreeItemId l_item = m_Input->GetSelection();
	
	if(l_item.IsOk())
	{
		wxString l_text = m_Input->GetItemText(l_item);
		if(l_item != m_Input->GetRootItem())
		{

			if(l_text.Contains(_("/")))
			{
				l_text += " informations :";
				m_Title->SetLabel(l_text);
			}
			else
			{
				std::map<std::string, IInPlugin*>::iterator l_it;
				l_it = m_InputPlugs->find(l_text.c_str());
				wxString l_description = (l_it->second)->description();
				wxString l_author = (l_it->second)->author();
				wxString l_version = (l_it->second)->version();
				l_text += " plugin informations :";
				m_Title->SetLabel(l_text);
				m_Line1->SetLabel(l_description);
				m_Line2->SetLabel(l_author);
				m_Line3->SetLabel(l_version);
			}
		}
	}
}
