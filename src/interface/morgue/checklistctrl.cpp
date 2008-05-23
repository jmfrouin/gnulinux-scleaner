/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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
        fImageList = new wxImageList(16, 16, true);
        AssignImageList(fImageList, wxIMAGE_LIST_SMALL);

        fImageList->Add(wxIcon(checked_xpm));
        fImageList->Add(wxIcon(checked_dis_xpm));
        fImageList->Add(wxIcon(unchecked_xpm));
        fImageList->Add(wxIcon(unchecked_dis_xpm));

        return true;
}


wxCheckListCtrl::~wxCheckListCtrl()
{
}


/// Set the appropriate icon
bool wxCheckListCtrl::SetIcon(long& item)
{
        wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(item);
        std::cout << "SetIcon : " << data << '\n';
        if (data)
        {
                int imageIndex = 0;
                if (data->GetChecked())
                {
                        if (data->GetEnabled())
                        {
                                imageIndex = wxCHECKLIST_IMAGE_CHILD_CHECK_ENABLED;
                        }
                        else
                        {
                                imageIndex = wxCHECKLIST_IMAGE_CHILD_CHECK_DISABLED;
                        }
                }
                else
                {
                        if (data->GetEnabled())
                        {
                                imageIndex = wxCHECKLIST_IMAGE_CHILD_UNCHECKED_ENABLED;
                        }
                        else
                        {
                                imageIndex = wxCHECKLIST_IMAGE_CHILD_UNCHECKED_DISABLED;
                        }
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
        long l_subitem;
        long item = HitTest(wxPoint(event.GetX(), event.GetY()), flags, &l_subitem);
        std::cout << "Item : " << std::dec << item << '\n';

        if (event.LeftDown())
        {
                if (flags & wxLIST_HITTEST_ONITEMICON)
                {
                        std::cout << "Flag: " << flags << '\n';
                        std::cout << "Item: " << std::dec << item << '\n';
                        //wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(item);
                        wxListItem l_item;
                        l_item.SetId(item);
                        GetItem(l_item);
                        wxCheckListItemAttr* data = (wxCheckListItemAttr*) l_item.GetData();
                        std::cout << l_item.GetText().char_str() << '\n';

                        std::cout << "Data: " << data << '\n';
                        std::cout << "Image: " << l_item.GetImage() << '\n';

                        if(data != 0)
                        {
                                std::cout << "mouse event" << data->GetEnabled() << " " << data->GetChecked() << '\n';
                        }

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
        wxCheckListItemAttr* data = (wxCheckListItemAttr*) GetItemData(10);
        std::cout << "Data: " << data << '\n';
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


/// Check/uncheck the item
bool wxCheckListCtrl::CheckItem(long& item, bool check)
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
bool wxCheckListCtrl::EnableItem(long& item, bool enable)
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
long wxCheckListCtrl::AddCheckedItem(int _counter, const wxString& _label, bool _checked)
{
        long Ret;
        wxListItem l_item;

        l_item.SetText(_label);
        l_item.SetImage(1);

        //Ret = InsertItem(_counter, _label, 1);

        wxCheckListItemAttr* l_data = new wxCheckListItemAttr;
        l_data->SetChecked(_checked);
        l_data->SetTranslatedLabel(_label);
        l_data->SetUntranslatedLabel(_label);

        //SetItemData(Ret, (long)l_data);
        //SetItemPtrData(Ret, (wxUIntPtr) l_data);
        l_item.SetData((long)l_data);

        Ret = InsertItem(l_item);

        std::cout << "AddCheckedItem " << _label << " data @ " <<  l_data << " Item : " << Ret << '\n';
        std::cout << "Data retrieve : 0x" << std::hex << l_item.GetData() << '\n';
        SetIcon(Ret);

        return Ret;
}
