/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
*/
/*
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
$Date: 2007-08-13 21:07:17 +0200 (lun, 13 aoû 2007) $
$Rev: 13 $
$Author: snoogie_sf $
------------------------------------------------------

*/

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <leak/leak_detector.h>

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
			T* l_ret = m_Inst;

			if(!l_ret)
			{
				m_Inst = l_ret = new T;
			}

			return l_ret;
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
		static T*	m_Inst;	///< The only single instance.
};

template <class T>
T* TSingleton<T>::m_Inst = 0;

#endif //_SINGLETON_H_
/* vi:set ts=4: */
