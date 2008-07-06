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
 * - @subpage orphan
 */

/*! @page orphan orphan: input plugin.
 * @section desc Description
 * <=> sudo dpkg --purge $(COLUMNS=200 dpkg -l | grep "^rc" | tr -s ' ' | cut -d ' ' -f 2)
 * @section pb Knows bugs
 * Didn't work yet
 */

#ifndef __ORPHAN_H__
#define __ORPHAN_H__

#include <config.h>
#include <plugins/in/thread_plugin.h>

/*!
 *@brief Thread plugin.
 *
 * This plugin will find / delete orphan folder from "/home/user/.application".
 */
class CorphanPlugin : public Plugins::IThreadPlugin
{
  public:
    CorphanPlugin();
    ~CorphanPlugin();

    /*!
     *@brief From IThreadablePlugin
     */
    virtual bool GetDefaultSelection() { return true; }
    EType Type() { return eRootThreadableInput; }
    std::string Description();
    virtual void Run();
};
#endif                           //__ORPHAN_H__
/* vi:set ts=4: */
