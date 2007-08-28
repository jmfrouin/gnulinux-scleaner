/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
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

#ifndef _IPLUGIN_H_
#define _IPLUGIN_H_

#include <config.h>
#include <string>
#include <list>
#include <tools/name.h>

/**
 * @brief Plugin Interface
 */
class IPlugin : public CName
{
	public:
		enum eType
		{
			eInput,
			eOutput
		};

    public:
		/*!
		 * @brief ctor
		 */
		IPlugin(){}

    	/*!
    	 * @brief dtor.
    	 */
    	virtual ~IPlugin(){}

		/*!
		*@brief Give a description of current plugin.
		*/
		virtual const std::string description() = 0;

		/*!
		*@brief Provide author information.
		*/
		virtual const std::string author() = 0;

		/*!
		*@brief Provide author information.
		*/
		virtual const std::string version() = 0;

		/*!
		*@brief This plugin is threadable ?
		*/
		virtual bool isThreadable()
		{
			bool l_ret = false;
			return l_ret;
		}

		/*!
		*@brief Input or output plugin ?
		*/
		virtual eType Type() = 0;
};
#endif                           //_IPLUGIN_H_
/* vi:set ts=4: */
