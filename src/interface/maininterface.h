/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)

------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------
Project : scleaner
------------------------------------------------------
$Date$
$Rev$
$Author$
------------------------------------------------------

*/

#ifndef _MAININTERFACE_H_
#define _MAININTERFACE_H_

#include <config.h>
#include <wx/frame.h>
#include <wx/toolbar.h>
#include <wx/splitter.h>
//#include <wx/treectrl.h>
#include "checktreectrl.h"
#include <wx/statusbr.h>
#include "tray.h"

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
