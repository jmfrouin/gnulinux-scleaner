wxWidgets CMake Modules and Template
v1.06 2006-03-27
By Jerry Fath 2005-2006
Based on work by Jorgen Bodde

Introduction
------------
The files in this package will help you get started using CMake with wxWidgets based applications.

Installation
------------
1) Download the correct CMake version for your platform from http://www.cmake.org
2) Install CMake according to the instructions provided
3) Copy the FindwxW.cmake and UsesxW.cmake files from this package to [cmakeinstalldir]/Modules
4) Copy the CMakeListsTPL.txt file to your project source directory and rename it to CMakeLists.txt
5) Edit CMakeLists.txt to provide information about your project's source files, include directories, etc.
6) Set the WXWIN environment variable to point to the wxWidgets base installation path (eg set WXWIN=c:/wxWidgets)
7) If you're running under Linux, set the WXWINCFG environment variable to the name of the active build directory
   in the wxWidgets directory (eg export WXWINCFG=buildgtk).  The active build directory is the desired build specific
   directory you created when bulding wxWidgets.  The wxWidgets build you specify using WXWINCFG is the configuration
   that will be used when compiling and linking your application.
8) Run CMakeSetup or ccmake as described in the CMake documentation to configure and generate a makefile or project.

Notes
-----
This package has been tested for Win32 and Linux builds.  Slight modifications may be necessary for OSX and others.
