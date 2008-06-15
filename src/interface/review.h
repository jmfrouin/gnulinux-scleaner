/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.org
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

#ifndef __REVIEW_H__
#define __REVIEW_H__

#include "wx/listctrl.h"
#include <list>
#include <string>
#include <def.h>

namespace GUI
{
    class CReview: public wxDialog
    {
        DECLARE_DYNAMIC_CLASS( CReview )
        DECLARE_EVENT_TABLE()

    public:
        CReview();
        CReview(std::list<std::string> filelist, wxWindow* parent, wxWindowID id = ID_REVIEW, const wxString& caption = SYMBOL_REVIEW_TITLE, const wxPoint& pos = SYMBOL_POSITION, const wxSize& size = SYMBOL_DIALOG_SIZE, long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL);

        bool Create(std::list<std::string> filelist, wxWindow* parent, wxWindowID id = ID_REVIEW, const wxString& caption = SYMBOL_REVIEW_TITLE, const wxPoint& pos = SYMBOL_POSITION, const wxSize& size = SYMBOL_DIALOG_SIZE, long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL);

        ~CReview();

        void Init();

        void CreateControls(std::list<std::string> filelist);

        wxBitmap GetBitmapResource( const wxString& name );

        wxIcon GetIconResource( const wxString& name );

        static bool ShowToolTips();
    };
}
#endif    // __REVIEW_H__
