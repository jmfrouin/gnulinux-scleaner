/**
 * This file is part of scleaner project.

 * Copyright (C) 2007,2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.org
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

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include "types.h"

namespace Tools
{
  /*!
   *@brief Mutex
   */
  class CMutex
  {
    public:
      /*!
       *@brief ctor
       */
      CMutex();

      /*!
       *@brief dtor.
       */
      ~CMutex();

      /*!
       *@brief pthread_mutex_lock encapsulation
       */
      void Lock();

      /*!
       *@brief pthread_mutex_unlock encapsulation
       */
      void UnLock();

    private:
      Mutex fMutex;
  };
}                                // namespace Tools
#endif                           // __MUTEX_H__
