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

#include "checklistctrl.h"

/*
 * wxCheckListCtrl
 */

IMPLEMENT_CLASS(wxCheckListCtrl, wxListCtrl)

BEGIN_EVENT_TABLE(wxCheckListCtrl, wxListCtrl)
    EVT_MOUSE_EVENTS(wxCheckListCtrl::OnMouseEvent)
    EVT_CHAR(wxCheckListCtrl::OnKeyDown)
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
    m_imageList = new wxImageList(16, 16, true);
    AssignImageList(m_imageList, wxIMAGE_LIST_SMALL);

    m_imageList->Add(wxIcon(checked_xpm));
    m_imageList->Add(wxIcon(unchecked_xpm));

    return true;
}

wxCheckListCtrl::~wxCheckListCtrl()
{
}

/// Set the appropriate icon
bool wxCheckListCtrl::SetIcon(long& item)
{
	std::cout << "SetIcon : Item = " << item << '\n';
	wxListItem l_item;
	l_item.SetId(item);
	GetItem(l_item);

	if(l_item.GetImage() == 0)
	{
        SetItemImage(item, 1);
	}
	else
	{
        SetItemImage(item, 0);
	}

	return true;
}


void wxCheckListCtrl::OnMouseEvent(wxMouseEvent& event)
{
    int flags = 0;
	long l_subitem;
    long item = HitTest(wxPoint(event.GetX(), event.GetY()), flags, &l_subitem);
	std::cout << "Item : " << std::dec << item << '\n';
    
    if (event.LeftDown())
    {
		SetIcon(item);
    }

    event.Skip();
}

void wxCheckListCtrl::OnKeyDown(wxKeyEvent& event)
{
    /*wxListItem item = GetSelection();
    if (event.GetKeyCode() == WXK_SPACE)
    {
        if (item.IsOk())
        {
            wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(item);

            if (data && data->GetEnabled())
            {
                data->SetChecked(!data->GetChecked());
                SetIcon(item);

                wxCheckListEvent commandEvent(wxEVT_COMMAND_CHECKLISTCTRL_TOGGLED, GetId());
                commandEvent.SetEventObject(this);
                commandEvent.SetListItemId(item);
                commandEvent.SetChecked(data->GetChecked());
                commandEvent.SetData(data);
                GetEventHandler()->ProcessEvent(commandEvent);
            }
        }
    }
    else
    {
        event.Skip();
    }*/
        event.Skip();
}
