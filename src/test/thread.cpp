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

 * This file is based on file from Laurent Gomilla :
 * http://loulou.developpez.com/tutoriels/moteur3d/
*/


#include <iostream>
#include "thread.h"

CThread::CThread()
{

}


CThread::~CThread()
{

}


int CThread::Run()
{
        int Ret;

        int l_tmp;
        std::cout << "Launching thread ..." << '\n';
        l_tmp = pthread_create(&m_Thread, 0, link, this);

        if(l_tmp != 0)
        {
                std::cerr <<  Ret << strerror(Ret) << '\n';
                Ret = EXIT_FAILURE;
        }
        std::cout << "Waiting end of thread ..." << '\n';

        pthread_join(m_Thread, 0);

}


void CThread::__Run()
{
        std::cout << "I am in the thread !!" << '\n';
        std::cout << "But I am very tired I ll sleep a bit !!" << '\n';
        usleep(500000);
        std::cout << "Ok ready to ... quit :) !!" << '\n';
        pthread_exit(0);
}


/* vi:set ts=4: */
