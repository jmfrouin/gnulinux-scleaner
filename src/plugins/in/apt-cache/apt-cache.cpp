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

#include "apt-cache.h"

#include <iostream>

#include <plugins/in/in_plugin_initializer.h>
#include <leak/leak_detector.h>

Plugins::CInPluginInitializer<Capt_cachePlugin> gAptCache;

Capt_cachePlugin::Capt_cachePlugin()
{
  SetName("apt cache");
}


Capt_cachePlugin::~Capt_cachePlugin()
{
}


std::string Capt_cachePlugin::Description()
{
  return "Find apt cache archives";
}


void Capt_cachePlugin::Run()
{
  while(fRunning)
  {
    std::cout << "Blob\n";
    fRunning = false;
  }
}


/* vi:set ts=4: */
