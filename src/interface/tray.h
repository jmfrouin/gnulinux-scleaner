/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
*/
/*
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
$Date$
$Rev$
$Author$
------------------------------------------------------

*/

#ifndef _TRAY_H_
#define _TRAY_H_

#include <wx/taskbar.h>
#include <tools/smart_pointer.h>

class CMainInterface;

class CTrayIcon: public wxTaskBarIcon, public CSmartCpt
{
	private:
		enum {
    		PU_RESTORE = 10001,
    		PU_NEW_ICON,
    		PU_OLD_ICON,
    		PU_EXIT,
    		PU_CHECKMARK,
    		PU_SUB1,
    		PU_SUB2,
    		PU_SUBMAIN
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
    	void OnMenuSetNewIcon(wxCommandEvent&);
    	void OnMenuSetOldIcon(wxCommandEvent&);
       	void OnMenuCheckmark(wxCommandEvent&);
       	void OnMenuUICheckmark(wxUpdateUIEvent&);
    	void OnMenuSub(wxCommandEvent&);
    	virtual wxMenu *CreatePopupMenu();

	public: 
		CMainInterface*	m_Parent;

	DECLARE_EVENT_TABLE()
};

#endif //_TRAY_H_
/* vi:set ts=4: */
