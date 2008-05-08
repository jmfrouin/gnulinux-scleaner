/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.fr
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
#include <engine/settings_manager.h>
#include <wx/config.h>
#include <wx/spinbutt.h>
#include "preferences.h"

#include <wx/imaglist.h>
#include <gfx/plugin.xpm>
#include <gfx/preferences.xpm>

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
        EVT_BUTTON(wxOK, CPreferences::OnApply)
        EVT_BUTTON(wxCANCEL, CPreferences::OnCancel)
    END_EVENT_TABLE()


    /*!
     * CPreferences constructors
     */
    CPreferences::CPreferences():
    fSplashScreen(0), fToolbar(0), fStatusbar(0), fDelete(0)
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
        fEngine = Engine::CEngine::Instance();
        fSettings = Engine::CSettingsManager::Instance();
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
        wxListbook* PrefListbook = new wxListbook(l_MainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
        l_Sizer0->Add(PrefListbook, 1, wxGROW | wxALL, 5);

        wxBoxSizer* l_ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
        l_ButtonSizer->Add(new wxButton(l_MainPanel, wxOK, _T("Apply")), 1, wxGROW | wxALL, 2);
        l_ButtonSizer->Add(new wxButton(l_MainPanel, wxCANCEL, _T("Cancel")), 1, wxGROW | wxALL, 2);

        l_Sizer0->Add(l_ButtonSizer, 0, wxGROW | wxALL, 1);


        wxPanel* PluginsPanel = new wxPanel(PrefListbook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

        wxBoxSizer* l_Sizer = new wxBoxSizer(wxVERTICAL);
        PluginsPanel->SetSizer(l_Sizer);

        wxStaticText* l_Title = new wxStaticText(PluginsPanel, wxID_ANY, wxString(i8n("Plugin default selection : "), wxConvUTF8));
        l_Sizer->Add(l_Title, 1, wxGROW | wxALL, 5);

        std::map<std::string, Plugins::IInPlugin*>::iterator l_it;
        for(l_it = fEngine->GetAvailableInputPlugs()->begin(); l_it != fEngine->GetAvailableInputPlugs()->end(); ++l_it)
        {
            wxCheckBox* l_PluginCB = new wxCheckBox(PluginsPanel, wxID_ANY, wxString(l_it->first.c_str(), wxConvUTF8) + wxString(i8n(" default selection"), wxConvUTF8));
            l_PluginCB->SetValue(l_it->second->GetDefaultSelection());
            l_Sizer->Add(l_PluginCB, 1, wxGROW | wxALL, 5);
        }

        wxPanel* PrefPanel = new wxPanel(PrefListbook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

        wxBoxSizer* l_Sizer2 = new wxBoxSizer(wxVERTICAL);
        PrefPanel->SetSizer(l_Sizer2);

        //Duplicate file method : Not fully implemented !
        //wxArrayString itemRadioBox3Strings;
        //itemRadioBox3Strings.Add(_("&CRC32"));
        //itemRadioBox3Strings.Add(_("&MD5"));
        //wxRadioBox* itemRadioBox3 = new wxRadioBox(PrefPanel, ID_RADIOBOX2, _("Duplicates files method"), wxDefaultPosition, wxDefaultSize, itemRadioBox3Strings, 1, wxRA_SPECIFY_ROWS );
        //itemRadioBox3->SetSelection(0);
        //l_Sizer2->Add(itemRadioBox3, 1, wxGROW | wxALL, 5);

        //Show splashscreen ?
        fSplashScreen = new wxCheckBox(PrefPanel, wxID_ANY, _T("Show splash screen on startup"), wxDefaultPosition);
        fSplashScreen->SetValue(fSettings->GetShowSplash());
        l_Sizer2->Add(fSplashScreen, 1, wxGROW | wxALL, 5);

        //Show toolbar ?
        fToolbar = new wxCheckBox(PrefPanel, wxID_ANY, _T("Show toolbar (need reboot)"), wxDefaultPosition);
        fToolbar->SetValue(fSettings->GetShowToolbar());
        l_Sizer2->Add(fToolbar, 1, wxGROW | wxALL, 5);

        //Show statusbar ?
        fStatusbar = new wxCheckBox(PrefPanel, wxID_ANY, _T("Show status bar (need reboot)"), wxDefaultPosition);
        fStatusbar->SetValue(fSettings->GetShowStatusbar());
        l_Sizer2->Add(fStatusbar, 1, wxGROW | wxALL, 5);

        //Progress bar refresh's delay
        /*wxSpinButton* l_PBDelay = new wxSpinButton(PrefPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL, _T("Progress bar update's delay"));
        l_Sizer2->Add(l_PBDelay, 1, wxGROW | wxALL, 5);*/

        //Delete file after output plugin ?
        fDelete = new wxCheckBox(PrefPanel, wxID_ANY, _T("Delete files after applying the output plugin"), wxDefaultPosition);
        fStatusbar->SetValue(fSettings->GetDelete());
        l_Sizer2->Add(fDelete, 1, wxGROW | wxALL, 5);

        //Append pages, by alphabetical order:
        //Add image :
        int NbImages;

        wxImageList* ImageList = new wxImageList(32, 32);
        PrefListbook->AssignImageList(ImageList);
        ImageList->Add(wxIcon(preferences_xpm));
        ImageList->Add(wxIcon(plugin_xpm));

        if(PrefListbook->GetImageList())
        {
            NbImages = PrefListbook->GetImageList()->GetImageCount();
            if(NbImages)
                std::cout << "I found " << NbImages << " images.\n";
                //GetPageCount() % nImages;
        }
        else
            std::cout << "I foundn't any images.\n";

        PrefListbook->AddPage(PrefPanel, _T("Application"), false, 0);
        PrefListbook->AddPage(PluginsPanel, _T("Plugins"), false, 1);
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

    void CPreferences::OnCancel(wxCommandEvent& WXUNUSED(event))
    {
        Close(true);
    }

    void CPreferences::OnApply(wxCommandEvent& WXUNUSED(event))
    {
        fSettings->SetShowSplash(fSplashScreen->GetValue());
        fSettings->SetShowToolbar(fToolbar->GetValue());
        fSettings->SetShowStatusbar(fStatusbar->GetValue());
        fSettings->SetDelete(fDelete->GetValue());
        Close(true);
    }
}
