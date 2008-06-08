/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.fr
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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "aboutdialog.h"
#include <def.h>

IMPLEMENT_DYNAMIC_CLASS( CAboutDialog, wxDialog )

BEGIN_EVENT_TABLE( CAboutDialog, wxDialog )

END_EVENT_TABLE()

CAboutDialog::CAboutDialog()
{
    Init();
}

CAboutDialog::CAboutDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool CAboutDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}

CAboutDialog::~CAboutDialog()
{
}

void CAboutDialog::Init()
{
}

void CAboutDialog::CreateControls()
{
    CAboutDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    /*wxStaticBitmap* itemStaticBitmap4 = new wxStaticBitmap( itemDialog1, wxID_STATIC, wxT("/usr/share/pixmaps/scleaner.png"), wxDefaultPosition, wxSize(24, 24), 0 );
    itemBoxSizer3->Add(itemStaticBitmap4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);*/

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _(NAME), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Copyleft 2007-2008 Frouin Jean-Michel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText6, 0, wxALIGN_RIGHT|wxALL, 5);

    wxHyperlinkCtrl* itemHyperlinkCtrl7 = new wxHyperlinkCtrl( itemDialog1, ID_ABOUTDIALOG_WEBLINK, _("Visit website"), _T("http://www.scleaner.fr"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
    itemBoxSizer2->Add(itemHyperlinkCtrl7, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer8, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText(itemDialog1, wxID_STATIC, _("I want to thanks all people who help me to release this beta (by alphabetical order):\nJacquier Pierre (webmaster of scleaner.fr)\nMedina Bastien (graphist)\nPaleino David(debian packager, italian translator)\nVoss Peer (german translator)\n"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemDialog1, wxID_STATIC, _("This software used other free softwares :\nwxWidgets for interface, libbz2 for archive compression,\nlibpthread for threads, libgd for plugins implementation,\ncmake for compilation managment.\n"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemButton11, 0, wxGROW|wxALL, 5);
}

bool CAboutDialog::ShowToolTips()
{
    return true;
}

wxBitmap CAboutDialog::GetBitmapResource( const wxString& name )
{
    wxUnusedVar(name);
    if (name == _T("src/gfx/scleaner.png"))
    {
        wxBitmap bitmap(_T("src/gfx/scleaner.png"), wxBITMAP_TYPE_PNG);
        return bitmap;
    }
    return wxNullBitmap;
}

wxIcon CAboutDialog::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullIcon;
}
