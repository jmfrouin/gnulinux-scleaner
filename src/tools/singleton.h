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


#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <leak/leak_detector.h>

namespace Tools
{
    /*!
     *@brief A singleton template.
     *@note Tips : A good idea is to use a CSmartPtr to grab Instance() to avoid memory leak.
     */
    template <class T>
    class TSingleton
    {
        public:
            /*!
             *@brief Singleton accessor.
             */
            static T* Instance()
            {
                T* Ret = fInst;

                if(!Ret)
                {
                    fInst = Ret = new T;
                }

                return Ret;
            }

        protected:
            /*!
             *@brief Default constructor
             *
             *Made constructor private to avoid problem.
             *
             *Nobody except itself can create it.
             */
            TSingleton()
            {
            }

            /*!
             *@brief Destructor
             *@note Made destructor private to avoid problem.
             *@note Nobody except itself can create it.
             */
            virtual ~TSingleton()
            {
            }

        private:
            static T*   fInst;      ///< The only single instance.
    };
} //namespace

template <class T>
T* Tools::TSingleton<T>::fInst = 0;
#endif                           //__SINGLETON_H__
/* vi:set ts=4: */
