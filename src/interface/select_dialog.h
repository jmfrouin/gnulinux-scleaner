/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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

#ifndef __SELECT_DIALOG_H__
#define __SELECT_DIALOG_H__

#include <list>
#include <string>
#include <wx/frame.h>

class wxCheckListBox;
class wxPanel;

namespace GUI
{
        /*!
        *@brief Dialog to select input plugins.
        */
        class CSelectDialog : public wxFrame
        {
                public:
                        /*!
                        *@brief Constructor
                        *@param _title The dialog box title.
                        *@param _pluginList Available plugin list.
                        */
                        CSelectDialog(const wxString& _title, std::list<std::string>& _pluginList);

                        /*!
                        *@brief Destructor
                        */
                        virtual ~CSelectDialog();

                        //Callbacks
                        void OnListbox(wxCommandEvent& event);

                protected:
                wxCheckListBox* m_Input;
                        wxPanel*                m_Panel;

            DECLARE_EVENT_TABLE()
        };
}
#endif// __SELECT_DIALOG_H__
