/////////////////////////////////////////////////////////////////////////////
// Name:        preferences.cpp
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Fri 12 Oct 2007 23:13:46 CEST
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

#include "preferences.h"

////@begin XPM images
////@end XPM images


/*!
 * CPreferences type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CPreferences, wxDialog )


/*!
 * CPreferences event table definition
 */

BEGIN_EVENT_TABLE( CPreferences, wxDialog )

////@begin CPreferences event table entries
////@end CPreferences event table entries

END_EVENT_TABLE()


/*!
 * CPreferences constructors
 */

CPreferences::CPreferences()
{
    Init();
}

CPreferences::CPreferences( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * CPreferences creator
 */

bool CPreferences::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CPreferences creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CPreferences creation
    return true;
}


/*!
 * CPreferences destructor
 */

CPreferences::~CPreferences()
{
////@begin CPreferences destruction
////@end CPreferences destruction
}


/*!
 * Member initialisation
 */

void CPreferences::Init()
{
////@begin CPreferences member initialisation
////@end CPreferences member initialisation
}


/*!
 * Control creation for CPreferences
 */

void CPreferences::CreateControls()
{    
////@begin CPreferences content construction
    CPreferences* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxArrayString itemRadioBox3Strings;
    itemRadioBox3Strings.Add(_("&CRC32"));
    itemRadioBox3Strings.Add(_("&MD5"));
    wxRadioBox* itemRadioBox3 = new wxRadioBox( itemDialog1, ID_RADIOBOX2, _("Duplicates files method"), wxDefaultPosition, wxDefaultSize, itemRadioBox3Strings, 1, wxRA_SPECIFY_ROWS );
    itemRadioBox3->SetSelection(0);
    itemBoxSizer2->Add(itemRadioBox3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end CPreferences content construction
}


/*!
 * Should we show tooltips?
 */

bool CPreferences::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CPreferences::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CPreferences bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CPreferences bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CPreferences::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CPreferences icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CPreferences icon retrieval
}
