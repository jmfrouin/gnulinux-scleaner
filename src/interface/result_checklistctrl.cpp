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
    IMPLEMENT_CLASS(ResultCheckListCtrl, wxListCtrl)

    BEGIN_EVENT_TABLE(ResultCheckListCtrl, wxListCtrl)
        EVT_MOUSE_EVENTS(ResultCheckListCtrl::OnMouseEvent)
        EVT_CHAR(ResultCheckListCtrl::OnKeyDown)
        EVT_CONTEXT_MENU(ResultCheckListCtrl::OnContextMenu)
        EVT_LIST_COL_CLICK(ID_RESCHECKLIST, ResultCheckListCtrl::OnColClick)
        EVT_MENU(ID_SELECT_ALL, ResultCheckListCtrl::OnSelectAll)
        EVT_MENU(ID_UNSELECT_ALL, ResultCheckListCtrl::OnUnselectAll)
        EVT_MENU(ID_INVERT_SELECTION, ResultCheckListCtrl::OnInvertSelection)
        EVT_MENU(ID_SELECT_FROM_SAME_FOLDER, ResultCheckListCtrl::OnSelectFromSameFolder)
        EVT_MENU(ID_UNSELECT_FROM_SAME_FOLDER, ResultCheckListCtrl::OnUnselectFromSameFolder)
    END_EVENT_TABLE()

    ResultCheckListCtrl::ResultCheckListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pt,
    const wxSize& sz, long style):
    wxListCtrl(parent, id, pt, sz, style)
    {
        LoadIcons();
    }

    bool ResultCheckListCtrl::LoadIcons()
    {
        //FIXME : Manual delete need
        m_imageList = new wxImageList(16, 16, true);
        AssignImageList(m_imageList, wxIMAGE_LIST_SMALL);

        m_imageList->Add(wxIcon(checked_xpm));
        m_imageList->Add(wxIcon(unchecked_xpm));
        m_imageList->Add(wxIcon(folder_xpm));

        return true;
    }

    ResultCheckListCtrl::~ResultCheckListCtrl()
    {
    }

    bool ResultCheckListCtrl::SetIcon(long& item)
    {
        bool l_ret = true;

        wxListItem l_item;
        l_item.SetId(item);
        GetItem(l_item);
        wxString l_text = l_item.GetText();

        if(l_item.GetImage() == 0)
        {
            Engine::CEngine::Instance()->SetUnselectedInputPlugs(std::string(l_text.ToAscii()));
            SetItemImage(item, 1);
        }
        else
            SetItemImage(item, 0);

        return l_ret;
    }


    void ResultCheckListCtrl::OnMouseEvent(wxMouseEvent& event)
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


    void ResultCheckListCtrl::OnKeyDown(wxKeyEvent& event)
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

        if(GetSelectionCount() ==1)
        {
            //Context menu for 1 selected item by user
            menu.Append(ID_SELECT_ALL, wxString(i8n("&Select all files"), wxConvUTF8));
            menu.Append(ID_UNSELECT_ALL, wxString(i8n("&Unselect all files"), wxConvUTF8));
            menu.Append(ID_INVERT_SELECTION, wxString(i8n("&Invert selection"), wxConvUTF8));
            menu.AppendSeparator();
            menu.Append(ID_SELECT_FROM_SAME_FOLDER, wxString(i8n("&Select all files from same folder"), wxConvUTF8));
            menu.Append(ID_UNSELECT_FROM_SAME_FOLDER, wxString(i8n("&Unselect all files from same folder"), wxConvUTF8));
        }
        else
        {
            //Context menu for more than 1 selected item by user
            menu.Append(ID_SELECT_ALL, wxString(i8n("&Select all files"), wxConvUTF8));
            menu.Append(ID_UNSELECT_ALL, wxString(i8n("&Unselect all files"), wxConvUTF8));
            menu.Append(ID_INVERT_SELECTION, wxString(i8n("&Invert selection"), wxConvUTF8));
        }

        PopupMenu(&menu, pos.x, pos.y);
    }

    void ResultCheckListCtrl::OnSelectAll(wxCommandEvent& WXUNUSED(event))
    {
        long Item = -1;
        if(GetSelectionCount() == 1)
        {
            //If user has selected only 1 item, that apply to all files
            for ( ;; )
            {
                Item = GetNextItem(Item);
                if(Item == -1)
                    break;
                SetItemImage(Item, 0);
            }
        }
        else
        {
            //If user has selected more than 1 item, that apply to selected files
            for ( ;; )
            {
                Item = GetNextItem(Item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
                if(Item == -1)
                    break;
                SetItemImage(Item, 0);
            }
        }
    }

    void ResultCheckListCtrl::OnUnselectAll(wxCommandEvent& WXUNUSED(event))
    {
        long Item = -1;
        if(GetSelectionCount() == 1)
        {
            //If user has selected only 1 item, that apply to all files
            for ( ;; )
            {
                Item = GetNextItem(Item);
                if(Item == -1)
                    break;
                SetItemImage(Item, 1);
            }
        }
        else
        {
            //If user has selected more than 1 item, that apply to selected files
            for ( ;; )
            {
                Item = GetNextItem(Item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
                if(Item == -1)
                    break;
                SetItemImage(Item, 1);
            }
        }
    }

    void ResultCheckListCtrl::OnInvertSelection(wxCommandEvent& event)
    {
        long Item = -1;
        if(GetSelectionCount() == 1)
        {
            //If user has selected only 1 item, that apply to all files
            for ( ;; )
            {
                Item = GetNextItem(Item);
                if(Item == -1)
                    break;

                wxListItem LItem;
                LItem.SetId(Item);
                GetItem(LItem);

                if(LItem.GetImage())
                    SetItemImage(Item, 0);
                else
                    SetItemImage(Item, 1);
            }
        }
        else
        {
            //If user has selected more than 1 item, that apply to selected files
            for ( ;; )
            {
                Item = GetNextItem(Item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
                if(Item == -1)
                    break;

                wxListItem LItem;
                LItem.SetId(Item);
                GetItem(LItem);

                if(LItem.GetImage())
                    SetItemImage(Item, 0);
                else
                    SetItemImage(Item, 1);
            }
        }
    }

    void ResultCheckListCtrl::OnSelectFromSameFolder(wxCommandEvent& event)
    {
        long Item = -1;
        wxString Folder = GetSelectionFolderName();
        for ( ;; )
        {
            Item = GetNextItem(Item);
            if(Item == -1)
                break;

            wxListItem LItem;
            LItem.SetId(Item);
            LItem.SetColumn(2);
            GetItem(LItem);
            std::cout << LItem.m_text << " = ";
            std::cout << Folder << '\n';
            if(LItem.m_text.Find(Folder) != wxNOT_FOUND)
                SetItemImage(Item, 0);
        }
    }

    void ResultCheckListCtrl::OnUnselectFromSameFolder(wxCommandEvent& event)
    {
        long Item = -1;
        wxString Folder = GetSelectionFolderName();
        for ( ;; )
        {
            Item = GetNextItem(Item);
            if(Item == -1)
                break;

            wxListItem LItem;
            LItem.SetId(Item);
            LItem.SetColumn(2);
            GetItem(LItem);
            if(LItem.m_text.Find(Folder) != wxNOT_FOUND)
                SetItemImage(Item, 1);
        }
    }

    void ResultCheckListCtrl::OnColClick(wxListEvent& event)
    {

    }

    //Private
    long ResultCheckListCtrl::GetSelection()
    {
        long Item = -1;
        for(;;)
        {
            Item = GetNextItem(Item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

            if(Item == -1)
                break;
            else
                return Item;
        }
        return Item;
    }

    wxString ResultCheckListCtrl::GetSelectionFolderName()
    {
        long Item = -1;
        wxString Res;
        for(;;)
        {
            Item = GetNextItem(Item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

            if(Item == -1)
                break;
            else
            {
                wxListItem LItem;
                LItem.SetId(Item);
                LItem.SetColumn(2);
                GetItem(LItem);
                return LItem.m_text;
            }
        }
        return Res;
    }

     int ResultCheckListCtrl::GetSelectionCount()
    {
        int Count = 0;
        long Item = -1;
        for(;;)
        {
            Item = GetNextItem(Item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
            if(Item == -1)
                break;
            else
                Count++;
        }
        return Count;
    }
}

