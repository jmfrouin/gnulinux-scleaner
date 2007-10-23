/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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

#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

namespace Tools
{
	/*!
	 *@brief Thread another class by heritage.
	 */
	class IThread
	{
		public:
			IThread();
			virtual ~IThread();
	
			/*!
			 *@brief Launch thread
			 */
			int Run();
	
			/*!
			 *@brief The function to run to be pure virtual.
			 */
			virtual void __Run() = 0;
	
			/*!
			 *@brief Need to be call when __Run has end.
			 */
			void __End();
	
		private:
			pthread_t m_Thread;
	
	};
	
	static void* link(void* _context)
	{
		//IThread* l_Thread = dynamic_cast<IThread*>(_context);
		IThread* l_Thread = (IThread*)_context;
		l_Thread->__Run();
		return 0;
	}
}
#endif							 //_THREAD_H_
/* vi:set ts=4: */
