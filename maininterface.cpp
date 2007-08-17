/////////////////////////////////////////////////////////////////////////////
// Name:        maininterface.cpp
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Fri 17 Aug 2007 23:52:34 CEST
// RCS-ID:      
// Copyright:   Project are under GNU GPL v3
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "maininterface.h"

////@begin XPM images
////@end XPM images


/*!
 * MainInterface type definition
 */

IMPLEMENT_CLASS( MainInterface, wxFrame )


/*!
 * MainInterface event table definition
 */

BEGIN_EVENT_TABLE( MainInterface, wxFrame )

////@begin MainInterface event table entries
////@end MainInterface event table entries

END_EVENT_TABLE()


/*!
 * MainInterface constructors
 */

MainInterface::MainInterface()
{
    Init();
}

MainInterface::MainInterface( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*!
 * MainInterface creator
 */

bool MainInterface::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MainInterface creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end MainInterface creation
    return true;
}


/*!
 * MainInterface destructor
 */

MainInterface::~MainInterface()
{
////@begin MainInterface destruction
////@end MainInterface destruction
}


/*!
 * Member initialisation
 */

void MainInterface::Init()
{
////@begin MainInterface member initialisation
////@end MainInterface member initialisation
}


/*!
 * Control creation for MainInterface
 */

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

    wxTreeCtrl* itemTreeCtrl11 = new wxTreeCtrl( itemSplitterWindow10, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );

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

////@end MainInterface content construction
}


/*!
 * Should we show tooltips?
 */

bool MainInterface::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap MainInterface::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MainInterface bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end MainInterface bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon MainInterface::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MainInterface icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end MainInterface icon retrieval
}
