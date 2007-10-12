/////////////////////////////////////////////////////////////////////////////
// Name:        preferences.h
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Fri 12 Oct 2007 23:13:46 CEST
// RCS-ID:      
// Copyright:   Project are under GNU GPL v3
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PREFERENCES_H_
#define _PREFERENCES_H_

/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CPREFERENCES 10014
#define ID_RADIOBOX2 10015
#define SYMBOL_CPREFERENCES_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_CPREFERENCES_TITLE _("Preferences")
#define SYMBOL_CPREFERENCES_IDNAME ID_CPREFERENCES
#define SYMBOL_CPREFERENCES_SIZE wxSize(400, 300)
#define SYMBOL_CPREFERENCES_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CPreferences class declaration
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

////@begin CPreferences member variables
////@end CPreferences member variables
};

#endif
    // _PREFERENCES_H_
