/*
Copyright (C) 2007 FROUIN Jean-Michel (jmfrouin@gmail.com)
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
$Date$
$Rev$
$Author$
------------------------------------------------------

*/

/*! @mainpage Simple Cleaner homepage
 *
 * $Date$
 *
 * $Rev$
 *
 * <center>Documentation homepage : http://www.scleaner.net
 *
 * Project homepage : https://savannah.nongnu.org/projects/scleaner/ </center>
 *
 * @section intro_history Version history (what's new)
 * v0.25.0:
 * @li CHANGELOG added :D
 * @li Replace Panel for plugin information with an HTML form.
 * @li Toolbar works.
 * @li Add a splash screen.
 * @li Preparation for i8n.
 *
 * v0.2:
 * @li Adding GFX interface.
 * @li Adding CEngine which will deals with CLI and GUI.
 *
 * v0.1:
 * @li Initial version.
 *
 * @section intro_whatis What is scleaner ?
 *
 * scleaner will be able to clean your GNU/Linux desktop (developped under Ubuntu 7.04 Feisty) by removing for example all unwanted log, orphan or duplicate files ...
 *
 * It support plugins to allow developpers to add there own plugins. It is able to minimize in Tray.
 * 
 * It use wxWidgets for frontend.
 * 
 * It used this https://wiki.ubuntu.com/SystemCleanUpTool as guidelines for developpement and add some others ideas.
 * @section install Installation
 *
 * Not yet implemented
 *
 * @section screenshots Screenshots
 *
 *  @image html gfx/scleaner0.25.0.png
 *
 *
 *
 *  @image html gfx/gpl.png
 *
 */

 /*! @page page3 Plugins documentations
 * Here you can find all plugins documentations.
 */

 /*! @page page1 Improvement
 *
 * @section error Error code
 *
 * Can be nice to centralise all error code in a .h file include by config.h or def.h.
 *
 * @section info Write an system info object
 *
 * man 2 uname (useful to get current used kernel version, to clean all unusued kernel)
 */

 /*! @page page2 Plugins to write
 *
 * Empty file
 *
 * Empty folder
 * 
 * .app orphan folder 
 *
 * duplicate files : use MD5 SUM to identify them.
 *
 * broken symlink
 *
 * broken executable
 *
 * make clean
 *
 * .thumbnail
 * 
 * Unused and old kernel package
 *
 * Orphans
 */

/*! @page page4 Build & Installation
* 
* Please check INSTALL file for test scleaner 0.2.0.
*
*/

/* vi:set ts=4: */

