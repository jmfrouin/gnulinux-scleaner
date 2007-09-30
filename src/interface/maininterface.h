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

#ifndef _MAININTERFACE_H_
#define _MAININTERFACE_H_

#include <config.h>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <wx/frame.h>
#include <wx/toolbar.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <engine/iprogress.h>
#include <tools/smart_pointer.h>
#include "tray.h"

class IInPlugin;
class IOutPlugin;
class wxRadioBox;
class wxHtmlWindow;
class CEngine;
class wxProgressDialog;

/*!
 * CMainInterface class declaration
 */
class CMainInterface: public wxFrame, public IProgressbar
{
	DECLARE_CLASS( CMainInterface )
		DECLARE_EVENT_TABLE()

		public:
		/// Constructors
		CMainInterface();
		CMainInterface(wxWindow* parent, wxWindowID id = SYMBOL_MAININTERFACE_IDNAME, const wxString& caption = SYMBOL_MAININTERFACE_TITLE, const wxPoint& pos = SYMBOL_MAININTERFACE_POSITION, const wxSize& size = SYMBOL_MAININTERFACE_SIZE, long style = SYMBOL_MAININTERFACE_STYLE);

		bool Create(wxWindow* parent, wxWindowID id = SYMBOL_MAININTERFACE_IDNAME, const wxString& caption = SYMBOL_MAININTERFACE_TITLE, const wxPoint& pos = SYMBOL_MAININTERFACE_POSITION, const wxSize& size = SYMBOL_MAININTERFACE_SIZE, long style = SYMBOL_MAININTERFACE_STYLE );

		~CMainInterface();

		void Init();
		void CreateControls();
		wxBitmap GetBitmapResource( const wxString& name );
		wxIcon GetIconResource( const wxString& name );
		static bool ShowToolTips();

		//Callbacks
		//void OnSelChanged(wxTreeEvent& event);
		void OnAbout(wxCommandEvent& WXUNUSED(event));
		void OnQuit(wxCommandEvent& WXUNUSED(event));
		void OnProcess(wxCommandEvent& WXUNUSED(event));
		void OnScan(wxCommandEvent& WXUNUSED(event));
		void OnSelect(wxCommandEvent& WXUNUSED(event));
		void OnSelRadio(wxCommandEvent& event);
		void OnNotebook(wxNotebookEvent& event);

		/*!
		 *@brief Call splash screen
		 *@param _delay Delay, before splash will gone.
		 */
		void launchSplash(int _delay);

		/*!
		 *@brief Retrieve list of selected files to process.
		 *@param _fl Files list to fill.
		 */
		void GetSelectedFiles(std::list<std::string>& _fl);

		//From IProgressbar
		void updateProgress(const std::string& _mess, bool _pulse, int _nb);

	protected:
		CTrayIcon*  m_Icon;
	#if defined(__WXCOCOA__)
		CTrayIcon*  m_DockIcon;
	#endif
		//Input plugins
		std::map<std::string, IInPlugin*>*  m_InputPlugs;

		//Output plugins
		std::map<std::string, IOutPlugin*>* m_OutputPlugs;

		//Engine
		TSmartPtr<CEngine>                  m_Engine;

		//GUI tree list which display input plugins and file list.
		wxNotebook*                         m_Input;

		//Informations GUI panel
		wxHtmlWindow*                       m_Html;

		//GUI checkbox which display output plugins
		wxRadioBox*                         m_Output;
		wxStatusBar*                        m_StatusBar;
		wxSplitterWindow* 					m_Split;

		//Progress bar for process part.
		wxProgressDialog*                   m_Progress;

		//Total sizes
		std::vector<double>                 m_TotalSizes;
};
#endif
// _MAININTERFACE_H_
