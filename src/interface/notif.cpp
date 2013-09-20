/**
 * This file is part of scleaner project.

 * Copyright (C) 2008 FROUIN Jean-Michel

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

#include "notif.h"
//#include <libnotify/notify.h>
#include <iostream>

namespace Interface
{
  CNotif::CNotif(const std::string& title, const std::string& content, int delay):
  fTitle(title), fContent(content), fDelay(delay)
  {
  }

  CNotif::~CNotif()
  {
  }

  void CNotif::Display()
  {
    //NotifyNotification* Notif;
    //notify_init("fun");
    //Notif = notify_notification_new(fTitle.c_str(), fContent.c_str(), 0, 0);
    //notify_notification_set_timeout(Notif, fDelay); //2s
    //if (!notify_notification_show (Notif, 0))
    //  std::cerr << "[ERR] Failed to send notification\n";
    //else
    //  g_object_unref(G_OBJECT(Notif));
  }
}
