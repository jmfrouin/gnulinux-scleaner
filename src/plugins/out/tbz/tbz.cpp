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

#include "tbz.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <fcntl.h>
#include <bzlib.h>
#include <sys/stat.h>			 ///Get file size.
#include <wx/dir.h>
#include <tools/tar_archive.h>
#include <plugins/outplugin_initializer.h>
#include <leak/leak_detector.h>

Plugins::CPluginInitializerOut<CtbzPlugin> g_tbz;

CtbzPlugin::CtbzPlugin()
{
	setName("tbz");
}


CtbzPlugin::~CtbzPlugin()
{
}


void CtbzPlugin::processFileList(std::list<std::string>& _fl, const std::string& _path, IProgressbar* _callback)
{
	Tools::CTarArchive l_tar;

	std::string l_date;
	Engine::CEngine::getTimestamp(l_date);

	if(l_tar.Create(_fl, _path + "/backup_" + l_date + ".tar" , _callback))
	{
		if(Compress(_path + "/backup_" + l_date + ".tar" , _path + "/backup_" + l_date + ".tbz", _callback))
		{
			std::string l_del(_path);
			l_del += "/backup_" + l_date + ".tar";
			unlink(l_del.c_str());
		}
		else
		{
			std::cerr << i8n("[ERR] An error occured during compression so I left ") << _path + "/backup_" + l_date + ".tar" << '\n';
		}
	}
}


Plugins::IPlugin::eType CtbzPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}


//Private methods
bool CtbzPlugin::Compress(const std::string& _input, const std::string& _output, IProgressbar* _callback)
{
	bool l_ret = false;
	FILE* l_out = fopen(_output.c_str(), "wb");

	// Open up the output file
	if(!l_out)
	{
		std::cout << i8n("Error out file!") << '\n';
		l_ret = false;
	}
	else
	{
		BZFILE* l_bz = 0;
		int l_err = 0;
		l_bz = BZ2_bzWriteOpen(&l_err, l_out, 9, 0, 90);

		if(l_err != BZ_OK)
		{
			std::cout << i8n("Error bzWriteOpen!") << '\n';
			l_ret = false;
		}
		else
		{
			// Open up the input file
			std::ifstream l_in(_input.c_str(), std::ios::in | std::ios::binary);

			if(!l_in.good())
			{
				std::cout << i8n("Error in file!") << '\n';
				l_ret = false;
			}
			else
			{
				// Get the file size. (I hate C I/O, so don't use them :D )
				struct stat l_info;
				double l_total;
				//Try to stat file.
				if(stat(_input.c_str(), &l_info) == -1)
				{
					std::cout << i8n("Cannot stat ") << _input.c_str() << '\n';
					l_ret = false;
				}
				else
				{
					char l_buf[4096];
					memset(l_buf, 0, 4096);
					l_total = l_info.st_size;
					double l_done = 0;
					do
					{
						l_in.read(l_buf, 4096);
						std::streamsize l_bytesread = l_in.gcount();
						l_done += l_bytesread;
						int l_res = static_cast<int>((l_done*50)/l_total)+50;
						std::string l_mess(i8n("bz2 compression of\n"));
						std::stringstream l_doneStr;
						l_doneStr << (l_res-50)*2;
						l_mess += _output + " :  " + l_doneStr.str() + "%";
						_callback->updateProgress(l_mess, false, l_res);
						BZ2_bzWrite(&l_err, l_bz, l_buf, l_bytesread);
					} while(l_in.good());

					if( l_in.bad() || !l_in.eof() )
					{
						l_ret = false;
					}
					else
					{
						l_ret = true;
					}

					l_in.close();
				}

				// Close up.
				BZ2_bzWriteClose(&l_err, l_bz, 0, 0, 0);
				fclose(l_out);
				l_out = 0;
			}
		}
	}

	return l_ret;
}


/* vi:set ts=4: */
