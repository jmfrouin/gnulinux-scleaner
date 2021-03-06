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
 * - @subpage logs
 */

/*! @page logs logs: Find logs files locate in /var/log
 * @section desc Description
 */

#ifndef __LOGS_H__
#define __LOGS_H__

#include <config.h>
#include <plugins/in/input_plugin.h>

class ClogsPlugin : public Plugins::IInputPlugin
{
  public:
    ClogsPlugin();
    ~ClogsPlugin();

    bool GrabNullFile()
    {
      return false;
    }

    bool GetDefaultSelection()
    {
      return false;
    }

    /*!
     *@brief From IInPlugin
     */
    void ProcessFile(const std::string& filename);
    void GetDirectory(std::string& path);

    /*!
     *@brief From IPlugin
     */
    EType Type() { return eRootInput; }
    std::string Description();
};
#endif                           //__LOGS_H__
/* vi:set ts=4: */
