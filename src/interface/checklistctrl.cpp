/*
Copyright (C) 2007 FROUIN Jean-Michel
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
$Date: 2007-09-20 19:54:41 +0200 (jeu, 20 sep 2007) $
$Rev: 109 $
$Author: snoogie $
------------------------------------------------------
*/

// Include XPM icons
#include <gfx/checked.xpm>
#include <gfx/unchecked.xpm>
#include <gfx/folder.xpm>

#include <wx/menu.h>

#include <def.h>

#include "checklistctrl.h"

/*
 * wxCheckListCtrl
 */

IMPLEMENT_CLASS(wxCheckListCtrl, wxListCtrl)

BEGIN_EVENT_TABLE(wxCheckListCtrl, wxListCtrl)
	EVT_MOUSE_EVENTS(wxCheckListCtrl::OnMouseEvent)
	EVT_CHAR(wxCheckListCtrl::OnKeyDown)
    EVT_CONTEXT_MENU(wxCheckListCtrl::OnContextMenu)
END_EVENT_TABLE()

wxCheckListCtrl::wxCheckListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pt,
const wxSize& sz, long style):
wxListCtrl(parent, id, pt, sz, style)
{
	LoadIcons();
}


/// Load the icons
bool wxCheckListCtrl::LoadIcons()
{
	//FIXME : Manual delete need
	m_imageList = new wxImageList(16, 16, true);
	AssignImageList(m_imageList, wxIMAGE_LIST_SMALL);

	m_imageList->Add(wxIcon(checked_xpm));
	m_imageList->Add(wxIcon(unchecked_xpm));
	m_imageList->Add(wxIcon(folder_xpm));

	return true;
}


wxCheckListCtrl::~wxCheckListCtrl()
{
}


/// Set the appropriate icon
bool wxCheckListCtrl::SetIcon(long& item)
{
	bool l_ret = true;

	wxListItem l_item;
	l_item.SetId(item);
	GetItem(l_item);

	if(l_item.GetImage() == 0)
	{
		//SetItemImage(item, 1);
	}
	else
	{
		//SetItemImage(item, 0);
	}

	SetItemImage(item, 2);

	return l_ret;
}


void wxCheckListCtrl::OnMouseEvent(wxMouseEvent& event)
{
	int l_flags = 0;
	long l_subitem;
	long l_item = HitTest(wxPoint(event.GetX(), event.GetY()), l_flags, &l_subitem);

	if (event.LeftDown())
	{
		if (l_flags & wxLIST_HITTEST_ONITEMICON)
		{
			SetIcon(l_item);
		}
	}

	event.Skip();
}


void wxCheckListCtrl::OnKeyDown(wxKeyEvent& event)
{
	int l_flags = 0;
	long l_subitem;
	long l_item = HitTest(wxPoint(event.GetX(), event.GetY()), l_flags, &l_subitem);

	if (event.GetKeyCode() == WXK_SPACE)
	{
		SetIcon(l_item);
	}
	else
	{
		event.Skip();
	}
}


void wxCheckListCtrl::OnContextMenu(wxContextMenuEvent& event)
{
    wxPoint point = event.GetPosition();
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


void wxCheckListCtrl::ShowContextMenu(const wxPoint& pos)
{
    wxMenu menu;

    menu.Append(ID_FOLDER_ADD, wxString(i8n("&Add a folder to scan\tCtrl-A"), wxConvUTF8));
    menu.Append(ID_FOLDER_DEL, wxString(i8n("&Remove selected folders from scan\tCtrl-D"), wxConvUTF8));

    PopupMenu(&menu, pos.x, pos.y);
}
