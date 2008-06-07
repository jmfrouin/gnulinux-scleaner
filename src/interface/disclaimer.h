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

#ifndef __DISCLAIMER_H__
#define __DISCLAIMER_H__

#include "wx/hyperlink.h"

#define ID_CDISCLAIMER 10011
#define SYMBOL_CDISCLAIMER_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CDISCLAIMER_TITLE _("Disclaimer")
#define SYMBOL_CDISCLAIMER_IDNAME ID_CDISCLAIMER
#define SYMBOL_CDISCLAIMER_SIZE wxSize(400, 300)
#define SYMBOL_CDISCLAIMER_POSITION wxDefaultPosition

class CDisclaimer: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CDisclaimer )
    DECLARE_EVENT_TABLE()

    public:
        CDisclaimer();
        CDisclaimer( wxWindow* parent, wxWindowID id = SYMBOL_CDISCLAIMER_IDNAME, const wxString& caption = SYMBOL_CDISCLAIMER_TITLE, const wxPoint& pos = SYMBOL_CDISCLAIMER_POSITION, const wxSize& size = SYMBOL_CDISCLAIMER_SIZE, long style = SYMBOL_CDISCLAIMER_STYLE );

        bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CDISCLAIMER_IDNAME, const wxString& caption = SYMBOL_CDISCLAIMER_TITLE, const wxPoint& pos = SYMBOL_CDISCLAIMER_POSITION, const wxSize& size = SYMBOL_CDISCLAIMER_SIZE, long style = SYMBOL_CDISCLAIMER_STYLE );

        ~CDisclaimer();

        void Init();

        void CreateControls();
        wxBitmap GetBitmapResource( const wxString& name );

        wxIcon GetIconResource( const wxString& name );
        static bool ShowToolTips();
};

#endif // __DISCLAIMER_H__
