/**
 * This file is part of scleaner project.

 * Copyright (c) 2004-2005 Andrew Reading.
 * Copyright (c) 2007 Sylvain Beucler.
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

#include "tar_archive.h"
#include <tar.h>
#include <grp.h>
#include <pwd.h>
#include <config.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <engine/iprogress.h>
#include <engine/settings_manager.h>
#include <log/log.h>

namespace Tools
{
    CTarArchive::CTarArchive():
    m_FirstFile(false)
    {
    }


    bool CTarArchive::FillHeader(const std::string& filename, posix_header& header)
    {
        bool Ret = false;

        #if defined DEBUG && defined VERBOSE
        std::cout << i8n("[DBG]File header for ") << filename << " :" << '\n';
        #endif

        struct stat Info;

        memset(&header, 0, 512);

        //Try to stat file.
        if(stat(filename.c_str(), &Info) == -1)
        {
            std::cout << i8n("[WNG] Cannot stat file: ") << filename.c_str() << i8n(" so I skip it !") << '\n';
            Ret = false;
        }
        else
        {
            std::string l_name(filename);

            #if defined WIN32
            // No UID or GID support for Windows - Hack it up.
            strncpy(header.mode, "0100777", 8);
            strncpy(header.uid, "0000000", 8);
            strncpy(header.gid, "0000000", 8);
            #else
            int Mode = 0;

            //Never reached ?
            if(!(Info.st_mode & S_IFREG))
            {
                // Not a normal file.  Let's archive it anyway, but warn the user.
                std::cout << i8n("[WNG] Archiving non-ordinary file (Linked or Device file?)") << '\n';
            }

            // Add the normal file bit.
            Mode += 100000;

            //  Find out the file permissions.
            if(Info.st_mode & TUREAD)
                Mode += 400;
            if(Info.st_mode & TUWRITE)
                Mode += 200;
            if(Info.st_mode & TUEXEC)
                Mode += 100;
            if(Info.st_mode & TGREAD)
                Mode += 40;
            if(Info.st_mode & TGWRITE)
                Mode += 20;
            if(Info.st_mode & TGEXEC)
                Mode += 10;
            if(Info.st_mode & TOREAD)
                Mode += 4;
            if(Info.st_mode & TOWRITE)
                Mode += 2;
            if(Info.st_mode & TOEXEC)
                Mode += 1;

            std::string Modestr(itos(Mode));
            Modestr = PadWithZeros(Modestr, 8);
            strncpy(header.mode, Modestr.c_str(), 8);

            //UID
            std::string l_uid(DecToOct(Info.st_uid));
            l_uid = PadWithZeros(l_uid, 8);
            strncpy(header.uid, l_uid.c_str(), 8);

            //GID
            std::string l_gid(DecToOct(Info.st_gid));
            l_gid = PadWithZeros(l_gid, 8);
            strncpy(header.gid, l_gid.c_str(), 8);

            // File Size.
            std::string Size = DecToOct(Info.st_size);
            Size = PadWithZeros(Size, 12);
            strncpy(header.size, Size.c_str(), 12);

            // Time of modification
            std::string l_mtime = DecToOct(time(0));
            l_mtime = PadWithZeros(l_mtime, 12);
            strncpy(header.mtime, l_mtime.c_str(), 12);

            // Type of file.
            header.typeflag = REGTYPE;

            if (S_ISLNK(Info.st_mode))
                header.typeflag = SYMTYPE;
            else
            {
                if (S_ISDIR(Info.st_mode))
                {
                    header.typeflag = DIRTYPE;
                    l_name += "/";
                }
            }

            strncpy(header.name, l_name.c_str(), 100);

            strncpy(header.linkname, "", 100);

            // Magic
            strncpy(header.magic, TMAGIC, TMAGLEN);

            strncpy(header.version, TVERSION, TVERSLEN);

            // Windows again, let's cheat.
            #if defined WIN32
            strncpy(header.uname, "root", 32);
            strncpy(header.gname, "root", 32);
            #else
            passwd* l_pwdFileInfo = getpwuid(Info.st_uid);
            group* l_grpFileInfo = getgrgid(Info.st_gid);

            if(!l_pwdFileInfo || !l_grpFileInfo)
            {
                // No entry.  Let's fake it.
                strncpy(header.uname, header.uid, 32);
                strncpy(header.gname, header.gid, 32);
            }
            else
            {
                strncpy(header.uname, l_pwdFileInfo->pw_name, 32);
                strncpy(header.gname, l_grpFileInfo->gr_name, 32);
            }
            #endif

            // Skip devminor and devmajor.
            strncpy(header.devmajor, "", 8);
            strncpy(header.devminor, "", 8);

            // Fill the prefix.
            strncpy(header.prefix, "", 167);

            // Initialize our pointer.
            char* l_startheaderPtr = reinterpret_cast<char*>(&header);
            char* lheaderPtr ;
            int l_checksum = 0;

            // Find the checksum.
            for(lheaderPtr = l_startheaderPtr; (lheaderPtr - l_startheaderPtr) < 512; ++lheaderPtr)
                l_checksum += static_cast<int>(*lheaderPtr);

            // Add 256 (2^8)
            l_checksum += 256;

            // Get it to Octal.
            std::string l_checksumstr = DecToOct(l_checksum);
            l_checksumstr = PadWithZeros(l_checksumstr, 8);
            strncpy(header.chksum, l_checksumstr.c_str(), 8);

            #if defined DEBUG && defined VERBOSE
            Log::CLog::Instance()->Log(__FILE__, __LINE__, "Mode (8bytes) : ", header.mode, true);
            Log::CLog::Instance()->Log(__FILE__, __LINE__, "UID (8b) : ", header.uid, true);
            Log::CLog::Instance()->Log(__FILE__, __LINE__, "GID (8b) : ", header.gid, true);
            Log::CLog::Instance()->Log(__FILE__, __LINE__, "Size (12b) : ", header.size, true);
            Log::CLog::Instance()->Log(__FILE__, __LINE__, "Time (12b) : ", header.mtime, true);
            Log::CLog::Instance()->Log(__FILE__, __LINE__, "Checksum : ", header.chksum, true);
            #endif
            #endif
            Ret=true;
        }

        return Ret;
    }


    bool CTarArchive::WriteData(const std::string& _input, const std::string& output)
    {
        bool Ret = false;

        /*int iAmountToRound = 0;
        static bool bFirstEntry = true;
        std::fstream f_In, f_Out;
        std::string strData = strTarfile;*/

        posix_header lheader;
        if(FillHeader(_input, lheader))
        {
            std::ofstream l_out(output.c_str(), std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);

            if(!l_out.good())
            {
                std::cerr << i8n("[ERR] Error output file: ") << output << '\n';
                Ret = false;
            }
            else
            {
                std::ifstream l_in(_input.c_str(), std::ios::in | std::ios::binary);

                if(!l_in.good())
                {
                    std::cerr << i8n("[WNG] Error in file: ") << _input << i8n(" (file is skipped)") << '\n';
                    Ret = true; // If we cannot read a file it's not vital, we skip, but we need to inform user !
                }
                else
                {
                    //Round it to % 512
                    if(m_FirstFile)
                    {
                        int l_AmountToRound = RoundTo512(l_out.tellp()) - l_out.tellp();

                        for(int i = 0; i < l_AmountToRound; ++i)
                            l_out.put('\0');
                    }

                    m_FirstFile = true;

                    //Write header
                    l_out.write(reinterpret_cast<char*>(&lheader), sizeof(lheader));

                    //Append file content
                    char l_char;
                    while(l_in.get(l_char))
                        l_out.put(l_char);

                    l_in.close();
                    l_out.close();
                    Ret = true;
                }
            }
        }
        else
        {
            std::cerr << i8n("[WNG] File '") << _input << i8n("' hasn't been add to tar archive !") << '\n';
            Ret = true; // If we cannot compute header, we skip it.
        }

        return Ret;
    }


    bool CTarArchive::CleanClose(const std::string& output)
    {
        bool Ret = false;

        std::ofstream l_out(output.c_str(), std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);

        if(!l_out.good())
        {
            std::cout << i8n("[ERR] Cannot open ") << output << i8n(" file!") << '\n';
            Ret = false;
        }
        else
        {
            int l_AmountToRound = RoundTo512(l_out.tellp()) - l_out.tellp();

            for(int i = 0; i < l_AmountToRound; ++i)
            {
                l_out.put('\0');
            }
            l_out.put('\0');
            l_out.put('\0');
            l_out.close();
            Ret = true;
        }
        return Ret;
    }


    bool CTarArchive::Create(std::list<std::string> filenames, const std::string& output, IProgressbar* callback)
    {
        bool Ret = false;
        std::list<std::string>::iterator It;
        int Size = filenames.size();
        int Done = 0;
        bool Error = false;
        bool Continue;

        for(It = filenames.begin(); It != filenames.end(); ++It)
        {
            ++Done;
            if(!WriteData(*It, output))
            {
                Error = true;
                break;
            }
            int Res = Done*50/Size;
            std::string Mess(i8n("Adding\n"));
            Mess += *It;
            Continue = callback->UpdateProgress(Mess, false, Res);
            if(!Continue)
                break;
            #if defined DEBUG && defined VERBOSE
            std::cout <<"[DBG] " <<  *It << i8n(" appended to ") << output << '\n';
            #endif
        }

        if(Error | !Continue)
        {
            unlink(output.c_str());
            if(Error)
                std::cout << i8n("[ERR] Due to error(s) on WriteData, I delete ") << output << '\n';
            else
                std::cout << i8n("[ERR] User cancel so I delete ") << output << '\n';
            Ret = false;
        }
        else
        {
            if(CleanClose(output))
                Ret = true;
            else
            {
                unlink(output.c_str());
                std::cerr << i8n("[ERR] Due to error(s) on CleanClose, I delete ") << output << '\n';
                Ret = false;
            }
        }

        if(Ret && Continue) //Delete files here
            if(Engine::CSettingsManager::Instance()->GetDelete())
                for(It = filenames.begin(); It != filenames.end(); ++It)
                {
                    #if defined DEBUG
                    Log::CLog::Instance()->Log(__FILE__, __LINE__, It->c_str());
                    Log::CLog::Instance()->Log(__FILE__, __LINE__, " deleted ! \n");
                    #endif
                    unlink(It->c_str());
                }
        return Ret;
    }


    //Simplify manipulation :
    std::string CTarArchive::itos(int _nb)
    {
        std::stringstream Ret;
        Ret << _nb;
        return Ret.str();
    }


    std::string CTarArchive::DecToOct(int _nb)
    {
        std::stringstream Ret;
        Ret << std::oct << _nb;
        return Ret.str();
    }


    std::string CTarArchive::PadWithZeros(std::string& _s, unsigned int _size)
    {
        std::string Ret;
        int Size = _size - 1;
        int l_padsize = Size - _s.size();

        if(_s.size() <= _size)
            for(int i = 0; i < l_padsize; ++i)
                Ret.append(1, '0');
        else
            return static_cast<std::string>(0);

        Ret.append(_s);

        return Ret;
    }


    int CTarArchive::RoundTo512(int n)
    {
        if(n % 512 == 0)
            return n;
        else
            return (n - (n % 512)) + 512;
    }
}

/* vi:set ts=4: */
