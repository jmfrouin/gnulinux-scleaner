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

/*
 *@brief :      Commons definition file
 *@version 08.06.2008
 *@author Jean-Michel Frouin (jmfrouin@gmail.com)
 */
#ifndef __DEF_H__
#define __DEF_H__

#define BUILD 1003

//For i8n
#include <libintl.h>
#include <locale.h>

//Bash Colors
#define VERT "\e[0;32m"
#define ROUGE "\e[0;31m"
#define BLEU "\e[0;34m"
#define VIOLET "\e[0;35m"
#define CYAN "\e[0;36m"
#define STOP "\e[0m"

//Useful macros
#define t(u) #u
#define VERSION(M,m,B) t(M) "." t(m) "." t(B)
#define VER VERSION(MAJOR,MINOR,BUILD)
#define i8n(X) gettext(X)
#define ROUND(x) ((x-(int)x>0)?(int)x+1:(int)x) //Mainly wrote for formatSize
//CRC32 stuff
#define CRC_POLY_REV 0xEDB10050

//General app infos
#define MAJOR 0
#define MINOR 70
#define NAME "scleaner RC1 v"VER
#define VERSION_MEMORY_MANAGER 0.3
#define VERSION_FILELOG 0.2

//Paths
#define PLUG_FOLDER "/usr/share/scleaner/plugs"
#define CPUINFO "/proc/cpuinfo"
#define MEMINFO "/proc/meminfo"
#define LOGFILE "/tmp/scleaner.log"
#define LEAKFILE "/tmp/scleaner_leaks.log"
#define CONFFILE "/.scleaner/prefs.conf"
#define FSTAB "/etc/fstab"

//Controls identifiers
//Main interface
#define ID_MAININTERFACE 10000
#define ID_MAININTERFACE_AUI 10001
#define ID_MAININTERFACE_NOTEBOOK 10002
#define ID_MAININTERFACE_TOOLBAR 10003
#define ID_MAININTERFACE_STATUSBAR 10004
#define ID_MAININTERFACE_PROCESS 10005
#define ID_SELECT 10006

//System infos
#define SYMBOL_SYSTEMINFOS_TITLE _("System Infos")
#define ID_SYSTEMINFOS 10010

//Review your choice
#define SYMBOL_REVIEW_TITLE _("Review")
#define ID_REVIEW 10020
#define ID_REVIEW_LISTCTRL 10021

//Preferences
#define SYMBOL_PREFERENCES_TITLE _("Preferences")
#define ID_PREFERENCES 10030
#define ID_PREFERENCES_PANEL 10031
#define ID_PREFERENCES_DELETE 10032
#define ID_PREFERENCES_RADIOBOX 10033
#define ID_PREFERENCES_SYSTEM_FILES 10034
#define ID_PREFERENCES_RECURSIVE_SCAN 10035

//Checklists
#define ID_RESCHECKLIST 10040
#define ID_CHECKLIST_SELECT_ALL 10041
#define ID_CHECKLIST_UNSELECT_ALL 10042
#define ID_CHECKLIST_SELECT_FROM_SAME_FOLDER 10043
#define ID_CHECKLIST_UNSELECT_FROM_SAME_FOLDER 10044
#define ID_CHECKLIST_INVERT_SELECTION 10045

//Menu
#define ID_MENU_ABOUT 10050
#define ID_MENU_SCAN 10051
#define ID_MENU_PREFS 10052
#define ID_MENU_SYSTEM_INFOS 10053

//Buttons
#define ID_BUTTON_FOLDER_INC_ADD 10060
#define ID_BUTTON_FOLDER_INC_DEL 10061
#define ID_BUTTON_FOLDER_EX_ADD 10062
#define ID_BUTTON_FOLDER_EX_DEL 10063

//Style
#define SYMBOL_INTERFACE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_DIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxMAXIMIZE_BOX
#define SYMBOL_TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT

//Size
#define SYMBOL_INTERFACE_SIZE wxSize(1024, 768)
#define SYMBOL_DIALOG_SIZE wxSize(400, 300)

//Position
#define SYMBOL_POSITION wxDefaultPosition
#define SYMBOL_SASH_POS 400
#endif                           // __DEF_H__
/* vi:set ts=4: */
