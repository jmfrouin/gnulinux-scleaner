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
$Date: 2007-09-21 19:43:56 +0200 (ven, 21 sep 2007) $
$Rev: 111 $
$Author: snoogie $
------------------------------------------------------
*/

#ifndef _WX_CHECKLISTCTRL_H_
#define _WX_CHECKLISTCTRL_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>

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

		/// Load the icons
		bool LoadIcons();

		/// Set the appropriate icon
		bool SetIcon(long& item);

	protected:
		wxImageList*        m_imageList;

		DECLARE_EVENT_TABLE()
};
#endif							 // _WB_CHECKLISTCTRL_H_
