#include "select_dialog.h"
#include <iostream>
#include <wx/checklst.h>
#include <wx/panel.h>

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
