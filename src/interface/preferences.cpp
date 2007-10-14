/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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

#include "preferences.h"

namespace GUI
{
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
}
