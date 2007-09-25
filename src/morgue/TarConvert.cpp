// Misc Conversion functions for both Extraction and Compilation.
//
// DFArc
//
// Copyright (c) 2004-2005 Andrew Reading.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, this list of conditions
// and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, this list of
// conditions and the following disclaimer in the documentation and/or other materials provided with the
// distribution.
//    * Redistributions in any form must be accompanied by information on how to obtain complete source
// code for the DB software and any accompanying software that uses the DB software. The source code
// must either be included in the distribution or be available for no more than the cost of distribution
// plus a nominal fee, and must be freely redistributable under reasonable conditions. For an executable
// file, complete source code means the source code for all modules it contains. It does not include
// source code for modules or files that typically accompany the major components of the operating
// system on which the executable file runs.
//    * The files produced by DFArc are not subject to this license but instead any licensing terms
// provided inside said files.
//
// THIS SOFTWARE IS PROVIDED BY SLEEPYCAT SOFTWARE ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT, ARE DISCLAIMED. IN NO EVENT SHALL SLEEPYCAT SOFTWARE BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "includes/dfarc.hpp"

///////////////////////////
// CONVENIENCE FUNCTIONS //
///////////////////////////

//
// class CTar, std::string DecToOct(int n)
//
// PURPOSE: Convert n to octal.
// RETURNS: The string of the octal number.
//
std::string CTar::DecToOct(int n)
{
	std::stringstream ss;

	ss.clear();
	ss << std::oct << n;

	return ss.str();
}


//
// class CTar, std::string OctToDec(int n)
//
// PURPOSE: Convert n from Octal to Decimal.
// RETURNS: The string of the decimal number.
//
std::string CTar::OctToDec(int n)
{
	int iN = n;
	int iPlace = 0, iDigit = 0;
	double dResult = 0;

	while(iN > 0)
	{
		// Take the ones digit.
		iDigit = iN % 10;

		// Get rid of the last digit.
		iN /= 10;

		// Add it to the total. (8^Pos * digit).
		dResult += iDigit * pow(static_cast<double>(8), static_cast<double>(iPlace));

		// Move the place forward.
		iPlace++;
	}

	return ToString(static_cast<int>(dResult));
}


//
// class CTar, std::string ToString(int n)
//
// PURPOSE: Convert an int to a string.
// RETURNS: The string.
//
std::string CTar::ToString(int n)
{
	std::ostringstream ss;

	ss << n;

	return ss.str();
}


//
// class CTar, int RountTo512(int n)
//
// PURPOSE: Moves the number to the nearest multiple of 512.
// RETURNS: The new number.
//
int CTar::RoundTo512(int n)
{
	if(n % 512 == 0)
	{
		return n;
	}
	else
	{
		return (n - (n % 512)) + 512;
	}
}


//////////////////////
// String Functions //
//////////////////////

//
// class CTar, void PrependString(std::vector<std::string> &FileList, const char *szString)
//
// PURPOSE: Adds a preceeding string (path) to each entry in the list.
// RETURNS: Nothing.
//
void CTar::PrependString(std::vector<std::string> &FileList, const char *szString)
{
	std::string strStr = szString;
	strStr.append(1, '/');

	for(unsigned int i = 0; i < FileList.size(); ++i)
	{
		FileList.at(i).insert(0, strStr);
	}

	strPrefix = strStr;
}


//
// class CTar, std::string PadWithZeros(std::string &s, int iAcheiveSize)
//
// PURPOSE: Pads the left side of the string with zeroes to achieve the size of iAcheiveSize.
// RETURNS: The padded string.
//
std::string CTar::PadWithZeros(std::string &s, int iAcheiveSize)
{
	std::string str;
	int iSize = iAcheiveSize - 1;
	int iPadSize = iSize - s.size();

	if(s.size() <= iSize)
	{
		for(int i = 0; i < iPadSize; i++)
		{
			str.append(1, '0');
		}
	}
	else
	{
		// Crash it so we don't seriously screw up the file and think it's the
		// tar algorithm.
		return static_cast<std::string>(0);
	}

	str.append(s);

	return str;
}


////////////////////
// Tar Operations //
////////////////////

//
// class CTar, bool VerifyChecksum(TarHeader *Header)
//
// PURPOSE: Ensures the internal Header checksum is valid.
// RETURNS: True if valid.
//          False otherwise.
bool CTar::VerifyChecksum(TarHeader *Header)
{
	char *CheckRecord = 0;
	int iChksum = 0;
	std::string strPreChksum = Header->Chksum;

	// Checksum is counted as if it was blank.  Let's back it up and clear it.
	memset(Header->Chksum, 0, sizeof(Header->Chksum));

	// Prepare the incrementor.
	CheckRecord = reinterpret_cast<char*>(Header);

	// Find the checksum.
	for(CheckRecord; (CheckRecord - reinterpret_cast<char*>(Header)) < 512; ++CheckRecord)
	{
		iChksum += static_cast<int>(*CheckRecord);
	}

	// Add 256 (2^8)
	iChksum += 256;

	std::string strChksum = DecToOct(iChksum);

	if(atoi(strChksum.c_str()) == atoi(strChksum.c_str()))
	{
		return true;
	}

	return false;
}
