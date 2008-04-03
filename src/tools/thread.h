/**
 * This file is part of scleaner project.

 * Copyright (C) 2007,2008 FROUIN Jean-Michel

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

#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <unistd.h>
#include "mutex.h"
typedef pthread_t Thread;

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
            int Start();

            /*!
             *@brief The function to run to be pure virtual.
             */
            virtual void Run() = 0;
            const bool Running() const { return fRunning; }

            static const int GetCount();
            static const int GetMax();
            static void SetMax(const int tmax);

            /*!
             *@brief Need to be call when Run has end.
             */
            void Stop();

        private:
            Thread fThread;
            static int fCount;
            static int fMax;
            CMutex fLock;
            bool fRunning;
    };

    int IThread::fCount = 0;
    int IThread::fMax = 16;
}
#endif                           //__THREAD_H__
/* vi:set ts=4: */
