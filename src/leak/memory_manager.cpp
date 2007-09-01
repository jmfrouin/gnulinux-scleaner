/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
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

-------------------------------------------------------------------------

This file is based on file from Laurent Gomilla : 
http://loulou.developpez.com/tutoriels/moteur3d/

-------------------------------------------------------------------------
$Date$
$Rev$
$Author$
-------------------------------------------------------------------------
*/

#include <iomanip>
#include <sstream>
#include <iostream>
#include <config.h>

#include "memory_manager.h"

std::size_t CMemoryManager::TBlock::Total = 0;

CMemoryManager::CMemoryManager()
{
    m_File.open("_memoryleaks.log");
    if (!m_File)
    {
        std::cout << "Erreur : Cannot open m_File" << std::endl;
    }

    //    throw CLoadingFailed("Memory leaks.log", "Impossible d'accéder en écriture");
    m_File << " MemoryManager v" << VERSION_MEMORY_MANAGER << ___(" - Report (Compiled on ") << __DATE__ << " @ " << __TIME__ << ")" << std::endl;
}

CMemoryManager::~CMemoryManager()
{
#if defined DEBUG
        std::cout << "[DEBUG] [CMemoryManager] ~CMemoryManager()" << std::endl;
#endif

    if (m_Blocks.empty())
    {
        m_File << std::endl;
        m_File << "====================================================================================" << std::endl;
        m_File << ___("   No leak detected, congratulations !  ") << std::endl;
        m_File << "====================================================================================" << std::endl << std::endl;
    }
    else
    {
        m_File << std::endl;
        m_File << "====================================================================================" << std::endl;
        m_File << ___(" Oops... Some leaks have been detected  ") << std::endl;
        m_File << "====================================================================================" << std::endl << std::endl;
        m_File << std::endl;
        Report();
    }
}

void CMemoryManager::Report()
{
#if defined DEBUG
        std::cout << "[DEBUG] [CMemoryManager] ReportLeaks()" << std::endl;
#endif

    std::size_t TotalSize = 0;
    for (TBlockMap::iterator i = m_Blocks.begin(); i != m_Blocks.end(); ++i)
    {
        TotalSize += i->second.Size;
        m_File << "-> 0x" << i->first
            << " | "   << std::setw(7) << std::setfill(' ') << static_cast<int>(i->second.Size) << " bytes"
            << " | "   << i->second.File << " (" << i->second.Line << ")" << std::endl;
        free(i->first);
    }

    m_File << std::endl << std::endl << "-- "
        << static_cast<int>(m_Blocks.size()) << ___(" blocs not empty, ")
        << static_cast<int>(TotalSize)       << ___(" bytes --")
        << std::endl;

}

void* CMemoryManager::Allocate(std::size_t _size, const std::string& _file, int _line, bool _array)
{
    void* Ptr = malloc(_size);

#if defined DEBUG && VERBOSE
    std::cout << "[DEBUG] [CMemoryManager] Allocate()" << Ptr << std::endl;
    std::cout << "[DEBUG] [CMemoryManager] +++" << " " << Ptr << " " << static_cast<int>(NewBlock.Size) << " " << NewBlock.Total << " " << NewBlock.File << " " << NewBlock.Line << std::endl;
#endif

    TBlock NewBlock;
    NewBlock.Size  = _size;
    NewBlock.File  = _file;
    NewBlock.Line  = _line;
    NewBlock.Array = _array;
    NewBlock.Total += _size;
    m_Blocks[Ptr]  = NewBlock;

    m_File << "+++" << " " << Ptr << " " << static_cast<int>(NewBlock.Size) << " " << NewBlock.Total << " " << NewBlock.File << " " << NewBlock.Line << std::endl;

    return Ptr;
}

void CMemoryManager::Free(void* _ptr, bool _array)
{
    TBlockMap::iterator It = m_Blocks.find(_ptr);

#if defined DEBUG && VERBOSE
        std::cout << "[DEBUG] [CMemoryManager] Free(" << _ptr << ") " << std::endl;
#endif

    if (It == m_Blocks.end())
    {
        free(_ptr);
        return;
    }

    if (It->second.Array != _array)
    {
        m_File << "-- ERREUR | 0x" << _ptr << " @ " << It->second.File << ___(" Line : ") << It->second.Line << std::endl;
        return;
    }

    if(!m_DeleteStack.empty())
    {
        m_File << "---" << " " << _ptr << " " << static_cast<int>(It->second.Size) << " " << m_DeleteStack.top().File << " " << m_DeleteStack.top().Line << std::endl;
    }
    else
    {
        m_File << "---" << " " << _ptr << " " << static_cast<int>(It->second.Size) << std::endl;
    }

    m_Blocks.erase(It);
    if(!m_DeleteStack.empty())
    {
        m_DeleteStack.pop();
    }
    free(_ptr);
}

void CMemoryManager::NextDelete(const std::string& _file, int _line)
{
    TBlock Delete;
    Delete.File = _file;
    Delete.Line = _line;

    m_DeleteStack.push(Delete);
}
/* vi:set ts=4: */
