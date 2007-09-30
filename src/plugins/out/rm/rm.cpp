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
$Date: 2007-09-30 00:35:53 +0200 (dim, 30 sep 2007) $
$Rev: 144 $
$Author: snoogie $
------------------------------------------------------
*/

#include "rm.h"
#include <plugins/outplugin_initializer.h>
#include <leak/leak_detector.h>

CPluginInitializerOut<CrmPlugin> g_rm;

CrmPlugin::CrmPlugin()
{
	setName("rm");
}


CrmPlugin::~CrmPlugin()
{
}


void CrmPlugin::processFileList(std::list<std::string>& _fl, const std::string& _path, IProgressbar* _callback)
{
	std::list<std::string>::iterator l_it;
	int l_size = _fl.size();
	int l_done = 0;
	for(l_it = _fl.begin(); l_it != _fl.end(); ++l_it)
	{
		//unlink((*l_it).c_str());
		std::cout << (*l_it).c_str() << '\n';

		int l_res = l_done*100/l_size;
		_callback->updateProgress((*l_it), false, l_res);
	}
}


IPlugin::eType CrmPlugin::Type()
{
	eType l_ret;
	l_ret = eInput;
	return l_ret;
}


/* vi:set ts=4: */
