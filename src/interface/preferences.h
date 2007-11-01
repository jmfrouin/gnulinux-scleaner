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

#ifndef _PREFERENCES_H_
#define _PREFERENCES_H_

#define ID_CPREFERENCES 10014
#define ID_RADIOBOX2 10015
#define SYMBOL_CPREFERENCES_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_CPREFERENCES_TITLE _("Preferences")
#define SYMBOL_CPREFERENCES_IDNAME ID_CPREFERENCES
#define SYMBOL_CPREFERENCES_SIZE wxSize(400, 300)
#define SYMBOL_CPREFERENCES_POSITION wxDefaultPosition

#include <wx/listbook.h>
#include <tools/smart_pointer.h>

namespace Engine
{
	class CEngine;
}

namespace GUI
{
	/*!
	 *@brief CPreferences class declaration
	 */
	class CPreferences: public wxDialog
	{    
	    DECLARE_DYNAMIC_CLASS( CPreferences )
	    DECLARE_EVENT_TABLE()
	
	public:
	    /// Constructors
	    CPreferences();
	    CPreferences( wxWindow* parent, wxWindowID id = SYMBOL_CPREFERENCES_IDNAME, const wxString& caption = SYMBOL_CPREFERENCES_TITLE, const wxPoint& pos = SYMBOL_CPREFERENCES_POSITION, const wxSize& size = SYMBOL_CPREFERENCES_SIZE, long style = SYMBOL_CPREFERENCES_STYLE );
	
	    /// Creation
	    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CPREFERENCES_IDNAME, const wxString& caption = SYMBOL_CPREFERENCES_TITLE, const wxPoint& pos = SYMBOL_CPREFERENCES_POSITION, const wxSize& size = SYMBOL_CPREFERENCES_SIZE, long style = SYMBOL_CPREFERENCES_STYLE );
	
	    /// Destructor
	    ~CPreferences();
	
	    /// Initialises member variables
	    void Init();
	
	    /// Creates the controls and sizers
	    void CreateControls();
	
	////@begin CPreferences event handler declarations
	
	////@end CPreferences event handler declarations
	
	////@begin CPreferences member function declarations
	
	    /// Retrieves bitmap resources
	    wxBitmap GetBitmapResource( const wxString& name );
	
	    /// Retrieves icon resources
	    wxIcon GetIconResource( const wxString& name );
	////@end CPreferences member function declarations
	
	    /// Should we show tooltips?
	    static bool ShowToolTips();
	
	private:
		//Engine
		Tools::TSmartPtr<Engine::CEngine>   m_Engine;
	};
}
#endif // _PREFERENCES_H_
