/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.org
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

#ifndef __PREFERENCES_H__
#define __PREFERENCES_H__

#include <def.h>

#include <wx/listbook.h>
#include <tools/smart_pointer.h>

namespace Engine
{
  class CEngine;
  class CSettingsManager;
}


class wxCheckBox;

namespace GUI
{
  /*!
   *@brief CPreferences class declaration
   * @version 15.11.2007
   * @author Jean-Michel Frouin (jmfrouin@gmail.com)
   */
  class CPreferences: public wxDialog
  {
    DECLARE_DYNAMIC_CLASS( CPreferences )
      DECLARE_EVENT_TABLE()

      public:
      /// Constructors
      CPreferences();
      CPreferences( wxWindow* parent, wxWindowID id = ID_PREFERENCES, const wxString& caption = SYMBOL_PREFERENCES_TITLE, const wxPoint& pos = SYMBOL_POSITION, const wxSize& size = SYMBOL_DIALOG_SIZE, long style = SYMBOL_INTERFACE_STYLE );

      /// Creation
      bool Create( wxWindow* parent, wxWindowID id = ID_PREFERENCES, const wxString& caption = SYMBOL_PREFERENCES_TITLE, const wxPoint& pos = SYMBOL_POSITION, const wxSize& size = SYMBOL_DIALOG_SIZE, long style = SYMBOL_DIALOG_STYLE );

      /// Destructor
      ~CPreferences();

      /// Initialises member variables
      void Init();

      /// Creates the controls and sizers
      void CreateControls();

      /// Retrieves bitmap resources
      wxBitmap GetBitmapResource( const wxString& name );

      /// Retrieves icon resources
      wxIcon GetIconResource( const wxString& name );

      /// Should we show tooltips?
      static bool ShowToolTips();

      /// User click Cancel button
      void OnCancel(wxCommandEvent& WXUNUSED(event));

      /// User click Apply button
      void OnApply(wxCommandEvent& WXUNUSED(event));

      /// User click on 'Delete' button
      void OnDelete(wxCommandEvent& WXUNUSED(event));

    private:
      //Engine
      Tools::TSmartPtr<Engine::CEngine>               fEngine;

      //Settings manager
      Tools::TSmartPtr<Engine::CSettingsManager>      fSettings;

      //Preferences
      wxCheckBox*     fSplashScreen;
      wxCheckBox*     fToolbar;
      wxCheckBox*     fStatusbar;
      wxCheckBox*     fDelete;
      wxCheckBox*     fSystemFiles;
  };
}
#endif                           // __PREFERENCES_H__
