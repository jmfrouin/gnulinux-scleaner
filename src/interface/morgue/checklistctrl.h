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

#ifndef _WX_CHECKLISTCTRL_H_
#define _WX_CHECKLISTCTRL_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>

// Type of item

#define wxCHECKLIST_ICON_CHILD       0x01
#define wxCHECKLIST_ICON_FOLDER      0x02

// Identifier of the icon
#define wxCHECKLIST_IMAGE_CHILD_CHECK_ENABLED     0
#define wxCHECKLIST_IMAGE_CHILD_CHECK_DISABLED    1
#define wxCHECKLIST_IMAGE_CHILD_UNCHECKED_ENABLED   2
#define wxCHECKLIST_IMAGE_CHILD_UNCHECKED_DISABLED  3

/*!
 * wxCheckListItemAttr
 * Holds the data for each list item.
 */

class wxCheckListItemAttr: public wxListItemAttr
{
        public:
                wxCheckListItemAttr() { m_checked = false; m_enabled = true; m_iconType = wxCHECKLIST_ICON_CHILD;}
                ~wxCheckListItemAttr()  {}

                void SetChecked(bool checked) { m_checked = checked; }
                bool GetChecked() const { return m_checked; }

                void SetEnabled(bool enabled) { m_enabled = enabled; }
                bool GetEnabled() const { return m_enabled; }

                void SetIconType(int iconType) { m_iconType = iconType; }
                int GetIconType() const { return m_iconType; }

                void SetTranslatedLabel(const wxString& label) { m_translatedLabel = label; }
                const wxString& GetTranslatedLabel() const { return m_translatedLabel; }

                void SetUntranslatedLabel(const wxString& label) { m_untranslatedLabel = label; }
                const wxString& GetUntranslatedLabel() const { return m_untranslatedLabel; }

        private:
                bool    m_checked;
                bool    m_enabled;
                int     m_iconType;

                wxString    m_untranslatedLabel;
                wxString    m_translatedLabel;
};

/*!
 * wxCheckListCtrl
 * The options hierarchy viewer.
 */

class wxCheckListCtrl: public wxListCtrl
{
        DECLARE_CLASS(wxCheckListCtrl)
                public:
                wxCheckListCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pt = wxDefaultPosition,
                        const wxSize& sz = wxDefaultSize, long style = wxLC_REPORT | wxSUNKEN_BORDER | wxLC_HRULES);
                ~wxCheckListCtrl();

                //// Event handlers
                void OnMouseEvent(wxMouseEvent& event);
                void OnKeyDown(wxKeyEvent& event);

                //// Accessors

                wxImageList* GetImageList() const { return fImageList; }

                //// Operations

                /// Add an item
                long AddCheckedItem(int _counter, const wxString& _label, bool _checked = false);

                /// Check/uncheck the item
                bool CheckItem(long& item, bool check);

                /// Enable/disable the item
                bool EnableItem(long& item, bool enable);

                /// Load the icons
                bool LoadIcons();

                /// Set the appropriate icon
                bool SetIcon(long& item);

        protected:
                wxImageList*        fImageList;

                DECLARE_EVENT_TABLE()
};

class wxCheckListEvent: public wxNotifyEvent
{
        public:
                wxCheckListEvent(wxEventType commandType = wxEVT_NULL, int id = 0):
                wxNotifyEvent(commandType, id)
                {
                        m_checked = false;
                        m_data = NULL;
                }

                void SetChecked(bool checked) { m_checked = checked; }
                bool IsChecked() const { return m_checked; }

                long GetListItemId() const { return m_listItemId; }
                void SetListItemId(long& id) { m_listItemId = id; }

                wxCheckListItemAttr* GetData() const { return m_data; }
                void SetData(wxCheckListItemAttr* data) { m_data = data; }

        private:
                bool                    m_checked;
                long                    m_listItemId;
                wxCheckListItemAttr*    m_data;

                DECLARE_DYNAMIC_CLASS(wxCheckListEvent);
};

typedef void (wxEvtHandler::*wxCheckListEventFunction)(wxCheckListEvent&);

// ----------------------------------------------------------------------------
// swatch control events and macros for handling them
// ----------------------------------------------------------------------------

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_COMMAND_CHECKLISTCTRL_TOGGLED, 900)
END_DECLARE_EVENT_TYPES()

#define EVT_CHECKLISTCTRL_TOGGLED(id, fn) DECLARE_EVENT_TABLE_ENTRY( wxEVT_COMMAND_CHECKLISTCTRL_TOGGLED, id, -1, (wxObjectEventFunction) (wxEventFunction) (wxCheckListEventFunction) & fn, (wxObject *) NULL ),
#endif                                                   // _WB_CHECKLISTCTRL_H_
