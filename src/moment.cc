#include "moment.hh"
#include <cassert>
#include <sys/time.h>

Moment Moment::genesis((Moment *)0);


Moment::Moment(Moment *m)
 : _sec(0),
   _usec(0)
{
  assert(m == 0);
  struct timeval tv;
  gettimeofday(&tv,0);
  _sec = tv.tv_sec;
  _usec = tv.tv_usec;
}


Moment
Moment::now()
{
  Moment nowish((Moment *)0);
  return nowish -= genesis;
}
