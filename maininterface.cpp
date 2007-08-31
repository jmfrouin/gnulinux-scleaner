/////////////////////////////////////////////////////////////////////////////
// Name:        maininterface.cpp
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Sat 25 Aug 2007 21:48:47 CEST
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

    if (FindWindow(ID_SPLITTERWINDOW1))
        ((wxSplitterWindow*) FindWindow(ID_SPLITTERWINDOW1))->SetSashPosition(200);
    if (FindWindow(ID_SPLITTERWINDOW2))
        ((wxSplitterWindow*) FindWindow(ID_SPLITTERWINDOW2))->SetSashPosition(50);
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

    wxStatusBar* itemStatusBar10 = new wxStatusBar( itemFrame1, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar10->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar10);

    wxPanel* itemPanel11 = new wxPanel( itemFrame1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

    wxNotebook* itemNotebook12 = new wxNotebook( itemFrame1, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxSplitterWindow* itemSplitterWindow13 = new wxSplitterWindow( itemNotebook12, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow13->SetMinimumPaneSize(0);

    wxTreeCtrl* itemTreeCtrl14 = new wxTreeCtrl( itemSplitterWindow13, ID_TREECTRL1, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );

    wxSplitterWindow* itemSplitterWindow15 = new wxSplitterWindow( itemSplitterWindow13, ID_SPLITTERWINDOW2, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
    itemSplitterWindow15->SetMinimumPaneSize(0);

    wxArrayString itemCheckListBox16Strings;
    wxCheckListBox* itemCheckListBox16 = new wxCheckListBox( itemSplitterWindow15, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, itemCheckListBox16Strings, wxLB_SINGLE );

    wxPanel* itemPanel17 = new wxPanel( itemSplitterWindow15, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer18 = new wxBoxSizer(wxVERTICAL);
    itemPanel17->SetSizer(itemBoxSizer18);

    wxStaticText* itemStaticText19 = new wxStaticText( itemPanel17, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemStaticText19, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( itemPanel17, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemStaticText20, 0, wxALIGN_RIGHT|wxALL, 5);

    wxStaticText* itemStaticText21 = new wxStaticText( itemPanel17, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemStaticText21, 0, wxALIGN_RIGHT|wxALL, 5);

    wxStaticText* itemStaticText22 = new wxStaticText( itemPanel17, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemStaticText22, 0, wxALIGN_RIGHT|wxALL, 5);

    itemBoxSizer18->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer24 = new wxStdDialogButtonSizer;

    itemBoxSizer18->Add(itemStdDialogButtonSizer24, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* itemButton25 = new wxButton( itemPanel17, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer24->AddButton(itemButton25);

    wxButton* itemButton26 = new wxButton( itemPanel17, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer24->AddButton(itemButton26);

    itemStdDialogButtonSizer24->Realize();

    itemSplitterWindow15->SplitHorizontally(itemCheckListBox16, itemPanel17, 50);
    itemSplitterWindow13->SplitVertically(itemTreeCtrl14, itemSplitterWindow15, 200);
    itemNotebook12->AddPage(itemSplitterWindow13, _("Tab"));

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
