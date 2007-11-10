/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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
#include <plugins/plugin_initializer.h>
#include "orphan.h"
#include <leak/leak_detector.h>

CPluginInitializer<CorphanPlugin> g_orphan;

CorphanPlugin::CorphanPlugin()
{
	setName("orphan");
}


CorphanPlugin::~CorphanPlugin()
{
}


const std::string CorphanPlugin::location()
{
	return "/var/log/orphan.log";
}


const std::string CorphanPlugin::description()
{
	return "Application settings orphan cleaner";
}


bool CorphanPlugin::isThreadable()
{
	bool l_ret = true;
	return l_ret;
}


void CorphanPlugin::__Run()
{
	std::cout << "I am in the thread !!" << '\n';
	std::cout << "But I am very tired I ll sleep a bit !!" << '\n';
	usleep(500000);
	std::cout << "Ok ready to ... quit :) !!" << '\n';
	IThread::__End();
}


IPlugin::eType CorphanPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}


/* vi:set ts=4: */
