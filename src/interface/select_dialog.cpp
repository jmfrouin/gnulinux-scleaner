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

#include "select_dialog.h"
#include <iostream>
#include <wx/checklst.h>
#include <wx/panel.h>

namespace GUI
{
	BEGIN_EVENT_TABLE(CSelectDialog, wxFrame)
	    EVT_LISTBOX(wxID_ANY, CSelectDialog::OnListbox)
	END_EVENT_TABLE()
	
	CSelectDialog::CSelectDialog(const wxString& _title, std::list<std::string>& _pluginList)
	: wxFrame(NULL, wxID_ANY, _title, wxPoint(100, 100)),
	m_Input(0), m_Panel(0)
	{
	    m_Panel = new wxPanel(this, wxID_ANY);
	    m_Input = new wxCheckListBox(m_Panel, wxID_ANY);
		std::list<std::string>::iterator l_it;
	
		//for(l_it = _pluginList.begin(); l_it != _pluginList.end(); ++l_it)
		//{
		//	std::cout << "Plugin : " << (*l_it) << '\n';
	    //	m_Input->Append(wxString((*l_it).c_str(), wxConvUTF8));
		//}
	}
	
	CSelectDialog::~CSelectDialog()
	{
	    delete m_Input;
	}
	
	//Callbacks
	void CSelectDialog::OnListbox(wxCommandEvent& event)
	{
		event.Skip();
	}
}
