/**
 * This file is part of scleaner project.

 * Copyright (C) 2008 FROUIN Jean-Michel

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

#include "systeminfos.h"

IMPLEMENT_DYNAMIC_CLASS( CSystemInfos, wxDialog )

BEGIN_EVENT_TABLE( CSystemInfos, wxDialog )

END_EVENT_TABLE()

CSystemInfos::CSystemInfos()
{
    Init();
}

CSystemInfos::CSystemInfos( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool CSystemInfos::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
        GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

CSystemInfos::~CSystemInfos()
{
}

void CSystemInfos::Init()
{
}

void CSystemInfos::CreateControls()
{
    CSystemInfos* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticText* itemStaticText3 = new wxStaticText( itemDialog1, wxID_STATIC, _("CPU Type (Freq)"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

        wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("Kernel version"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Avail / Free / Total RAM"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Avail / Free / Total Disk 1"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
}
