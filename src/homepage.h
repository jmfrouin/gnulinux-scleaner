/**
 * This file is part of scleaner project.

 * Copyright (C) 2007, 2008 FROUIN Jean-Michel

 * Visit scleaner website : http://www.scleaner.org
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

/*! @mainpage simple cleaner homepage
 *
 * Documentation homepage : http://www.scleaner.org
 *
 * Project homepage : https://savannah.nongnu.org/projects/scleaner/
 *
 * Development mailing list : https://savannah.nongnu.org/mail/?group=scleaner
 *
 * Get last version : http://download.savannah.nongnu.org/releases/scleaner/
 *
 * @section intro_whatis What is scleaner ?
 *
 * scleaner will be able to clean your GNU/Linux desktop (developped under Ubuntu 8.04) by removing for example all unwanted log, orphan or duplicate files ...
 *
 * It support plugins to allow developpers to add there own plugins. It is able to minimize in Tray.
 *
 * It use wxWidgets for frontend.
 *
 * It used this https://wiki.ubuntu.com/SystemCleanUpTool as guidelines for developpement and add some others ideas.
 *
 * Others very usefull ressources :
 *
 * http://www.commentcamarche.net/faq/sujet-7214-faire-le-menage-dans-ubuntu-residus-de-configuration-paquets
 *
 * http://doc.ubuntu-fr.org/maintenir_systeme
 * 
 * Kleansweep : http://linux.bydg.org/~yogin/
 * 
 * fslint : http://www.pixelbeat.org/fslint/
 * 
 * gtkorphan : http://www.pixelbeat.org/fslint/
 *
 * @section install Installation
 *
 * You can download the last version here : http://www.scleaner.org/ (get *.deb files)
 *
 *  @image html gfx/gpl.png
 */

/*! @page page3 Plugins documentations
 * Here you can find all plugins documentations.
 */

/*! @page page1 Successful platforms tested
 *
 * Ubuntu 8.04
 */

/*! @page page2 Inputs plugins to write
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
 *
 * .Trash folder plugins
 *
 * .thumbnail for browser stuff
 *
 * Plugin sur les par2 / rar avi
 *
 * *.ext~
 */

/*! @page page5 Output plugins to write
 *
 * based on hubackup / sbackup ?
 *
 * Burn to cd
 *
 * Copy to usbdisk ?
 *
 */

/*! @page page4 Build & Installation
 *
 * Please check INSTALL file for test scleaner.
 *
 */


/*! @page page4 Build & Installation
 *
 * Please check INSTALL file for test scleaner.
 *
 */

 /*! @page page5 Packaging
 * 
 * @section In order to package scleaner for debian distributions : 
 * 1 - clean build folder
 * 2 - If possible save snapshot from git
 * 2' - If not, cp scleaner ../scleaner-X.XX.XX 
 * 2'1 - clean this folder from all .git folders (using scleaner for that is highly recommanded)
 * 3 - we want to build debian package for version 0.70.1076 (Need to desactivate update_build.sh in CMakeLists.txt) 
 * 4 - cd scleaner-X.X.XX
 * 5 - dch -i 
 * 6 - cp debian/changelog /home/snoogie/dev/scleaner/debian/
 * 7 - dpkg-buildpackage -rfakeroot
 *
 */
