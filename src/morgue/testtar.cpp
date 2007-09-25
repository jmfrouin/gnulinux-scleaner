#include <iostream>
#include <list>
#include <string>
#include "tar_archive.h"

int main()
{
	int l_ret;
	CTarArchive l_tar;
	std::string l_1("test.txt");
	std::string l_2("test2.txt");
	std::list<std::string> l_list;
	l_list.push_back(l_1);
	l_list.push_back(l_2);
	bool res = l_tar.Create(l_list, "test.tar");
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
