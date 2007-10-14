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

#ifndef _TRAY_H_
#define _TRAY_H_

#include <wx/taskbar.h>
#include <tools/smart_pointer.h>

namespace GUI
{
	class CMainInterface;
}

namespace GUI
{
	class CTrayIcon: public wxTaskBarIcon, public Tools::CSmartCpt
	{
		private:
			enum
			{
				PU_RESTORE = 10001,
				PU_EXIT,
			};
	
		public:
		#if defined(__WXCOCOA__)
			CTrayIcon(wxTaskBarIconType iconType = DEFAULT_TYPE):
			wxTaskBarIcon(iconType), m_Parent(0)
			#else
				CTrayIcon():
			m_Parent(0)
			#endif
				{}
	
			void setParent(CMainInterface* _parent);
			void OnLeftButtonDClick(wxTaskBarIconEvent&);
			void OnMenuRestore(wxCommandEvent&);
			void OnMenuExit(wxCommandEvent&);
			virtual wxMenu *CreatePopupMenu();
	
		public:
			CMainInterface* m_Parent;
	
			DECLARE_EVENT_TABLE()
	};
}
#endif							 //_TRAY_H_
/* vi:set ts=4: */
