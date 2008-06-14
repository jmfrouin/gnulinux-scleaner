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

#ifndef __LOG_H__
#define __LOG_H__

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <tools/singleton.h>
#include <def.h>

namespace Log
{
        class CLog : public Tools::TSingleton<CLog>
        {
                 public :
                        /*!
                         * @brief Logger
                         * @version 15.11.2007
                         * @author Jean-Michel Frouin (jmfrouin@gmail.com)
                         */
                        CLog(const std::string& file = LOGFILE);

                        ~CLog();

                        void Open(const std::string& file = LOGFILE);

                        void Close();

                        void Log(const std::string&  file, const int& line, const std::string& tolog, bool nl = false);

                        template <class T, class U>
                        void Log(const std::string& file, const int& line, const T& tolog, const U& tolog2, bool nl = false)
                        {
                            fFile << VERT << "[DBG] [" << file << ':' << line << "] "  << tolog << tolog2 << STOP;
                            if(nl)
                                fFile << '\n';
                            fFile.flush();
                        }

                protected :
                        /*!
                         * @brief Display current date.
                         * @return std::string Date.
                         */
                        std::string Date() const { return __DATE__; }

                        /*!
                         * @brief Display current time.
                         * @return std::string Time
                         */
                        std::string Time() const {return __TIME__; }

                private:
                    std::ofstream fFile;
        };

}

#endif                                                   // __LOG_H__
/* vi:set ts=4: */
