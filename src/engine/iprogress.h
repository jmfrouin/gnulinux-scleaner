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

#ifndef __IPROGRESS_H__
#define __IPROGRESS_H__

#include <string>

/**
 * @brief Plugin Interface
 * @version 29.03.2008
 * @author Jean-Michel Frouin (jmfrouin@gmail.com)
 */
class IProgressbar
{
    public:
        /*!
         *@brief Update process progress bar callback.
         *@param pulse Put it in indeterminate state.
         *@param nb Update number.
         *@return true on continue, false on stop
         */
        virtual bool UpdateProgress(const std::string& mess, bool pulse, int nb = 0) = 0;
};
#endif                           //_IPROGRESS_H_
/* vi:set ts=4: */
