/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

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

 * This file is based on file from Laurent Gomilla :
 * http://loulou.developpez.com/tutoriels/moteur3d/
*/

#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__

#include <fstream>
#include <map>
#include <stack>
#include <string>
#include <log/log.h>

/*!
 * @brief Memory manager, in fact for the moment it's only a leak detector.
 * @version 23.10.2007
 * @author Jean-Michel Frouin (jmfrouin@gmail.com)
 */
class CMemoryManager
{
        public :
                /*!
                 * @brief       Default constructor.
                 */
                CMemoryManager();
                /*!
                 * @brief       Destructor.
                 */
                ~CMemoryManager();

                /*!
                 * @brief       Do memory allocation.
                 * @param       _size Size to allocate.
                 * @param       _file Store the file where delete is did.
                 * @param       _line Store the line where delete is did.
                 * @param       _array Pointer point on array type ?.
                 */
                void* Allocate(std::size_t size, const std::string& file, int line, bool array);
                /*!
                 * @brief       Free memory.
                 * @param       _ptr Pointer on memory zone to free.
                 * @param       _array Pointer point on array type ?.
                 */
                void Free(void* ptr, bool array);
                /*!
                 * @brief       Default constructor.
                 * @param       _file Store the file where delete is did.
                 * @param       _line Store the line where delete is did.
                 */
                void NextDelete(const std::string& file, int line);

                void Report();

        private:
                /*!
                 * @brief Memory stucture.
                 */
                struct TBlock
                {
                        std::size_t             Size;
                        std::string             File;
                        unsigned int            Line;
                        bool                    Array;
                        static std::size_t      Total;
                };

                typedef std::map<void*, TBlock> TBlockMap;

                TBlockMap          fBlocks;
                std::stack<TBlock> fDeleteStack;
                std::ofstream fFile;
};
#endif                                                   // __MEMORY_MANAGER_H__
/* vi:set ts=4: */
