/**
 * This file is part of scleaner project.

 * Copyright (C) 2007 FROUIN Jean-Michel

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
#include "bz.h"

int main()
{
	int l_ret;
	CBZ l_bz;
	bool res = l_bz.Compress("backup.tar", "backup.tbz");
	if(res)
	{
		l_ret = EXIT_SUCCESS;
	}
	else
	{
		l_ret = EXIT_FAILURE;
	}
	return l_ret;
}


/* vi:set ts=4: */
