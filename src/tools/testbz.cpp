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
