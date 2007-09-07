/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
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
$Date$
$Rev$
$Author$
------------------------------------------------------

*/

/*
 * @brief :      Commons definition file
 * @author :     Jean-Michel Frouin
 * @date :       09/01/2007
 */

#ifndef _DEF_H_
#define _DEF_H_

//Bash Colors
#define VERT "\e[0;32m"
#define ROUGE "\e[0;31m"
#define BLEU "\e[0;34m"
#define VIOLET "\e[0;35m"
#define CYAN "\e[0;36m"
#define STOP "\e[0m"

//General app infos
#define MAJOR 0
#define MINOR 30
#define BUG 0
#define t(u) #u
#define VERSION(M,m,b) t(M) "." t(m) "." t(b)
#define VER VERSION(MAJOR,MINOR,BUG)
#define NAME "scleaner v"VER
#define SPLASH true

////@begin control identifiers
#define ID_TEST 10000
#define ID_BUTTON1 10001
#define ID_BUTTON2 10002
#define ID_CHECKLISTBOX1 10003
#define ID_BUTTON3 10004
#define ID_SPLITTERWINDOW1 10005
#define ID_PANEL1 10006
#define ID_STATICLINE 10007
#define SYMBOL_TEST_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_TEST_TITLE _("test")
#define SYMBOL_TEST_IDNAME ID_TEST
#define SYMBOL_TEST_SIZE wxSize(400, 300)
#define SYMBOL_TEST_POSITION wxDefaultPosition
#define ID_MAININTERFACE 10000
#define ID_TOOLBAR1 10002
#define ID_PROCESS 10003
#define ID_STOP 10004
#define ID_TOOL3 10005
#define ID_TOOL4 10006
#define ID_SPLITTERWINDOW1 10007
#define ID_STATUSBAR1 10008
#define ID_TREECTRL1 10009
#define ID_CHECKLISTBOX1 10010
#define ID_SPLITTERWINDOW2 10011
#define ID_TITLE 10012

//Menu ID
#define ID_ABOUT 10013
#define ID_TOOLBAR 10014

#define SYMBOL_MAININTERFACE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_MAININTERFACE_TITLE _("MainInterface")
#define SYMBOL_MAININTERFACE_IDNAME ID_MAININTERFACE
#define SYMBOL_MAININTERFACE_SIZE wxSize(800, 480)
#define SYMBOL_MAININTERFACE_POSITION wxDefaultPosition

#define SYMBOL_MAININTERFACE_SASH1_POS 400
#define SYMBOL_MAININTERFACE_SASH2_POS 100
#define TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT

//Useful macro
#define ___(X) gettext(X)

#endif                           // _DEF_H_
/* vi:set ts=4: */
