/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

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

#ifndef _ABOUTDIALOG_H_
#define _ABOUTDIALOG_H_

#include "wx/hyperlink.h"

#define ID_CABOUTDIALOG 10011
#define ID_HYPERLINKCTRL1 10013
#define ID_BUTTON 10000
#define SYMBOL_CABOUTDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CABOUTDIALOG_TITLE _("AboutDialog")
#define SYMBOL_CABOUTDIALOG_IDNAME ID_CABOUTDIALOG
#define SYMBOL_CABOUTDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_CABOUTDIALOG_POSITION wxDefaultPosition

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

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );

    /// Should we show tooltips?
    static bool ShowToolTips();
};

#endif
    // _ABOUTDIALOG_H_
