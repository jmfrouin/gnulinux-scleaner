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
#include "types.h"

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
             *@brief Start thread.
             */
            void Start();

            /*!
             *@brief The function to run to be pure virtual.
             */
            virtual void Run() = 0;
            const bool Running() const { return fRunning; }

             /*!
             *@brief Stop the thread.
             */
            void Stop();

            /*!
            *@brief Wait the end of thread.
            */
            void Join();

            /*!
             *@brief Lock the mutex.
             */
            void Lock() { return fLock.Lock(); }

            /*!
             *@brief Unlock mutex
             */
            void UnLock() { return fLock.UnLock(); }

            static const int GetCount() { return fCount; }
            static const int GetMax() { return fMax; }
            static void SetMax(const int tmax) { fMax = tmax; }

        protected:
            static void* __Run(void* thread);

        protected:
            Thread fThread;
            static int fCount;
            static int fMax;
            CMutex fLock;
            volatile bool fRunning;
    };
}
#endif                           //__THREAD_H__
/* vi:set ts=4: */
