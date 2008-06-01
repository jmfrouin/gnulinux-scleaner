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
 * - @subpage kernels
 */

/*! @page kernels kernels: input plugin.
 * @section desc Description
 * This plugin allow user to remove all <b>kernels</b> unused, automatically installed on system.
 * <br>
 * @section pb Knows bugs
 * Didn't check yet!
 */

#ifndef __KERNELS_H__
#define __KERNELS_H__

#include <config.h>
#include <plugins/in/thread_plugin.h>

class pkgCache;
class pkgSourceList;
class MMap;

/*!
 *@brief Find unused kernels.
 */
class CkernelsPlugin : public Plugins::IThreadPlugin
{
    public:
        CkernelsPlugin();
        ~CkernelsPlugin();

        bool GetDefaultSelection() { return true; }

        /*!
         *@brief From IThreadablePlugin
         */
        EType Type() { return eRootThreadableInput; }
        std::string Description();
        void GetFileList(std::list<std::string>& fl);
        virtual void Run();

     private:
        /*!
         *@brief Search for a package in cache.
         *@param name The package name.
         *@param result A string containing the first found package.
         */
        bool Search(const std::string& name, std::string& result);

    private:
        pkgCache*       fCache;
        pkgSourceList*  fSrcList;
        MMap*           fMap;
};
#endif                           //__KERNELS_H__
/* vi:set ts=4: */
