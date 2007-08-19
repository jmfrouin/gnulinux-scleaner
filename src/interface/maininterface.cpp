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

#include "maininterface.h"

IMPLEMENT_CLASS( MainInterface, wxFrame )

BEGIN_EVENT_TABLE( MainInterface, wxFrame )
END_EVENT_TABLE()

MainInterface::MainInterface()
{
    Init();
}

MainInterface::MainInterface( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}

bool MainInterface::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
    return true;
}

MainInterface::~MainInterface()
{
}

void MainInterface::Init()
{
}

void MainInterface::CreateControls()
{    
////@begin MainInterface content construction
    MainInterface* itemFrame1 = this;

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

    //wxTreeCtrl* itemTreeCtrl11 = new wxTreeCtrl( itemSplitterWindow10, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );
    wxCheckTreeCtrl* itemTreeCtrl11 = new wxCheckTreeCtrl( itemSplitterWindow10, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );
	wxString l_text;
	l_text = _("dpkg");
    itemTreeCtrl11->AppendItem(itemTreeCtrl11->GetRootItem(),
                           l_text /*,
                           MyTreeCtrl::TreeCtrlIcon_File */ );

    wxArrayString itemCheckListBox12Strings;
    itemCheckListBox12Strings.Add(_("dzdz"));
    itemCheckListBox12Strings.Add(_("dz"));
    itemCheckListBox12Strings.Add(_("dzdz"));
    itemCheckListBox12Strings.Add(_("d"));
    itemCheckListBox12Strings.Add(_("zd"));
    itemCheckListBox12Strings.Add(_("dz"));
    wxCheckListBox* itemCheckListBox12 = new wxCheckListBox( itemSplitterWindow10, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, itemCheckListBox12Strings, wxLB_SINGLE );

    itemSplitterWindow10->SplitVertically(itemTreeCtrl11, itemCheckListBox12, 50);

    wxStatusBar* itemStatusBar13 = new wxStatusBar( itemFrame1, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar13->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar13);
}

bool MainInterface::ShowToolTips()
{
    return true;
}

wxBitmap MainInterface::GetBitmapResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon MainInterface::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullIcon;
}
