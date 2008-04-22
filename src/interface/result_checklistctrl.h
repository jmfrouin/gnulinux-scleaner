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

#include <wx/listctrl.h>
#include <wx/imaglist.h>

namespace GUI
{
    class ResultCheckListCtrl: public wxListCtrl
    {
        DECLARE_CLASS(ResultCheckListCtrl)
        public:
            ResultCheckListCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pt = wxDefaultPosition,
                const wxSize& sz = wxDefaultSize, long style = wxLC_REPORT | wxSUNKEN_BORDER | wxLC_HRULES);
            virtual ~ResultCheckListCtrl();

            /*!
            *@brief Callbacks
            */
            virtual void OnMouseEvent(wxMouseEvent& event);
            virtual void OnKeyDown(wxKeyEvent& event);
            void OnContextMenu(wxContextMenuEvent& event);
            void ShowContextMenu(const wxPoint& pos);
            void OnSelectAll(wxCommandEvent& event);
            void OnUnselectAll(wxCommandEvent& event);
            void OnSelectFromSameFolder(wxCommandEvent& event);
            void OnUnselectFromSameFolder(wxCommandEvent& event);
            void OnSelectFromSameExtension(wxCommandEvent& event);
            void OnUnselectFromSameExtension(wxCommandEvent& event);

            virtual bool LoadIcons();
            virtual bool SetIcon(long& item);

        private:
            long GetSelection();

        protected:
            wxImageList*        m_imageList;

    DECLARE_EVENT_TABLE()

    };
} // namespace
#endif                           // __RESULT_CHECKLISTCTRL_H__
