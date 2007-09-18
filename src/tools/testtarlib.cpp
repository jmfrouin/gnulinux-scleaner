#include <iostream>
#include "tarlib.h"

int main()
{
	CTarLib l_tar;
	l_tar.computeFileHeader("test.txt");
	l_tar.computeFileHeader("test");
	return EXIT_SUCCESS;
}
/* vi:set ts=4: */
