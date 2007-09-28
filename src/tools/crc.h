/*
The CRC code was devised by Don P. Mitchell of AT&T Bell Laboratories
and Ned W. Rhodes of Software Systems Group. It has been published in
"Design and Validation of Computer Protocols", Prentice Hall,
Englewood Cliffs, NJ, 1991, Chapter 3, ISBN 0-13-539925-4.

Copyright is held by AT&T.

AT&T gives permission for the free use of the CRC source code.
 
Copyright (C) 1991 Don P. Mitchell of AT&T Bell Laboratories
Copyright (C) 1991 New W. Rhodes of Software Systems Group
Copyright (C) 1997 Andrew E. Mileski
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
$Date: 2007-09-27 20:34:37 +0200 (jeu, 27 sep 2007) $
$Rev: 132 $
$Author: snoogie $
------------------------------------------------------
*/

#ifndef _CRC_H_
#define _CRC_H_

/*!
*@brief Routines to generate, calculate, and test a 16-bit CRC.
*/
class CCRC
{
	public:

		/*!
		 *@brief Calculate a 16-bit CRC checksum using ITU-T V.41 polynomial. The OSTA-UDF(tm) 1.50 standard states that using CRCs is mandatory.The polynomial used is: x^16 + x^12 + x^15 + 1
		 *@param _data Pointer to the data block.
		 *@param _size Size of the data block.
		 *@param _crc  CRC of the data block.
		 */
		static void calc_UDF_CRC(unsigned int* _data, unsigned int _size, unsigned short& _crc);
		
};

#endif //_CRC_H_
