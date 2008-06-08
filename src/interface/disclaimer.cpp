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

#include "disclaimer.h"
#include <def.h>

IMPLEMENT_DYNAMIC_CLASS( CDisclaimer, wxDialog )

BEGIN_EVENT_TABLE( CDisclaimer, wxDialog )

END_EVENT_TABLE()

CDisclaimer::CDisclaimer()
{
    Init();
}

CDisclaimer::CDisclaimer( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool CDisclaimer::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
        GetSizer()->SetSizeHints(this);
    Centre();
    return true;
}

CDisclaimer::~CDisclaimer()
{
}

void CDisclaimer::Init()
{
}

void CDisclaimer::CreateControls()
{
    CDisclaimer* Disclaimer = this;

    wxBoxSizer* SizerV = new wxBoxSizer(wxVERTICAL);
    Disclaimer->SetSizer(SizerV);

    wxStaticText* Content = new wxStaticText(Disclaimer, wxID_STATIC, _("By clicking this option, you understand that you could dammage your computer (Until final version)"), wxDefaultPosition, wxDefaultSize, 0 );
    SizerV->Add(Content, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* SizerH = new wxBoxSizer(wxHORIZONTAL);
    SizerV->Add(SizerH, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* ButtonYes = new wxButton(Disclaimer, wxID_YES, _("I understand"), wxDefaultPosition, wxDefaultSize, 0 );
    SizerH->Add(ButtonYes, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* ButtonNo = new wxButton(Disclaimer, wxID_NO, _("I am not sure what to do"), wxDefaultPosition, wxDefaultSize, 0 );
    SizerH->Add(ButtonNo, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

}

