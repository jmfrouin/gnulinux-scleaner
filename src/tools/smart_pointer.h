/**
 * This file is part of scleaner project.

 * Copyright (C) 2007-2008 FROUIN Jean-Michel

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


#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

#include <iostream>

#if defined LEAKS
#include <leak/leak_detector.h>
#endif

typedef unsigned int SmartCptType;

namespace Tools
{
    /*!
     * @brief Simple counter used by Smart pointer.
     */
    class CSmartCpt
    {
        public:
            /*!
             *@brief Default constructor
             */
            CSmartCpt(): fCounter(0) {}

            /*!
             *@brief Destructor
             */
            virtual ~CSmartCpt() {}

            /*!
             * @brief Increment counter.
             */
            SmartCptType _IncRef() { return ++fCounter; }

            /*!
             * @brief Decrement counter.
             */
            SmartCptType _DecRef() { return --fCounter; }
        private:
            SmartCpt fCounter;    ///< Reference counter.
    };

    /*!
     * @brief Pointer which can handle multireference.
     *
     * This smart pointer erase the object only when nobody use it anymore by maintaining a reference counter.
     *
     * Be careful : This implementation is written for SAPI project and is not yet fully implemented.
     *
     * For the moment, this smart pointer doesn't support array object.
     */
    template <class T>
    class TSmartPtr
    {
        public:
            /*!
             *@brief Default constructor.
             */
            TSmartPtr(): fObject(0) {}

            /*!
             *@brief Destructor.
             */
            ~TSmartPtr() { *this = 0; }

            /*!
             * @brief Simple pointer affectation.
             */
            TSmartPtr<T>& operator=(T* object)
            {
                if(object)
                {
                    object->_IncRef();
                }

                if(fObject)
                {
                    SmartCptType Cpt;
                    Cpt = fObject->_DecRef();
                    if(Cpt == 0)
                    {
                        delete fObject;
                    }
                }
                fObject = object;
                return *this;
            }

            /*!
             * @brief Smart pointer affectation.
             */
            TSmartPtr<T>& operator=(TSmartPtr<T>& object)
            {
                *this = object.fObject;
                return *this;
            }

            /*!
             *@brief In order to use it, as a dumb pointer.
             */
            operator T*()
            {
                return fObject;
            }

            bool operator==(const int& value) const
            {
                return ((int)this == value);
            }

            bool operator!=(const int& value) const
            {
                return ((int)this != value);
            }

            /*!
             *@brief Dereferencement operators for object.
             */
            T& operator*() { return *fObject; }

            /*!
             *@brief Dereferencement operators for pointer on object.
             */
            T* operator->() { return fObject; }

        private:
            T* fObject;             ///< Object handle by this pointer.
    };
} //namespace
#endif                           //__SMART_POINTER_H__
/* vi:set ts=4: */
