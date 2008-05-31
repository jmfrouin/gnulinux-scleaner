/**
 * This file is part of scleaner project.

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


#include <iostream>
#include <plugins/in/inplugin_initializer.h>
#include "backupextensions.h"
#include <sys/stat.h>            ///Get file size.
#include <leak/leak_detector.h>
#include <engine/engine.h>

Plugins::CPluginInitializerIn<CbackupextensionsPlugin> gCrimosoft;

CbackupextensionsPlugin::CbackupextensionsPlugin()
{
    SetName("backupextensions");
}


CbackupextensionsPlugin::~CbackupextensionsPlugin()
{
}


void CbackupextensionsPlugin::ProcessFile(const std::string& filename)
{
    if((filename.find("~",0) == (filename.length()-1)) ||
        (filename.find(".$$$",0) == (filename.length()-4)) ||
        (filename.find(".$db",0) == (filename.length()-4)) ||
        (filename.find(".001",0) == (filename.length()-4)) ||
        (filename.find(".001",0) == (filename.length()-4)) ||
        (filename.find(".113",0) == (filename.length()-4)) ||
        (filename.find(".abbu",0) == (filename.length()-5)) ||
        (filename.find(".abk",0) == (filename.length()-4)) ||
        (filename.find(".bac",0) == (filename.length()-4)) ||
        (filename.find(".backupdb",0) == (filename.length()-9)) ||
        (filename.find(".bak",0) == (filename.length()-4)) ||
        (filename.find(".bck",0) == (filename.length()-4)) ||
        (filename.find(".bck",0) == (filename.length()-4)) ||
        (filename.find(".bcm",0) == (filename.length()-4)) ||
        (filename.find(".bdb",0) == (filename.length()-4)) ||
        (filename.find(".bkc",0) == (filename.length()-4)) ||
        (filename.find(".bkf",0) == (filename.length()-4)) ||
        (filename.find(".bkp",0) == (filename.length()-4)) ||
        (filename.find(".bks",0) == (filename.length()-4)) ||
        (filename.find(".bps",0) == (filename.length()-4)) ||
        (filename.find(".bup",0) == (filename.length()-4)) ||
        (filename.find(".bup",0) == (filename.length()-4)) ||
        (filename.find(".cbk",0) == (filename.length()-4)) ||
        (filename.find(".da0",0) == (filename.length()-4)) ||
        (filename.find(".dbk",0) == (filename.length()-4)) ||
        (filename.find(".dov",0) == (filename.length()-4)) ||
        (filename.find(".fbf",0) == (filename.length()-4)) ||
        (filename.find(".fbk",0) == (filename.length()-4)) ||
        (filename.find(".ful",0) == (filename.length()-4)) ||
        (filename.find(".gb1",0) == (filename.length()-4)) ||
        (filename.find(".gho",0) == (filename.length()-4)) ||
        (filename.find(".iv2i",0) == (filename.length()-5)) ||
        (filename.find(".jbk",0) == (filename.length()-4)) ||
        (filename.find(".llx",0) == (filename.length()-4)) ||
        (filename.find(".mem",0) == (filename.length()-4)) ||
        (filename.find(".nb7",0) == (filename.length()-4)) ||
        (filename.find(".nbk",0) == (filename.length()-4)) ||
        (filename.find(".nco",0) == (filename.length()-4)) ||
        (filename.find(".nrs",0) == (filename.length()-4)) ||
        (filename.find(".oeb",0) == (filename.length()-4)) ||
        (filename.find(".old",0) == (filename.length()-4)) ||
        (filename.find(".ori",0) == (filename.length()-4)) ||
        (filename.find(".oyx",0) == (filename.length()-4)) ||
        (filename.find(".paq",0) == (filename.length()-4)) ||
        (filename.find(".qbb",0) == (filename.length()-4)) ||
        (filename.find(".qbx",0) == (filename.length()-4)) ||
        (filename.find(".qic",0) == (filename.length()-4)) ||
        (filename.find(".rbc",0) == (filename.length()-4)) ||
        (filename.find(".rbf",0) == (filename.length()-4)) ||
        (filename.find(".rbk",0) == (filename.length()-4)) ||
        (filename.find(".rdb",0) == (filename.length()-4)) ||
        (filename.find(".rrr",0) == (filename.length()-4)) ||
        (filename.find(".skb",0) == (filename.length()-4)) ||
        (filename.find(".spg",0) == (filename.length()-4)) ||
        (filename.find(".sqb",0) == (filename.length()-4)) ||
        (filename.find(".tbk",0) == (filename.length()-4)) ||
        (filename.find(".tmp",0) == (filename.length()-4)) ||
        (filename.find(".uci",0) == (filename.length()-4)) ||
        (filename.find(".v2i",0) == (filename.length()-4)) ||
        (filename.find(".win",0) == (filename.length()-4)) ||
        (filename.find(".win",0) == (filename.length()-4)) ||
        (filename.find(".xlk",0) == (filename.length()-4)))
        fFL.push_back(filename);
}


std::string CbackupextensionsPlugin::Description()
{
    return "Find various backup files";
}
/* vi:set ts=4: */
