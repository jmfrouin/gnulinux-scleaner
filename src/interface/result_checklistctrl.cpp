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

// Include XPM icons
#include <gfx/checked.xpm>
#include <gfx/unchecked.xpm>
#include <gfx/folder.xpm>

#include <wx/menu.h>
#include <def.h>
#include <engine/engine.h>
#include "result_checklistctrl.h"

namespace GUI
{
    IMPLEMENT_CLASS(ResultCheckListCtrl, wxCheckListCtrl)

    ResultCheckListCtrl::ResultCheckListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pt,
    const wxSize& sz, long style):
    wxCheckListCtrl(parent, id, pt, sz, style)
    {
        LoadIcons();
    }


    ResultCheckListCtrl::~ResultCheckListCtrl()
    {
    }


    void ResultCheckListCtrl::OnContextMenu(wxContextMenuEvent& event)
    {
        wxPoint point = event.GetPosition();
        //std::cout << "Right click detected\n";
        // If from keyboard
        if (point.x == -1 && point.y == -1) {
            wxSize size = GetSize();
            point.x = size.x / 2;
            point.y = size.y / 2;
        } else {
            point = ScreenToClient(point);
        }
        ShowContextMenu(point);
    }


    void ResultCheckListCtrl::ShowContextMenu(const wxPoint& pos)
    {
        wxMenu menu;

        menu.Append(0, wxString(i8n("&Select all files"), wxConvUTF8));
        menu.Append(0, wxString(i8n("&Unselect all files"), wxConvUTF8));
        menu.Append(0, wxString(i8n("&Select all files from same folder"), wxConvUTF8));
        menu.Append(0, wxString(i8n("&Unselect all files from same folder"), wxConvUTF8));
        menu.Append(0, wxString(i8n("&Select all files with same extension"), wxConvUTF8));
        menu.Append(0, wxString(i8n("&Unselect all files with same extension"), wxConvUTF8));

        PopupMenu(&menu, pos.x, pos.y);
    }
}
