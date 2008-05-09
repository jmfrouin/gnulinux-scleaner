/**
 * This file is part of scleaner project.

 * Copyright (C) 2004-2005 Andrew Reading.
 * Copyright (C) 2007 Sylvain Beucler.
 * Visit scleaner website : http://www.scleaner.fr
 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

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

#include "tbz.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <fcntl.h>
#include <bzlib.h>
#include <sys/stat.h>            ///Get file size.
#include <wx/dir.h>
#include <tools/tar_archive.h>
#include <plugins/outplugin_initializer.h>
#include <leak/leak_detector.h>

Plugins::CPluginInitializerOut<CtbzPlugin> gTBZ;

CtbzPlugin::CtbzPlugin()
{
    SetName("tbz");
}


CtbzPlugin::~CtbzPlugin()
{
}


void CtbzPlugin::ProcessFileList(std::list<std::string>& fl, const std::string& path, IProgressbar* callback)
{
    Tools::CTarArchive Tar;

    std::string Date;
    Engine::CEngine::GetTimestamp(Date);

    if(Tar.Create(fl, path + "/backup_" + Date + ".tar" , callback))
    {
        if(Compress(path + "/backup_" + Date + ".tar" , path + "/backup_" + Date + ".tbz", callback))
        {
            std::string Del(path);
            Del += "/backup_" + Date + ".tar";
            unlink(Del.c_str());
        }
        else
        {
            std::cerr << i8n("[ERR] An error occured during compression so I left ") << path + "/backup_" + Date + ".tar" << '\n';
        }
    }
}


//Private methods
bool CtbzPlugin::Compress(const std::string& input, const std::string& output, IProgressbar* callback)
{
    bool Ret = false;
    FILE* Out = fopen(output.c_str(), "wb");

    // Open up the output file
    if(!Out)
    {
        std::cout << i8n("Error out file!") << '\n';
        Ret = false;
    }
    else
    {
        BZFILE* BZ = 0;
        int Err = 0;
        BZ = BZ2_bzWriteOpen(&Err, Out, 9, 0, 90);

        if(Err != BZ_OK)
        {
            std::cout << i8n("Error bzWriteOpen!") << '\n';
            Ret = false;
        }
        else
        {
            // Open up the input file
            std::ifstream In(input.c_str(), std::ios::in | std::ios::binary);

            if(!In.good())
            {
                std::cout << i8n("Error in file!") << '\n';
                Ret = false;
            }
            else
            {
                // Get the file size. (I hate C I/O, so don't use them :D )
                struct stat Info;
                double Total;
                //Try to stat file.
                if(stat(input.c_str(), &Info) == -1)
                {
                    std::cout << i8n("Cannot stat ") << input.c_str() << '\n';
                    Ret = false;
                }
                else
                {
                    char Buffer[4096];
                    memset(Buffer, 0, 4096);
                    Total = Info.st_size;
                    double Done = 0;
                    do
                    {
                        In.read(Buffer, 4096);
                        std::streamsize BytesRead = In.gcount();
                        Done += BytesRead;
                        int Result = static_cast<int>((Done*50)/Total)+50;
                        std::string Mess(i8n("bz2 compression of\n"));
                        std::stringstream DoneStr;
                        DoneStr << (Result-50)*2;
                        Mess += output + " :  " + DoneStr.str() + "%";
                        callback->UpdateProgress(Mess, false, Result);
                        BZ2_bzWrite(&Err, BZ, Buffer, BytesRead);
                    } while(In.good());

                    if( In.bad() || !In.eof() )
                        Ret = false;
                    else
                        Ret = true;

                    In.close();
                }

                // Close up.
                BZ2_bzWriteClose(&Err, BZ, 0, 0, 0);
                fclose(Out);
                Out = 0;
            }
        }
    }

    return Ret;
}


std::string CtbzPlugin::Description()
{
    return "Create a tar + bzip2 archive";
}
/* vi:set ts=4: */
