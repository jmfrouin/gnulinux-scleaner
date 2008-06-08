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

#include <def.h>
#include "wx/hyperlink.h"

class CDisclaimer: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CDisclaimer )
    DECLARE_EVENT_TABLE()

    public:
        CDisclaimer();
        CDisclaimer( wxWindow* parent, wxWindowID id = ID_DISCLAIMER, const wxString& caption = SYMBOL_DISCLAIMER_TITLE, const wxPoint& pos = SYMBOL_POSITION, const wxSize& size = SYMBOL_DIALOG_SIZE, long style = SYMBOL_DIALOG_STYLE );

        bool Create( wxWindow* parent, wxWindowID id = ID_DISCLAIMER, const wxString& caption = SYMBOL_DISCLAIMER_TITLE, const wxPoint& pos = SYMBOL_POSITION, const wxSize& size = SYMBOL_DIALOG_SIZE, long style = SYMBOL_DIALOG_STYLE );

        ~CDisclaimer();

        void Init();

        void CreateControls();
};

#endif // __DISCLAIMER_H__
