/*
Copyright (C) 2007 FROUIN Jean-Michel
------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------
Project : scleaner
------------------------------------------------------
$Date$
$Rev$
$Author$
------------------------------------------------------
*/

#ifndef _SMART_POINTER_
#define _SMART_POINTER_

#include <iostream>

#if defined LEAKS
#include <leak_detector.h>
#endif

typedef unsigned int t_SmartCpt;

/*!
 * @brief Simple counter used by Smart pointer.
 */
class CSmartCpt
{
    public:
		/*!
		*@brief Default constructor
		*/
        CSmartCpt(): m_Counter(0) {}

		/*!
		*@brief Destructor
		*/
        virtual ~CSmartCpt() {}

        /*!
         * @brief Increment counter.
         */
        t_SmartCpt _incRef() { return ++m_Counter; }

        /*!
         * @brief Decrement counter.
         */
        t_SmartCpt _decRef() { return --m_Counter; }
    private:
        t_SmartCpt m_Counter;    ///< Reference counter.
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
        TSmartPtr(): m_Object(0) {}

        /*!
         *@brief Destructor.
         */
        ~TSmartPtr() { *this = 0; }

        /*!
         * @brief Simple pointer affectation.
         */
        TSmartPtr<T>& operator=(T* _Object)
        {
            if(_Object)
            {
                _Object->_incRef();
            }

            if(m_Object)
            {
                t_SmartCpt l_cpt;
                l_cpt = m_Object->_decRef();
                if(l_cpt == 0)
                {
                    delete m_Object;
                }
            }
            m_Object = _Object;
            return *this;
        }

        /*!
         * @brief Smart pointer affectation.
         */
        TSmartPtr<T>& operator=(TSmartPtr<T>& _Object)
        {
            *this = _Object.m_Object;
            return *this;
        }

		/*!
		*@brief In order to use it, as a dumb pointer.
		*/
		operator T*()
		{
			return m_Object;
		}

		bool operator==(const int& _Value) const
		{
			bool l_ret;
			l_ret = ((int)this == _Value);
			return l_ret;
		}

		bool operator!=(const int& _Value) const
		{
			bool l_ret;
			l_ret = ((int)this != _Value);
			return l_ret;
		}

        /*!
         *@brief Dereferencement operators for object.
         */
        T& operator*() { return *m_Object; }

        /*!
         *@brief Dereferencement operators for pointer on object.
         */
        T* operator->() { return m_Object; }

    private:
        T* m_Object;             ///< Object handle by this pointer.
};
#endif                           //_SMART_POINTER_
/* vi:set ts=4: */
