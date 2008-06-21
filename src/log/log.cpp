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
 */

#include "log.h"
#include <leak/leak_detector.h>

namespace Log
{
  CLog::CLog(const std::string& file)
  {
    fFile.open(file.c_str(), std::ios::out | std::ios::trunc);
    if (!fFile)
      std::cout << i8n("[ERR] : Cannot open ") << file << '\n';

    fFile  << "===========================================" << '\n';
    fFile  << "   - CLog  v" << VERSION_FILELOG << " - Event log - " << '\n';
    fFile  << "===========================================" << '\n';
    fFile  << '\n';
    fFile.flush();
  }

  CLog::~CLog()
  {
    std::cout << "Close\n";
    fFile  << '\n';
    fFile  << "===========================================" << '\n';
    fFile  << "  - CLog " << VERSION_FILELOG << " Event log closed - " << '\n';
    fFile  << "===========================================" << '\n';
    fFile.flush();
    Close();
  }

  void CLog::Close()
  {
    if(fFile.is_open())
      fFile.close();
  }

  void CLog::Log(const std::string& file, const int& line, const std::string& tolog, bool nl)
  {
    //if dbg
    fFile << VERT << "[DBG] [" << file << ':' << line << "] " << tolog << STOP;
    if(nl)
      fFile << '\n';
    fFile.flush();
  }
}


/* vi:set ts=4: */
