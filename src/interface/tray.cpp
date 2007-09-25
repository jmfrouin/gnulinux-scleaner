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
EVT_MENU(PU_NEW_ICON,CTrayIcon::OnMenuSetNewIcon)
EVT_MENU(PU_OLD_ICON,CTrayIcon::OnMenuSetOldIcon)
EVT_MENU(PU_CHECKMARK,CTrayIcon::OnMenuCheckmark)
EVT_UPDATE_UI(PU_CHECKMARK,CTrayIcon::OnMenuUICheckmark)
EVT_TASKBAR_LEFT_DCLICK  (CTrayIcon::OnLeftButtonDClick)
EVT_MENU(PU_SUB1, CTrayIcon::OnMenuSub)
EVT_MENU(PU_SUB2, CTrayIcon::OnMenuSub)
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


static bool check = true;

void CTrayIcon::OnMenuCheckmark(wxCommandEvent& )
{
	check =!check;
}


void CTrayIcon::OnMenuUICheckmark(wxUpdateUIEvent &event)
{
	event.Check( check );
}


void CTrayIcon::OnMenuSetNewIcon(wxCommandEvent&)
{
	//wxIcon icon(smile_xpm);

	//if (!SetIcon(icon, wxT("wxTaskBarIcon Sample - a different icon")))
	//wxMessageBox(wxT("Could not set new icon."));
}


void CTrayIcon::OnMenuSetOldIcon(wxCommandEvent&)
{
	//if (IsIconInstalled())
	//{
	//    RemoveIcon();
	//}
	//else
	//{
	//    wxMessageBox(wxT("wxTaskBarIcon Sample - icon already is the old version"));
	//}
}


void CTrayIcon::OnMenuSub(wxCommandEvent&)
{
	wxMessageBox(wxT("You clicked on a submenu!"));
}


// Overridables
wxMenu *CTrayIcon::CreatePopupMenu()
{
	// Try creating menus different ways
	// TODO: Probably try calling SetBitmap with some XPMs here
	wxMenu *menu = new wxMenu;
	menu->Append(PU_RESTORE, _T(NAME));
	menu->AppendSeparator();
	menu->Append(PU_OLD_ICON, _T("&Restore Old Icon"));
	menu->Append(PU_NEW_ICON, _T("&Set New Icon"));
	menu->AppendSeparator();
	menu->Append(PU_CHECKMARK, _T("Checkmark"),wxT(""), wxITEM_CHECK);
	menu->AppendSeparator();
	wxMenu *submenu = new wxMenu;
	submenu->Append(PU_SUB1, _T("One submenu"));
	submenu->AppendSeparator();
	submenu->Append(PU_SUB2, _T("Another submenu"));
	menu->Append(PU_SUBMAIN, _T("Submenu"), submenu);
	#ifndef __WXMAC_OSX__		 /*Mac has built-in quit menu*/
	menu->AppendSeparator();
	menu->Append(PU_EXIT,    _T("E&xit"));
	#endif
	return menu;
}


void CTrayIcon::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
	m_Parent->Show(true);
}


/* vi:set ts=4: */
