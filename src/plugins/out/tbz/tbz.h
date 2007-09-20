/*
 Copyright (C) 2004-2005 Andrew Reading.
 Copyright (C) 2007 Sylvain Beucler.
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

/*! @page page3 Plugins documentations.
* - @subpage tbz
*/

/*! @page tbz tbz: output plugin.
* @section desc Description
* This plugin allow user to create a <b>tarball</b> with all selected files from input plugins. Then it will compress it using <b>bzip2</b>.
* <br>
* @section param Parameters
* @section pb Knows bugs
* @section todo Todo
*/

#ifndef _TBZ_H_
#define _TBZ_H_

#include <config.h>
#include <plugins/out_plugin.h>

class CtbzPlugin : public IOutPlugin
{
    public:
        CtbzPlugin();
        ~CtbzPlugin();

		/*!
		*@brief From IPlugin.
		*/
		void processFileList(std::list<std::string>& _fl);
		const std::string description();
		const std::string author();
		const std::string version();
		eType Type();
	
	private:
		/*!
		*@brief Compress a file using bz algo.
		*@param _input Input file name.
		*@param _output Output file name.
		*@return true on success, false otherwise.
		*/
		bool Compress(const std::string& _input, const std::string& _output);
};
#endif                           //_TBZ_H_
/* vi:set ts=4: */
