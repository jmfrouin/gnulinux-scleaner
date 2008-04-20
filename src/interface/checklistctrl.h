/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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

#ifndef _WX_CHECKLISTCTRL_H_
#define _WX_CHECKLISTCTRL_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>

namespace GUI
{
    /*!
     * wxCheckListCtrl
     * The options hierarchy viewer.
     */

    class wxCheckListCtrl: public wxListCtrl
    {
    DECLARE_CLASS(wxCheckListCtrl)
        public:
            wxCheckListCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pt = wxDefaultPosition, const wxSize& sz = wxDefaultSize, long style = wxLC_REPORT | wxSUNKEN_BORDER | wxLC_HRULES);
            virtual ~wxCheckListCtrl();

            virtual void OnMouseEvent(wxMouseEvent& event);
            virtual void OnKeyDown(wxKeyEvent& event);

            /*!
            *@brief Load the icons
            */
            virtual bool LoadIcons();

            /// Set the appropriate icon
            virtual bool SetIcon(long& item);

        protected:
            wxImageList*        m_imageList;

    DECLARE_EVENT_TABLE()
    };
} // namespace
#endif                           // _WB_CHECKLISTCTRL_H_
