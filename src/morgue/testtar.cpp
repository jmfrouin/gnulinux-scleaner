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
#include <list>
#include <string>
#include "tar_archive.h"

int main()
{
  int Ret;
  CTarArchive l_tar;
  std::string l_1("test.txt");
  std::string l_2("test2.txt");
  std::list<std::string> l_list;
  l_list.push_back(l_1);
  l_list.push_back(l_2);
  bool res = l_tar.Create(l_list, "test.tar");
  if(res)
  {
    Ret = EXIT_SUCCESS;
  }
  else
  {
    Ret = EXIT_FAILURE;
  }
  return Ret;
}


/* vi:set ts=4: */
