#include <iostream>
#include "tarlib.h"

int main()
{
	CTarLib l_tar;
	l_tar.computeFileHeader("test.txt");
	return EXIT_SUCCESS;
}
/* vi:set ts=4: */
