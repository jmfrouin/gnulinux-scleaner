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

#ifndef __RESULT_CHECKLISTCTRL_H__
#define __RESULT_CHECKLISTCTRL_H__

#include "checklistctrl.h"

namespace GUI
{
    /*!
     * wxCheckListCtrl for Result files list
     */

    class ResultCheckListCtrl: public wxCheckListCtrl
    {
        DECLARE_CLASS(ResultCheckListCtrl)
            public:
            ResultCheckListCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pt = wxDefaultPosition,
                const wxSize& sz = wxDefaultSize, long style = wxLC_REPORT | wxSUNKEN_BORDER | wxLC_HRULES);
            virtual ~ResultCheckListCtrl();

            /*!
            *@brief Callbacks
            */
            void OnContextMenu(wxContextMenuEvent& event);
            void ShowContextMenu(const wxPoint& pos);
    };
} // namespace
#endif                           // __RESULT_CHECKLISTCTRL_H__
