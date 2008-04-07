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

    wxListCtrl* itemListCtrl8 = new wxListCtrl( itemAuiNotebook7, ID_LISTCTRL2, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );

    itemAuiNotebook7->AddPage(itemListCtrl8, _("Tab"), false);

<<<<<<< HEAD:maininterface.cpp
    wxSplitterWindow* itemSplitterWindow9 = new wxSplitterWindow( itemAuiNotebook7, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow9->SetMinimumPaneSize(0);
=======
    wxTreeCtrl* itemTreeCtrl9 = new wxTreeCtrl( itemAuiNotebook7, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );
>>>>>>> 57118111bd7d37336525ad1269306620213d5d83:maininterface.cpp

<<<<<<< HEAD:maininterface.cpp
    wxTreeCtrl* itemTreeCtrl10 = new wxTreeCtrl( itemSplitterWindow9, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );
=======
    itemAuiNotebook7->AddPage(itemTreeCtrl9, _("Tab"), false);
>>>>>>> 57118111bd7d37336525ad1269306620213d5d83:maininterface.cpp

<<<<<<< HEAD:maininterface.cpp
    wxPanel* itemPanel11 = new wxPanel( itemSplitterWindow9, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemPanel11->SetSizer(itemBoxSizer12);
=======
    wxListCtrl* itemListCtrl10 = new wxListCtrl( itemAuiNotebook7, ID_LISTCTRL2, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
>>>>>>> 57118111bd7d37336525ad1269306620213d5d83:maininterface.cpp

<<<<<<< HEAD:maininterface.cpp
    wxButton* itemButton13 = new wxButton( itemPanel11, ID_BUTTON1, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
=======
    itemAuiNotebook7->AddPage(itemListCtrl10, _("Tab"), false);
>>>>>>> 57118111bd7d37336525ad1269306620213d5d83:maininterface.cpp

<<<<<<< HEAD:maininterface.cpp
    wxButton* itemButton14 = new wxButton( itemPanel11, ID_BUTTON2, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton15 = new wxButton( itemPanel11, ID_BUTTON3, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton15, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton16 = new wxButton( itemPanel11, ID_BUTTON4, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton17 = new wxButton( itemPanel11, ID_BUTTON5, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton17, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton18 = new wxButton( itemPanel11, ID_BUTTON6, _("Button"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton18, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemSplitterWindow9->SplitVertically(itemTreeCtrl10, itemPanel11, 50);
    itemAuiNotebook7->AddPage(itemSplitterWindow9, _("Tab"), false);

    wxStatusBar* itemStatusBar19 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar19->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar19);
=======
    wxStatusBar* itemStatusBar11 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar11->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar11);
>>>>>>> 57118111bd7d37336525ad1269306620213d5d83:maininterface.cpp

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
