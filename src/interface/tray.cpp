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
$Date$
$Rev$
$Author$
------------------------------------------------------
*/

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "maininterface.h"
#include "tray.h"

BEGIN_EVENT_TABLE(CTrayIcon, wxTaskBarIcon)
EVT_MENU(PU_RESTORE, CTrayIcon::OnMenuRestore)
EVT_MENU(PU_EXIT,    CTrayIcon::OnMenuExit)
END_EVENT_TABLE()

void CTrayIcon::setParent(CMainInterface* _parent)
{
	m_Parent = _parent;
}


void CTrayIcon::OnMenuRestore(wxCommandEvent& )
{
	m_Parent->Show(true);
}


void CTrayIcon::OnMenuExit(wxCommandEvent& )
{
	m_Parent->Close(true);
}


// Overridables
wxMenu *CTrayIcon::CreatePopupMenu()
{
	wxMenu *menu = new wxMenu;
	menu->Append(PU_RESTORE, _T(NAME));
	#ifndef __WXMAC_OSX__		 /*Mac has built-in quit menu*/
	menu->AppendSeparator();
	menu->Append(PU_EXIT, wxString(i8n("E&xit"), wxConvUTF8));
	#endif
	return menu;
}


void CTrayIcon::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
	m_Parent->Show(true);
}


/* vi:set ts=4: */
