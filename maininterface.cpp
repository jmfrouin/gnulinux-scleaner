/////////////////////////////////////////////////////////////////////////////
// Name:        maininterface.cpp
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Sun 28 Oct 2007 01:59:28 CEST
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

#include "src/interface/maininterface.h"

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

    wxToolBar* itemToolBar4 = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER, ID_TOOLBAR1 );
    wxBitmap itemtool5Bitmap(wxNullBitmap);
    wxBitmap itemtool5BitmapDisabled;
    itemToolBar4->AddTool(ID_TOOL1, _T(""), itemtool5Bitmap, itemtool5BitmapDisabled, wxITEM_NORMAL, _T(""), wxEmptyString);
    wxBitmap itemtool6Bitmap(wxNullBitmap);
    wxBitmap itemtool6BitmapDisabled;
    itemToolBar4->AddTool(ID_TOOL2, _T(""), itemtool6Bitmap, itemtool6BitmapDisabled, wxITEM_NORMAL, _T(""), wxEmptyString);
    itemToolBar4->Realize();
    itemFrame1->SetToolBar(itemToolBar4);

    wxAuiNotebook* itemAuiNotebook7 = new wxAuiNotebook( itemFrame1, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE );

    wxListCtrl* itemListCtrl8 = new wxListCtrl( itemAuiNotebook7, ID_LISTCTRL1, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );

    itemAuiNotebook7->AddPage(itemListCtrl8, _("Tab"), false);

    wxListCtrl* itemListCtrl9 = new wxListCtrl( itemAuiNotebook7, ID_LISTCTRL2, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );

    itemAuiNotebook7->AddPage(itemListCtrl9, _("Tab"), false);

    wxStatusBar* itemStatusBar10 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar10->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar10);

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
