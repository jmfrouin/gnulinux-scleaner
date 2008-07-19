/////////////////////////////////////////////////////////////////////////////
// Name:        aboutdialog.h
// Purpose:
// Author:      Frouin Jean-Michel
// Modified by:
// Created:     Sun 15 Jun 2008 16:15:12 CEST
// RCS-ID:
// Copyright:   Project are under GNU GPL v3
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _ABOUTDIALOG_H_
#define _ABOUTDIALOG_H_

/*!
 * Includes
 */

////@begin includes
#include "wx/hyperlink.h"
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
#define ID_CABOUTDIALOG 10011
#define ID_HYPERLINKCTRL1 10013
#define ID_BUTTON 10000
#define SYMBOL_CABOUTDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CABOUTDIALOG_TITLE _("AboutDialog")
#define SYMBOL_CABOUTDIALOG_IDNAME ID_CABOUTDIALOG
#define SYMBOL_CABOUTDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_CABOUTDIALOG_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * CAboutDialog class declaration
 */

class CAboutDialog: public wxDialog
{
  DECLARE_DYNAMIC_CLASS( CAboutDialog )
    DECLARE_EVENT_TABLE()

    public:
    /// Constructors
    CAboutDialog();
    CAboutDialog( wxWindow* parent, wxWindowID id = SYMBOL_CABOUTDIALOG_IDNAME, const wxString& caption = SYMBOL_CABOUTDIALOG_TITLE, const wxPoint& pos = SYMBOL_CABOUTDIALOG_POSITION, const wxSize& size = SYMBOL_CABOUTDIALOG_SIZE, long style = SYMBOL_CABOUTDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CABOUTDIALOG_IDNAME, const wxString& caption = SYMBOL_CABOUTDIALOG_TITLE, const wxPoint& pos = SYMBOL_CABOUTDIALOG_POSITION, const wxSize& size = SYMBOL_CABOUTDIALOG_SIZE, long style = SYMBOL_CABOUTDIALOG_STYLE );

    /// Destructor
    ~CAboutDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    ////@begin CAboutDialog event handler declarations
    ////@end CAboutDialog event handler declarations

    ////@begin CAboutDialog member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
    ////@end CAboutDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    ////@begin CAboutDialog member variables
    ////@end CAboutDialog member variables
};
#endif
// _ABOUTDIALOG_H_
