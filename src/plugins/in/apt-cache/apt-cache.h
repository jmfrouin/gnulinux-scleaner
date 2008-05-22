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

/*! @page page3 Plugins documentations.
 * - @subpage apt_cache
 */

/*! @page apt_cache apt_cache: input plugin.
 * @section desc Description
 * This plugin allow user to remove all <b>apt_cache</b> unused, automatically installed on system.
 * <br>
 * @section param Parameters
 * @section pb Knows bugs
 * @section todo Todo
 */

#ifndef __APT_CACHE_H__
#define __APT_CACHE_H__

#include <config.h>
#include <plugins/in_plugin.h>

/*!
 *@brief Find unused apt_cache.
 */
class Capt_cachePlugin : public Plugins::IInPlugin
{
    public:
        Capt_cachePlugin();
        ~Capt_cachePlugin();

        bool GrabNullFile()
        {
            return false;
        }

        bool GetDefaultSelection()
        {
            return true;
        }

        /*!
         *@brief From IInPlugin
         */
        void GetDirectory(std::string& path);
        void ProcessFile(const std::string& filename);

        /*!
         *@brief From IPlugin
         */
        EType Type() { return eRootByFolderInput; }
        std::string Description();
};
#endif                           //__APT_CACHE_H__
/* vi:set ts=4: */
