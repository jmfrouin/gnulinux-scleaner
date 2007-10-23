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

#ifndef _MAINDIALOG_H_
#define _MAINDIALOG_H_

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <config.h>
#include <map>
#include <wx/splitter.h>
#include <wx/statline.h>
#include <tools/smart_pointer.h>
#include "tray.h"

class IPlugin;

class CMainDialog: public wxDialog, public CSmartCpt
{
	public:
		CMainDialog(wxWindow* parent, const wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, const long windowStyle = wxDEFAULT_DIALOG_STYLE);
		~CMainDialog();

		void OnOK(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void OnCloseWindow(wxCloseEvent& event);
		void OnChecklistboxSelected(wxCommandEvent& event);
		void Init(void);

	protected:
		CTrayIcon*  m_Icon;
	#if defined(__WXCOCOA__)
		CTrayIcon*  m_DockIcon;
	#endif
		std::map<std::string, IPlugin*>*    m_PluginsList;
		wxStaticText*                       m_Title;
		wxStaticText*                       m_Description;

		DECLARE_EVENT_TABLE()
};
#endif							 // _MAINDIALOG_H_
/* vi:set ts=4: */
