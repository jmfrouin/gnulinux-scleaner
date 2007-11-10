/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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

#include <iostream>
#include "thread.h"

namespace Tools
{
	IThread::IThread()
	{
	
	}
	
	
	IThread::~IThread()
	{
		std::cout << "Waiting end of thread ..." << '\n';
		pthread_join(m_Thread, 0);
	}
	
	
	int IThread::Run()
	{
		int l_ret;
	
		int l_tmp;
		std::cout << "Launching thread ..." << '\n';
		l_tmp = pthread_create(&m_Thread, 0, link, this);
	
		if(l_tmp != 0)
		{
			std::cerr <<  l_ret << strerror(l_ret) << '\n';
			l_ret = EXIT_FAILURE;
		}
		return l_ret;
	}
	
	
	/*void IThread::__Run()
	{
		std::cout << "I am in the thread !!" << '\n';
		std::cout << "But I am very tired I ll sleep a bit !!" << '\n';
		usleep(500000);
		std::cout << "Ok ready to ... quit :) !!" << '\n';
		__End();
	}*/
	
	void IThread::__End()
	{
		pthread_exit(0);
	}
}

/* vi:set ts=4: */
