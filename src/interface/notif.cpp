#include "notif.h"
#include <libnotify/notify.h>
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
    NotifyNotification* Notif;
    notify_init("fun");
    Notif = notify_notification_new(fTitle.c_str(), fContent.c_str(), 0, 0);
    notify_notification_set_timeout(Notif, fDelay); //2s
    if (!notify_notification_show (Notif, 0))
      std::cerr << "[ERR] Failed to send notification\n";
    else
      g_object_unref(G_OBJECT(Notif));
  }
}
