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

//#ifdef !DEBUG

#ifndef _LEAK_DETECTOR_H_
#define _LEAK_DETECTOR_H_

#include "memory_manager.h"

extern CMemoryManager g_mm;

/*!
 * @brief new operator surcharge
 */
inline void* operator new(std::size_t Size, const char* File, int Line)
{
	return g_mm.Allocate(Size, File, Line, false);
}


/*!
 * @brief new[] operator surcharge
 */
inline void* operator new[](std::size_t Size, const char* File, int Line)
{
	return g_mm.Allocate(Size, File, Line, true);
}


/*!
 * @brief delete operator surcharge
 */
inline void operator delete(void* Ptr)
{
	g_mm.Free(Ptr, false);
}


/*!
 * @brief delete[] operator surcharge
 */
inline void operator delete(void* Ptr, const char* File, int Line)
{
	g_mm.NextDelete(File, Line);
	g_mm.Free(Ptr, false);
}


inline void operator delete[](void* Ptr)
{
	g_mm.Free(Ptr, true);
}


inline void operator delete[](void* Ptr, const char* File, int Line)
{
	g_mm.NextDelete(File, Line);
	g_mm.Free(Ptr, true);
}
#endif							 // _LEAK_DETECTOR_H__

#undef delete

#ifndef new
#define new    new(__FILE__, __LINE__)
#define delete g_mm.NextDelete(__FILE__, __LINE__), delete
#endif

//#endif // DEBUG
/* vi:set ts=4: */
