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

#include <wx/imaglist.h>

// Include XPM icons
#include <gfx/checked.xpm>
#include <gfx/checked_dis.xpm>
#include <gfx/unchecked.xpm>
#include <gfx/unchecked_dis.xpm>

#include "checklistctrl.h"

/*
 * wxCheckListCtrl
 */

IMPLEMENT_CLASS(wxCheckListCtrl, wxListCtrl)

BEGIN_EVENT_TABLE(wxCheckListCtrl, wxListCtrl)
    EVT_MOUSE_EVENTS(wxCheckListCtrl::OnMouseEvent)
    EVT_CHAR(wxCheckListCtrl::OnKeyDown)
END_EVENT_TABLE()

DEFINE_EVENT_TYPE(wxEVT_COMMAND_CHECKLISTCTRL_TOGGLED)
IMPLEMENT_DYNAMIC_CLASS(wxCheckListEvent, wxNotifyEvent)

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
    AssignImageList(m_imageList);

    m_imageList->Add(wxIcon(checked_xpm));
    m_imageList->Add(wxIcon(checked_dis_xpm));
    m_imageList->Add(wxIcon(unchecked_xpm));
    m_imageList->Add(wxIcon(unchecked_dis_xpm));

#if 0
    m_imageList->Add(wxIcon(closedfolder_xpm), 0, true);
    m_imageList->Add(wxIcon(closedfolder_dis_xpm), 0, false);
#endif
    
    return true;
}

wxCheckListCtrl::~wxCheckListCtrl()
{
}

/// Set the appropriate icon
bool wxCheckListCtrl::SetIcon(wxListItem& item)
{
    wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(item);
    if (data)
    {
        int imageIndex = 0;
        if (data->GetChecked())
        {
            if (data->GetEnabled())
                imageIndex = wxCHECKLIST_IMAGE_CHILD_CHECK_ENABLED;
            else
                imageIndex = wxCHECKLIST_IMAGE_CHILD_CHECK_DISABLED;
        }
        else
        {
            if (data->GetEnabled())
                imageIndex = wxCHECKLIST_IMAGE_CHILD_UNCHECKED_ENABLED;
            else
                imageIndex = wxCHECKLIST_IMAGE_CHILD_UNCHECKED_DISABLED;
        }
        SetItemImage(item, imageIndex);

        return true;
    }
    else
        return false;
}


void wxCheckListCtrl::OnMouseEvent(wxMouseEvent& event)
{
    int flags = 0;
    wxListItem item = HitTest(wxPoint(event.GetX(), event.GetY()), flags);
    
    if (event.LeftDown())
    {
        if (flags & wxLIST_HITTEST_ONITEMICON)
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

    event.Skip();
}

void wxCheckListCtrl::OnKeyDown(wxKeyEvent& event)
{
    wxListItem item = GetSelection();
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
    }
}

/// Check/uncheck the item
bool wxCheckListCtrl::CheckItem(wxListItem& item, bool check)
{
    wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(item);
    
    if (data)
    {
        data->SetChecked(check);
        SetIcon(item);
    }
    return true;
}

/// Enable/disable the item
bool wxCheckListCtrl::EnableItem(wxListItem& item, bool enable)
{
    wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(item);
    
    if (data)
    {
        data->SetEnabled(enable);
        SetIcon(item);
    }
    return true;
}

/// Add an item
wxListItem wxCheckListCtrl::AddCheckedItem(wxListItem& parent, const wxString& label, bool checked)
{
    wxCheckListItemAttr* data = new wxCheckListItemAttr;
    data->SetChecked(checked);
    data->SetTranslatedLabel(label);
    data->SetUntranslatedLabel(label);
    wxListItem id = AppendItem(parent, label, -1, -1, data);
    SetIcon(id);

    return id;
}

/// Add an item with separate translated and untranslated labels
wxListItem wxCheckListCtrl::AddCheckedItem(wxListItem& parent, const wxString& translatedLabel, const wxString& untranslatedLabel, bool checked)
{
    wxCheckListItemAttr* data = new wxCheckListItemAttr;
    data->SetChecked(checked);
    data->SetTranslatedLabel(translatedLabel);
    data->SetUntranslatedLabel(untranslatedLabel);
    wxListItem id = AppendItem(parent, translatedLabel, -1, -1, data);
    SetIcon(id);

    return id;
}

/// Get the data for the item
wxCheckListItemAttr* wxCheckListCtrl::GetData(wxListItem& item)
{
    wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(item);
    return data;
}


