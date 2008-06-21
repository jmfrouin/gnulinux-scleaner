#ifndef __NOTIF_H__
#define __NOTIF_H__

#include <string>
namespace Interface
{
  class CNotif
  {
    public:
      CNotif(const std::string& title, const std::string& content, int delay = 2000);
      ~CNotif();

      /*! 
        *@brief Display it
        */
      void Display();

    private:
      std::string fTitle;
      std::string fContent;
      int fDelay;
  };
}

#endif //__NOTIF_H__
