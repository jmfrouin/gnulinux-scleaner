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

#include <iomanip>
#include <sstream>
#include <iostream>
#include <config.h>
#include <def.h>
#include <log/log.h>

#include "memory_manager.h"

std::size_t CMemoryManager::TBlock::Total = 0;

CMemoryManager::CMemoryManager()
{
  fFile.open(LEAKFILE);
  if (!fFile)
    std::cout << i8n("[ERR] : Cannot open ") << fFile << '\n';
  //    throw CLoadingFailed("Memory leaks.log", "Impossible d'accder en criture");
  fFile << " MemoryManager v" << VERSION_MEMORY_MANAGER << i8n(" - Report (Compiled on ") << __DATE__ << " @ " << __TIME__ << ")" << '\n';
}


CMemoryManager::~CMemoryManager()
{
  #if defined DEBUG
  //Log::CLog::Instance()->Log(__FILE__, __LINE__, "[CMemoryManager] ~CMemoryManager()");
  #endif

  if (fBlocks.empty())
  {
    fFile << '\n';
    fFile << "====================================================================================" << '\n';
    fFile << i8n("   No leak detected, congratulations !  ") << '\n';
    fFile << "====================================================================================" << '\n';
  }
  else
  {
    fFile << '\n';
    fFile << "====================================================================================" << '\n';
    fFile << i8n(" Oops... Some leaks have been detected  ") << '\n';
    fFile << "====================================================================================" << '\n';
    fFile << '\n';
    Report();
    fFile << "Byeeeeeeeeeeee\n";
  }
}


void CMemoryManager::Report()
{
  #if defined DEBUG
  //Log::CLog::Instance()->Log(__FILE__, __LINE__, "[CMemoryManager] ReportLeaks()");;
  #endif

  std::size_t TotalSize = 0;
  for (TBlockMap::iterator i = fBlocks.end(); --i != fBlocks.begin();)
  {
    TotalSize += i->second.Size;
    fFile << "-> 0x" << i->first
      << " | "   << std::setw(7) << std::setfill(' ') << static_cast<int>(i->second.Size) << i8n(" bytes")
      << " | "   << i->second.File << " (" << i->second.Line << ")" << '\n';
    free(i->first);
  }

  fFile << '\n' << "-- "
    << static_cast<int>(fBlocks.size()) << i8n(" blocs not empty, ")
    << static_cast<int>(TotalSize)       << i8n(" bytes --")
    << '\n';

}


void* CMemoryManager::Allocate(std::size_t size, const std::string& file, int line, bool array)
{
  void* Ptr = malloc(size);

  TBlock NewBlock;
  NewBlock.Size  = size;
  NewBlock.File  = file;
  NewBlock.Line  = line;
  NewBlock.Array = array;
  NewBlock.Total += size;
  fBlocks[Ptr]  = NewBlock;

  /*#if defined DEBUG && VERBOSE
  Log::CLog::Instance()->Log(__FILE__, __LINE__, "[CMemoryManager] Allocate()" << Ptr << '\n';
  Log::CLog::Instance()->Log(__FILE__, __LINE__, "[CMemoryManager] +++" << " " << Ptr << " " << static_cast<int>(NewBlock.Size) << " " << NewBlock.Total << " " << NewBlock.File << " " << NewBlock.Line << '\n';
  #endif*/

  fFile << "+++" << " " << Ptr << " " << static_cast<int>(NewBlock.Size) << " " << NewBlock.Total << " " << NewBlock.File << " " << NewBlock.Line << '\n';

  return Ptr;
}


void CMemoryManager::Free(void* ptr, bool array)
{
  TBlockMap::iterator It = fBlocks.find(ptr);

  /*#if defined DEBUG && VERBOSE
  Log::CLog::Instance()->Log(__FILE__, __LINE__, "[CMemoryManager] Free(" << ptr << ") " << '\n';
  #endif*/

  if (It == fBlocks.end())
  {
    free(ptr);
    return;
  }

  if (It->second.Array != array)
  {
    fFile << "-- ERR | 0x" << ptr << " @ " << It->second.File << i8n(" Line : ") << It->second.Line << '\n';
    return;
  }

  if(!fDeleteStack.empty())
    fFile << "---" << " " << ptr << " " << static_cast<int>(It->second.Size) << " " << fDeleteStack.top().File << " " << fDeleteStack.top().Line << '\n';
  else
    fFile << "---" << " " << ptr << " " << static_cast<int>(It->second.Size) << '\n';

  fBlocks.erase(It);
  if(!fDeleteStack.empty())
    fDeleteStack.pop();
  free(ptr);
}


void CMemoryManager::NextDelete(const std::string& file, int line)
{
  TBlock Delete;
  Delete.File = file;
  Delete.Line = line;

  fDeleteStack.push(Delete);
}


/* vi:set ts=4: */
