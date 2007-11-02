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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <iostream>
#include <engine/engine.h>
#include <wx/config.h>
#include "preferences.h"

//6.3 Load/save of preferences
//
//Preferences are usually stored with in the registry (Windows) or config file (Linux, etc.). wxWidgets supports this through wxConfig choosing the platform specific solution itself. Be carefully when keeping the preferences open over a longer time period. For safety reasons keep this period as small as possible.
//
//One might use wxFileConfig instead to force the use of config file even on Windows. The default location of the config file is based on the $HOME variable on Linux, etc. and $HOMEDRIVE + HOMEPATH on Windows. The file will only be written back to disk when the config objected is deleted or the Flush() method is called.
//Sample code
//
//#include <wx/config.h>   // configuration support
//
//const wxString PAGE_COMMON = _T("Common");
//...
//const wxString NOSPLASH = _T("NoSplashScreen");
//const wxString SHOWTOOLBAR = _T("ShowToolbar");
//const wxString SHOWSTATUSBAR = _T("ShowStatusbar");
//const wxString USEPAGES = _T("UsePages");
//
//CommonPrefs g_CommonPrefs = {
//    // application prefs
//    false, // noSplash
//    true,  // showToolbar
//    true,  // showStatusbar
//    false, // usePages
//};
//...
//
//void PreferenceDlg::LoadValuesPageCommon () {
//    wxString key = PAGE_COMMON;
//    key.Append (_T("/"));
//
//    // common prefs
//    wxConfig *cfg = new wxConfig (wxTheApp->GetAppName());
//    cfg->Read (key + NOSPLASH, &g_CommonPrefs.noSplash);
//    cfg->Read (key + SHOWTOOLBAR, &g_CommonPrefs.showToolbar);
//    cfg->Read (key + SHOWSTATUSBAR, &g_CommonPrefs.showStatusbar);
//    cfg->Read (key + USEPAGES, &g_CommonPrefs.usePages);
//    delete cfg;
//}
//
//void PreferenceDlg::SaveValuesPageCommon () {
//    wxString key = PAGE_COMMON;
//    key.Append (_T("/"));
//
//    // common prefs
//    wxConfig *cfg = new wxConfig (wxTheApp->GetAppName());
//    cfg->Write (key + NOSPLASH, g_CommonPrefs.noSplash);
//    cfg->Write (key + SHOWTOOLBAR, g_CommonPrefs.showToolbar);
//    cfg->Write (key + SHOWSTATUSBAR, g_CommonPrefs.showStatusbar);
//    cfg->Write (key + USEPAGES, g_CommonPrefs.usePages);
//    delete cfg;
//}



namespace GUI
{
	/*!
	 * CPreferences type definition
	 */
	IMPLEMENT_DYNAMIC_CLASS( CPreferences, wxDialog )
	
	
	/*!
	 * CPreferences event table definition
	 */
	
	BEGIN_EVENT_TABLE( CPreferences, wxDialog )
	END_EVENT_TABLE()
	
	
	/*!
	 * CPreferences constructors
	 */
	CPreferences::CPreferences()
	{
	    Init();
	}
	
