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

#include <plugins/in/in_plugin_initializer.h>
#include "nullfiles.h"
#include <leak/leak_detector.h>
#include <engine/engine.h>

Plugins::CInPluginInitializer<CnullfilesPlugin> gNullFiles;

CnullfilesPlugin::CnullfilesPlugin()
{
  SetName("null files");
}


CnullfilesPlugin::~CnullfilesPlugin()
{
}


void CnullfilesPlugin::ProcessFile(const std::string& filename)
{
  struct stat Stat;

  //Try to stat file.
  if(stat(filename.c_str(), &Stat) == -1)
    std::cout << i8n("[ERR] : Cannot stat ") << filename << '\n';
  else
  if(!Stat.st_size)
    fFL.push_back(filename);
}


std::string CnullfilesPlugin::Description()
{
  return "Find empty file size";
}


/* vi:set ts=4: */
