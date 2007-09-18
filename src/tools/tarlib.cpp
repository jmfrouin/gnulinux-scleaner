/* 
 Copyright (c) 2004-2005 Andrew Reading.
 Copyright (c) 2007 Sylvain Beucler.
 Copyright (c) 2007 Jean-Michel Frouin.
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
*/

#include "tarlib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

bool CTarLib::computeFileHeader(const std::string& _filename)
{
	bool l_ret = false;
	std::cout << "File header for " << _filename << " :" << '\n';
	
	std::string l_name(_filename);
	struct stat l_info;
	//Try to stat file.
	if(stat(l_name.c_str(), &l_info) == -1)
	{
		std::cout << "[ERR] : " __FILE__ << "@" << __LINE__ << ": Cannot stat " << l_name.c_str() << '\n';
		l_ret = false;
	}
	else
	{
		//Get size:
		std::cout << "Size : " << l_info.st_size << '\n';

#ifdef WIN32
        // No UID or GID support for Windows - Hack it up.
        //strncpy(Record.Mode, "0100777", 8);
        //strncpy(Record.Uid, "0000000", 8);
        //strncpy(Record.Gid, "0000000", 8);
#else
         int l_mode = 0;

         if(!(l_info.st_mode & S_IFREG))
         {
             // Not a normal file.  Let's archive it anyway, but warn the user.
             std::cout << "Warning: Archiving non-ordinary file (Linked or Device file?)" << '\n';
         }

         // Add the normal file bit.
         l_mode += 100000;

         //  Find out the file permissions.
         if(l_info.st_mode & 00400)
         {
             l_mode += 400;
         }
         if(l_info.st_mode & 00200)
         {
             l_mode += 200;
         }
         if(l_info.st_mode & 00100)
         {
             l_mode += 100;
         }
         if(l_info.st_mode & 00040)
         {
             l_mode += 40;
         }
         if(l_info.st_mode & 00020)
         {
             l_mode += 20;
         }
         if(l_info.st_mode & 00010)
         {
             l_mode += 10;
         }
         if(l_info.st_mode & 00004)
         {
             l_mode += 4;
         }
         if(l_info.st_mode & 00002)
         {
             l_mode += 2;
         }
         if(l_info.st_mode & 00001)
         {
             l_mode += 1;
         }

		std::string l_modestr;
		std::stringstream* l_tmp = new std::stringstream;
		(*l_tmp) << l_mode;
		l_modestr += l_tmp->str();
        l_modestr = PadWithZeros(l_modestr, 8);
		delete l_tmp;
		
		std::cout << "Mode (8b) : " << l_modestr << '\n';

		//UID
		std::string l_uid;
		l_tmp = new std::stringstream;
		(*l_tmp) << l_info.st_uid;
		l_uid += l_tmp->str();
		delete l_tmp;
        l_uid = PadWithZeros(l_uid, 8);
		std::cout << "UID (8b) : " << l_uid << '\n';
		
		//GID
		std::string l_gid;
		l_tmp = new std::stringstream;
		(*l_tmp) << l_info.st_gid;
		l_gid += l_tmp->str();
		delete l_tmp;
        l_gid = PadWithZeros(l_gid, 8);
		std::cout << "GID (8b) : " << l_gid << '\n';

    	// File Size.
    	std::string strFileSize = DecToOct(iFileEnd - iFileBegin);
    	strncpy(Record.Size, PadWithZeros(strFileSize, 12).c_str(), 12);

    // Time of modification
    std::string strTime = DecToOct(time(0));
    strncpy(Record.Mtime, PadWithZeros(strTime, 12).c_str(), 12);

    // Add blank checksum.
    memset(Record.Chksum, 0, 8);

    // Type of file.
    Record.Linkflag = 0;
    strncpy(Record.Linkname, "", 100);
    strncpy(Record.Magic, "ustar", 8);

		l_ret=true;
#endif
	}

	return l_ret;	
}

/* vi:set ts=4: */

