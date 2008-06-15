/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.org
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

#include "review.h"

IMPLEMENT_DYNAMIC_CLASS( CReview, wxDialog )

BEGIN_EVENT_TABLE( CReview, wxDialog )

END_EVENT_TABLE()


CReview::CReview()
{
    Init();
}

CReview::CReview(std::list<std::string> filelist, wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    Create(filelist, parent, id, caption, pos, size, style);
}

bool CReview::Create(std::list<std::string> filelist, wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls(filelist);
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}

CReview::~CReview()
{
}

void CReview::Init()
{
}

void CReview::CreateControls(std::list<std::string> filelist)
{
    CReview* Dialog = this;

    wxBoxSizer* Sizer = new wxBoxSizer(wxVERTICAL);
    Dialog->SetSizer(Sizer);

    wxListCtrl* List = new wxListCtrl( Dialog, ID_REVIEW_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    Sizer->Add(List, 0, wxGROW | wxALL, 5);

    wxBoxSizer* Sizer2 = new wxBoxSizer(wxHORIZONTAL);
    Sizer->Add(Sizer2, 0, wxGROW|wxALL, 5);

    wxButton* Cancel = new wxButton( Dialog, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    Sizer2->Add(Cancel, 0, wxGROW|wxALL, 5);

    wxButton* OK = new wxButton( Dialog, wxID_OK, _("Process"), wxDefaultPosition, wxDefaultSize, 0 );
    Sizer2->Add(OK, 0, wxGROW|wxALL, 5);
    wxListItem ItemCol;
    ItemCol.SetText(wxString(i8n("Name"), wxConvUTF8));

    ItemCol.SetImage(-1);
    List->InsertColumn(0, ItemCol);

    List->InsertItem(1, _("Poulpe"), 0);
    //wxListItem Item;
     //List->InsertItem(0, _("poulpe"), 0);
}

bool CReview::ShowToolTips()
{
    return true;
}

wxBitmap CReview::GetBitmapResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon CReview::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullIcon;
}
