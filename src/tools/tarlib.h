#ifndef _TARLIB_H_
#define _TARLIB_H_

#include <string>

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
};

#endif // _TARLIB_H_
/* vi:set ts=4: */
