/* 
 Copyright (c) 2004-2005 Andrew Reading.
 Copyright (c) 2007 Sylvain Beucler.
 Copyright (c) 2007 Jean-Michel Frouin.
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
*/

#ifndef _TARLIB_H_
#define _TARLIB_H_

#include <string>
#include <iostream>

/*!
*@brief Tar library allow only to create GNU tar archive for the moment.
*/
class CTarLib
{
	public:
	/*!
	*@brief Compute file header.
	*@param _filename File name.
	*@return true on success, false otherwise.
	*@todo public -> private.
	*/
	bool computeFileHeader(const std::string& _filename);

	//inline
	std::string PadWithZeros(std::string& _s, int _size)
	{
		std::cout << "pad" << '\n';
	    std::string l_ret;
	    int l_size = _size - 1;
	    int l_padsize = l_size - _s.size();
	
	    if(_s.size() <= _size)
	    {
	        for(int i = 0; i < l_padsize; ++i)
	        {
	            l_ret.append(1, '0');
	        }
	    }
	    else
	    {
	        return static_cast<std::string>(0);
	    }
	
	    l_ret.append(_s);
	
	    return l_ret;
	}

};

#endif // _TARLIB_H_
/* vi:set ts=4: */
