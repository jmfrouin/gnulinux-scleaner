/////////////////////////////////////////////////////////////////////////////
// Name:        aboutdialog.cpp
// Purpose:
// Author:      Frouin Jean-Michel
// Modified by:
// Created:     Sun 06 Apr 2008 01:03:17 CEST
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

#include "aboutdialog.h"

////@begin XPM images
////@end XPM images


/*!
 * CAboutDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CAboutDialog, wxDialog )


/*!
 * CAboutDialog event table definition
 */

BEGIN_EVENT_TABLE( CAboutDialog, wxDialog )

////@begin CAboutDialog event table entries
////@end CAboutDialog event table entries

END_EVENT_TABLE()


/*!
 * CAboutDialog constructors
 */

CAboutDialog::CAboutDialog()
{
    Init();
}

CAboutDialog::CAboutDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CAboutDialog creator
 */

bool CAboutDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CAboutDialog creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    ////@end CAboutDialog creation
    return true;
}


/*!
 * CAboutDialog destructor
 */

CAboutDialog::~CAboutDialog()
{
////@begin CAboutDialog destruction
////@end CAboutDialog destruction
}


/*!
 * Member initialisation
 */

void CAboutDialog::Init()
{
////@begin CAboutDialog member initialisation
////@end CAboutDialog member initialisation
}


/*!
 * Control creation for CAboutDialog
 */

void CAboutDialog::CreateControls()
{
////@begin CAboutDialog content construction
    CAboutDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    /*wxStaticBitmap* itemStaticBitmap4 = new wxStaticBitmap( itemDialog1, wxID_STATIC, wxT("/usr/share/pixmaps/scleaner.png"), wxDefaultPosition, wxSize(24, 24), 0 );
    itemBoxSizer3->Add(itemStaticBitmap4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);*/

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("scleaner 0.40.0 beta 1"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Copyleft 2007-2008 Frouin Jean-Michel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText6, 0, wxALIGN_RIGHT|wxALL, 5);

    wxHyperlinkCtrl* itemHyperlinkCtrl7 = new wxHyperlinkCtrl( itemDialog1, ID_HYPERLINKCTRL1, _("Visit website"), _T("http://www.scleaner.fr"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
    itemBoxSizer2->Add(itemHyperlinkCtrl7, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer8, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText(itemDialog1, wxID_STATIC, _("I want to thanks all people who help me to release this beta (by alphabetical order):\nJacquier Pierre (webmaster of scleaner.fr)\nMedina Bastien (graphist)\nPaleino David(debian packager, italian translator)\nVoss Peer (german translator)\n"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemDialog1, wxID_STATIC, _("This software used other free softwares :\nwxWidgets for interface, libbz2 for archive compression,\nlibpthread for threads, libgd for plugins implementation,\ncmake for compilation managment.\n"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemButton11, 0, wxGROW|wxALL, 5);

////@end CAboutDialog content construction
}


/*!
 * Should we show tooltips?
 */

bool CAboutDialog::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CAboutDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    wxUnusedVar(name);
    if (name == _T("src/gfx/scleaner.png"))
    {
        wxBitmap bitmap(_T("src/gfx/scleaner.png"), wxBITMAP_TYPE_PNG);
        return bitmap;
    }
    return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon CAboutDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
}
