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

#ifndef __STRING_H__
#define __STRING_H__

#include <config.h>
#include <string>

namespace Tools
{
    /**
     * @brief In order to enhance std::string.
     */
    class CString : public std::string
    {
        public:
            /*!
             *@brief Default constructor.
             */
            CString():
            std::string()
            {
            }

            /*!
             *@brief Destructor.
             */
            virtual ~CString();

            /*!
            *@brief lowercase string.
            */
            void ToLower()
            {
                for(int i=Length(); --i>=0; )
                {
                    if(this->at(i) >= 0x41 && this->at(i) <= 0x5A)
                    {
                        this->at(i) = this->at(i) + 0x20;
                    }
                }
            }
    };
}
#endif                           //_STRING_H_
/* vi:set ts=4: */
