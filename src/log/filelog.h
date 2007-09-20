/*
Copyright (C) 2007 FROUIN Jean-Michel
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

------------------------------------------------------
Project : scleaner
------------------------------------------------------
$Date$
$Rev$
$Author$
------------------------------------------------------
*/

#ifndef _FILELOG_H
#define _FILELOG_H

#include <fstream>
#include <sstream>

class CFileLog
{
public :
    CFileLog(const std::string& Filename = "output.log");
    ~CFileLog();

    template <class T> CFileLog& operator <<(const T& ToLog)
    {
        std::ostringstream Stream;
        Stream << ToLog;
        m_File << Stream.str();
        return *this;
    }

private:
    std::ofstream m_File;
};

#endif // _FILELOG_H
/* vi:set ts=4: */
