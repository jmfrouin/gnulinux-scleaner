/**
 * This file is part of scleaner project.

 * Copyright (c) 2004-2005 Andrew Reading.
 * Copyright (c) 2007 Sylvain Beucler.
 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

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

#ifndef _TAR_ARCHIVE_H_
#define _TAR_ARCHIVE_H_

#include <list>
#include <string>
#include <iostream>

class IProgressbar;

namespace Tools
{
    /*!
     *@brief Only to create GNU tar archive for the moment.
     */
    class CTarArchive
    {
        public:

            /*!
             *@brief Constructor
             */
            CTarArchive();

        private:

            /* tar Header Block, from POSIX 1003.1-1990.
               POSIX header.  */
            struct posix_header
            {                        /* byte offset */
                char name[100];      /*   0 */
                char mode[8];        /* 100 */
                char uid[8];         /* 108 */
                char gid[8];         /* 116 */
                char size[12];       /* 124 */
                char mtime[12];      /* 136 */
                char chksum[8];      /* 148 */
                char typeflag;       /* 156 */
                char linkname[100];  /* 157 */
                char magic[6];       /* 257 */
                char version[2];     /* 263 */
                char uname[32];      /* 265 */
                char gname[32];      /* 297 */
                char devmajor[8];    /* 329 */
                char devminor[8];    /* 337 */
                char prefix[155];    /* 345 */
                char padding[12];    /* 500-512 (pad to exactly the TAR_BLOCK_SIZE) */
            };

            /*!
             *@brief Compute file header.
             *@param _filename File name.
             *@param _header The header to fill.
             *@return true on success, false otherwise.
             */
            bool FillHeader(const std::string& _filename, posix_header& _header);

            /*!
             *@brief Write data from an input file to the output .tar.
             *@param _input Input file name.
             *@param _output Output file name.
             *@return true on success, false otherwise.
             */
            bool WriteData(const std::string& _input, const std::string& _output);

            /*!
             *@brief Close correctly the tar.
             *@param _output Output file name.
             *@return true on success, false otherwise.
             */
            bool CleanClose(const std::string& _output);

        public:

            /*!
             *@brief Create a tar archive.
             *@param _filenames List of filename to tar.
             *@param _output Output file name.
             *@param _callback Progressbar callback.
             *@return true on success, false otherwise.
             */
            bool Create(std::list<std::string> _filenames, const std::string& _output, IProgressbar* _callback);

        private:

            /*!
             *@brief Fill a string will 0.
             *@param _s string to pad.
             *@param _size pad size.
             *@return a std::string padded.
             *@todo Move it to engine maybe ?
             */
            std::string PadWithZeros(std::string& _s, unsigned int _size);

            /*!
             *@brief Convert an int to std::string.
             *@param _nb The int to convert.
             *@return std::string.
             */
            std::string itos(int _nb);

            /*!
             *@brief Convert a decimal int to octal int.
             *@param _nb The decimal int to convert.
             *@return octal int in a std::string.
             */
            std::string DecToOct(int _nb);

            /*!
             *@brief Round an int to 512.
             *@param n int to round.
             *@return number of \0 to insert.
             */
            int RoundTo512(int n);

        private:
            bool    m_FirstFile;
    };
}
#endif                           // _TAR_ARCHIVE_H_
/* vi:set ts=4: */
