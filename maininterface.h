/////////////////////////////////////////////////////////////////////////////
// Name:        maininterface.h
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Sat 25 Aug 2007 21:48:48 CEST
// RCS-ID:      
// Copyright:   Project are under GNU GPL v3
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAININTERFACE_H_
#define _MAININTERFACE_H_

/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
#include "wx/notebook.h"
#include "wx/splitter.h"
#include "wx/treectrl.h"
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
#define ID_MAININTERFACE 10000
#define ID_TOOLBAR1 10002
#define ID_TOOL1 10003
#define ID_TOOL2 10004
#define ID_TOOL3 10005
#define ID_TOOL4 10006
#define ID_STATUSBAR1 10008
#define ID_PANEL2 10012
#define ID_NOTEBOOK1 10013
#define ID_SPLITTERWINDOW1 10007
#define ID_TREECTRL1 10009
#define ID_SPLITTERWINDOW2 10001
#define ID_CHECKLISTBOX1 10010
#define ID_PANEL1 10011
#define SYMBOL_MAININTERFACE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_MAININTERFACE_TITLE _("MainInterface")
#define SYMBOL_MAININTERFACE_IDNAME ID_MAININTERFACE
#define SYMBOL_MAININTERFACE_SIZE wxSize(400, 300)
#define SYMBOL_MAININTERFACE_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * MainInterface class declaration
 */

class MainInterface: public wxFrame
{    
    DECLARE_CLASS( MainInterface )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MainInterface();
    MainInterface( wxWindow* parent, wxWindowID id = SYMBOL_MAININTERFACE_IDNAME, const wxString& caption = SYMBOL_MAININTERFACE_TITLE, const wxPoint& pos = SYMBOL_MAININTERFACE_POSITION, const wxSize& size = SYMBOL_MAININTERFACE_SIZE, long style = SYMBOL_MAININTERFACE_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MAININTERFACE_IDNAME, const wxString& caption = SYMBOL_MAININTERFACE_TITLE, const wxPoint& pos = SYMBOL_MAININTERFACE_POSITION, const wxSize& size = SYMBOL_MAININTERFACE_SIZE, long style = SYMBOL_MAININTERFACE_STYLE );

    /// Destructor
    ~MainInterface();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin MainInterface event handler declarations

////@end MainInterface event handler declarations

////@begin MainInterface member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MainInterface member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MainInterface member variables
////@end MainInterface member variables
};

#endif
    // _MAININTERFACE_H_