	CPreferences::CPreferences( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
	{
	    Init();
	    Create(parent, id, caption, pos, size, style);
	}
	
	
	/*!
	 * CPreferences creator
	 */
	
	bool CPreferences::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
	{
	    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
	    wxDialog::Create( parent, id, caption, pos, size, style );
	
	    CreateControls();
	    if (GetSizer())
	    {
	        GetSizer()->SetSizeHints(this);
	    }
	    Centre();
	    return true;
	}
	
	
	/*!
	 * CPreferences destructor
	 */
	CPreferences::~CPreferences()
	{
	}
	
	
	/*!
	 * Member initialisation
	 */
	void CPreferences::Init()
	{
		m_Engine = Engine::CEngine::Instance();
	}
	
	
	/*!
	 * Control creation for CPreferences
	 */
	void CPreferences::CreateControls()
	{    
    	wxPanel* l_MainPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

	    wxBoxSizer* l_Sizer0 = new wxBoxSizer(wxVERTICAL);
	    l_MainPanel->SetSizer(l_Sizer0);

		//Preferences ListBook
		//FIXME : Need to add bitmap
    	wxListbook* l_PrefListbook = new wxListbook(l_MainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
		l_Sizer0->Add(l_PrefListbook, 1, wxGROW | wxALL, 5);

		wxBoxSizer* l_ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
		l_ButtonSizer->Add(new wxButton(l_MainPanel, wxID_ANY, _T("Apply")), 1, wxGROW | wxALL, 2);
		l_ButtonSizer->Add(new wxButton(l_MainPanel, wxID_ANY, _T("Cancel")), 1, wxGROW | wxALL, 2);

		l_Sizer0->Add(l_ButtonSizer, 0, wxGROW | wxALL, 1);


    	wxPanel* l_PluginsPanel = new wxPanel(l_PrefListbook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

	    wxBoxSizer* l_Sizer = new wxBoxSizer(wxVERTICAL);
	    l_PluginsPanel->SetSizer(l_Sizer);
	
		std::map<std::string, Plugins::IInPlugin*>::iterator l_it;
		for(l_it = m_Engine->getAvailableInputPlugs()->begin(); l_it != m_Engine->getAvailableInputPlugs()->end(); ++l_it)
		{
	    	wxArrayString l_Choice;
			l_Choice.Add(wxString(i8n("Yes"), wxConvUTF8));
			l_Choice.Add(wxString(i8n("No"), wxConvUTF8));
			wxRadioBox* l_PluginRadio = new wxRadioBox(l_PluginsPanel, wxID_ANY, wxString(l_it->first.c_str(), wxConvUTF8) + wxString(i8n(" default selection"), wxConvUTF8), wxDefaultPosition, wxDefaultSize, l_Choice, 1, wxRA_SPECIFY_ROWS);
			l_PluginRadio->SetSelection(l_it->second->getDefaultSelection());
			l_Sizer->Add(l_PluginRadio, 1, wxGROW | wxALL, 5);
		}

    	l_PrefListbook->AddPage(l_PluginsPanel, _("Plugins"));

    	wxPanel* l_PrefPanel = new wxPanel(l_PrefListbook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

	    wxBoxSizer* l_Sizer2 = new wxBoxSizer(wxVERTICAL);
	    l_PrefPanel->SetSizer(l_Sizer2);

		//Duplicate file method.
	    wxArrayString itemRadioBox3Strings;
	    itemRadioBox3Strings.Add(_("&CRC32"));
	    itemRadioBox3Strings.Add(_("&MD5"));
	    wxRadioBox* itemRadioBox3 = new wxRadioBox(l_PrefPanel, ID_RADIOBOX2, _("Duplicates files method"), wxDefaultPosition, wxDefaultSize, itemRadioBox3Strings, 1, wxRA_SPECIFY_ROWS );
	    itemRadioBox3->SetSelection(0);
	    l_Sizer2->Add(itemRadioBox3, 1, wxGROW | wxALL, 5);

		//Show splashscreen ?
		wxCheckBox* l_Splashscreen = new wxCheckBox(l_PrefPanel, wxID_ANY, _T("Show splash screen on startup"), wxDefaultPosition);
	    l_Sizer2->Add(l_Splashscreen, 1, wxGROW | wxALL, 5);

		//Show toolbar ?
		wxCheckBox* l_Toolbar = new wxCheckBox(l_PrefPanel, wxID_ANY, _T("Show toolbar"), wxDefaultPosition);
	    l_Sizer2->Add(l_Toolbar, 1, wxGROW | wxALL, 5);

		//Show statusbar ?
		wxCheckBox* l_Statusbar = new wxCheckBox(l_PrefPanel, wxID_ANY, _T("Show status bar"), wxDefaultPosition);
	    l_Sizer2->Add(l_Statusbar, 1, wxGROW | wxALL, 5);

    	l_PrefListbook->AddPage(l_PrefPanel, _("Application"));
	}
	
	
	
	/*!
	 * Should we show tooltips?
	 */
	bool CPreferences::ShowToolTips()
	{
	    return true;
	}
	
	/*!
	 * Get bitmap resources
	 */
	wxBitmap CPreferences::GetBitmapResource( const wxString& name )
	{
	    // Bitmap retrieval
	    wxUnusedVar(name);
	    return wxNullBitmap;
	}
	
	/*!
	 * Get icon resources
	 */
	wxIcon CPreferences::GetIconResource( const wxString& name )
	{
	    // Icon retrieval
	    wxUnusedVar(name);
	    return wxNullIcon;
	}
}