/*
TarHeader CTar::FillHeader()
{
    int iFileBegin = 0;
    int iFileEnd = 0;
    int iChksum = 0;
    TarHeader Record;
    char *RecordPtr;
    std::string strData = strTarfileIn;
 
    
    if(bPrefixed)
    {
        // Take the first part off.
        unsigned int uiPos = strData.find(strPrefix.c_str(), 0);
        
        if(uiPos != std::string::npos)
        {
            strData.erase(0, uiPos + strPrefix.size());
        }
    }

    // Start collecting data.
    strncpy(Record.Name, strTarfileIn.c_str(), 100);

//    #ifdef WIN32
        // No UID or GID support for Windows - Hack it up.
        strncpy(Record.Mode, "0100777", 8);
        strncpy(Record.Uid, "0000000", 8);
        strncpy(Record.Gid, "0000000", 8);
//    #else
//         int l_mode = 0;
//         struct stat l_info;
//         std::string strBuf;

//         // Never works: we're not in the DMod dir and paths are relative...
//         if (stat(strTarfileIn.c_str(), &l_info) < 0)
// 	  {
// 	    perror("stat");
// 	    exit(1);
// 	  }

//         if(!(l_info.st_mode & S_IFREG))
//         {
//             // Not a normal file.  Let's archive it anyway, but warn the user.
//             fl_message("Warning: Archiving non-ordinary file (Linked or Device file?).");
//         }

//         // Add the normal file bit.
//         l_mode += 100000;

//         //  Find out the file pernissions.
//         if(l_info.st_mode & 00400)
//         {
//             l_mode += 400;
//         }
//         if(l_info.st_mode & 00200)
//         {
//             l_mode += 200;
//         }
//         if(l_info.st_mode & 00100)
//         {
//             l_mode += 100;
//         }
//         if(l_info.st_mode & 00040)
//         {
//             l_mode += 40;
//         }
//         if(l_info.st_mode & 00020)
//         {
//             l_mode += 20;
//         }
//         if(l_info.st_mode & 00010)
//         {
//             l_mode += 10;
//         }
//         if(l_info.st_mode & 00004)
//         {
//             l_mode += 4;
//         }
//         if(l_info.st_mode & 00002)
//         {
//             l_mode += 2;
//         }
//         if(l_info.st_mode & 00001)
//         {
//             l_mode += 1;
//         }

//         // Write it to the Mode header.
//         strBuf = ToString(l_mode);
//         strncpy(Record.Mode, PadWithZeros(strBuf, 8).c_str(), 8);

//         // Write the UID and GID.
//         strBuf = ToString(l_info.st_uid);
//         strncpy(Record.Uid, PadWithZeros(strBuf, 8).c_str() ,8);

//         strBuf = ToString(l_info.st_gid);
//         strncpy(Record.Gid, PadWithZeros(strBuf, 8).c_str(), 8);
//     #endif

    // File Size.
    std::string strFileSize = DecToOct(iFileEnd - iFileBegin);
    strncpy(Record.Size, PadWithZeros(strFileSize, 12).c_str(), 12);

    // Time of modification
    std::string strTime = DecToOct(time(0));
    strncpy(Record.Mtime, PadWithZeros(strTime, 12).c_str(), 12);

    // Add blank checksum.
    memset(Record.Chksum, 0, 8);

    // Type of file.
    Record.Linkflag = 0;
    strncpy(Record.Linkname, "", 100);
    strncpy(Record.Magic, "ustar", 8);

    // Windows again, let's cheat.
//     #ifdef WIN32
        strncpy(Record.Uname, "root", 32);
        strncpy(Record.Gname, "root", 32);
//     #else
//         passwd *pwdFileInfo = getpwuid(l_info.st_uid);
//         group *grpFileInfo = getgrgid(l_info.st_gid);

//         if(!pwdFileInfo || !grpFileInfo)
//         {
//             // No entry.  Let's fake it.
//             strncpy(Record.Uname, Record.Uid, 32);
//             strncpy(Record.Gname, Record.Gid, 32);
//         }
//         else
//         {
//             strncpy(Record.Uname, pwdFileInfo->pw_name, 32);
//             strncpy(Record.Gname, grpFileInfo->gr_name, 32);
//         }
//     #endif

    // Skip devminor and devmajor.
    strncpy(Record.Devmajor, "", 8);
    strncpy(Record.Devminor, "", 8);

    // Fill the padding.
    strncpy(Record.Padding, "", 167);

    // Initialize our pointer.
    RecordPtr = reinterpret_cast<char*>(&Record);

    // Find the checksum.
    for(RecordPtr; (RecordPtr - reinterpret_cast<char*>(&Record)) < 512; ++RecordPtr)
    {
        iChksum += static_cast<int>(*RecordPtr);
    }

    // Add 256 (2^8)
    iChksum += 256;

    // Get it to Octal.
    std::string Chksum = DecToOct(iChksum);
    strncpy(Record.Chksum, PadWithZeros(Chksum, 8).c_str(), 8);

    return Record;
}

*/
