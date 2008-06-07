#include "timer.h"
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <def.h>

namespace Tools
{
  CTimer::CTimer()
  {
    Snap();
  }

  CTimer::CTimer(const unsigned long long msectime)
  {
    fTimeStamp = msectime;
  }

  CTimer::CTimer(const CTimer& t)
  {
    fTimeStamp = t.fTimeStamp;
  }

  CTimer::~CTimer(void)
  {
  }

  unsigned long long CTimer::TimeStamp()
  {
    return fTimeStamp;
  }

  void CTimer::Snap()
  {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    fTimeStamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    std::cout << ROUGE << "Timer : " << fTimeStamp << '\n' << STOP;
  }

} // namespace Tools

