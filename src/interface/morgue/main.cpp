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

#include <config.h>
#include <string>
#include <plugins/plugin_manager.h>
#include <plugins/plugin.h>
#include "main.h"

#include <gfx/empty.xpm>
#include <gfx/full.xpm>
#include <gfx/smile.xpm>

BEGIN_EVENT_TABLE(CMainDialog, wxDialog)
EVT_BUTTON(wxID_OK, CMainDialog::OnOK)
EVT_BUTTON(wxID_EXIT, CMainDialog::OnExit)
EVT_CLOSE(CMainDialog::OnCloseWindow)
EVT_LISTBOX(ID_CHECKLISTBOX1, CMainDialog::OnChecklistboxSelected)
END_EVENT_TABLE()

CMainDialog::CMainDialog(wxWindow* parent, const wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, const long windowStyle):
wxDialog(parent, id, title, pos, size, windowStyle),
m_PluginsList(0)
{
  Init();
}


CMainDialog::~CMainDialog()
{
  delete m_Icon;
  #if defined(__WXCOCOA__)
  delete m_DockIcon;
  #endif
}


void CMainDialog::OnOK(wxCommandEvent& WXUNUSED(event))
{
  std::cout << "###" << (*m_PluginsList)["dpkg"]->getName() << '\n';
  Show(false);
}


void CMainDialog::OnExit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}


void CMainDialog::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
  Destroy();
}


void CMainDialog::Init(void)
{
  //Initialisation
  m_PluginsList = CPluginManager::Instance()->getPluginsListPtr();
  if(m_PluginsList == 0)
  {
    return;
  }

  ////@begin test content construction
  CMainDialog* itemDialog1 = this;

  this->SetBackgroundColour(wxColour(173, 216, 230));
  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
  itemDialog1->SetSizer(itemBoxSizer2);

  wxSplitterWindow* itemSplitterWindow3 = new wxSplitterWindow( itemDialog1, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(100, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
  itemSplitterWindow3->SetMinimumPaneSize(0);

  wxArrayString itemCheckListBox4Strings;
  std::map<std::string, IPlugin*>::iterator _it;
  for(_it = m_PluginsList->begin(); _it != m_PluginsList->end(); ++_it)
  {
    itemCheckListBox4Strings.Add(_(((*_it).second)->getName().c_str()));
  }

  wxCheckListBox* itemCheckListBox4 = new wxCheckListBox( itemSplitterWindow3, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, itemCheckListBox4Strings, wxLB_SINGLE );

  wxPanel* itemPanel5 = new wxPanel( itemSplitterWindow3, ID_PREFERENCES_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

  wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
  itemPanel5->SetSizer(itemBoxSizer7);

  m_Title = new wxStaticText( itemPanel5, wxID_STATIC, _("Title"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer7->Add(m_Title, 0, wxALIGN_LEFT|wxALL, 5);

  wxStaticLine* itemStaticLine6 = new wxStaticLine( itemPanel5, ID_STATICLINE, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
  itemBoxSizer7->Add(itemStaticLine6, 0, wxALIGN_LEFT|wxALL, 5);

  m_Description = new wxStaticText( itemPanel5, wxID_STATIC, _("Description"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer7->Add(m_Description, 0, wxALIGN_LEFT|wxALL, 5);

  itemSplitterWindow3->SplitVertically(itemCheckListBox4, itemPanel5, 50);
  itemBoxSizer2->Add(itemSplitterWindow3, 0, wxGROW|wxALL, 5);

  wxStdDialogButtonSizer* itemStdDialogButtonSizer12 = new wxStdDialogButtonSizer;

  itemBoxSizer2->Add(itemStdDialogButtonSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
  wxButton* itemButton13 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer12->AddButton(itemButton13);

  wxButton* itemButton14 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer12->AddButton(itemButton14);

  itemStdDialogButtonSizer12->Realize();
  ////@end test content construction

  //Tray icon !!
  m_Icon = new CTrayIcon();
  #if defined(__WXCOCOA__)
  m_DockIcon = new CTrayIcon(wxTaskBarIcon::DOCK);
  #endif

  m_Icon->setParent(this);

  if (!m_Icon->SetIcon(full_xpm, wxT(NAME)))
  {
    std::cout << "Could not set icon.";
  }
}


void CMainDialog::OnChecklistboxSelected(wxCommandEvent& event)
{
  //Fill title :
  std::string l_plugname = event.GetString().c_str();
  std::string l_title("Name : ");
  l_title += (*m_PluginsList)[l_plugname]->getName();
  m_Title->SetLabel(l_title);
  std::string l_description;
  l_description = (*m_PluginsList)[l_plugname]->description();
  m_Description->SetLabel(l_description);
}


/* vi:set ts=4: */
