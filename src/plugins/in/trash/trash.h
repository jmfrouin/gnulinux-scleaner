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

/*! @page page3 Plugins documentations.
 * - @subpage trash
 */

/*! @page trash trash: input plugin.
 * @section desc Description
 * This plugin allow user to clean his backup files : <b>*.bak, *~ or #*</b> nammed files.
 * <br>
 * In fact it just scan <b>/home/user/</b> and its subfolders.
 * @section param Parameters
 * @section pb Knows bugs
 * @todo Support both modes, simple user & root/sudo.
 */

#ifndef __TRASH_H__
#define __TRASH_H__

#include <config.h>
#include <plugins/in/thread_plugin.h>

class CtrashPlugin : public Plugins::IThreadPlugin
{
  public:
    CtrashPlugin();
    ~CtrashPlugin();

    bool GetDefaultSelection() { return true; }

    /*!
     *@brief From IPlugin
     */
    EType Type() { return eThreadableInput; }
    std::string Description();
    void GetFileList(std::list<std::string>& fl);
    virtual void Run();

};
#endif                           //__TRASH_H__
/* vi:set ts=4: */
