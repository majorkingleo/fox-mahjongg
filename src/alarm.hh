#ifndef ALARM_HH
#define ALARM_HH
#include "moment.hh"

class Alarm;

class AlarmHooks {
  
 public:

  virtual ~AlarmHooks()			{ }
  
  virtual void alarm();
  virtual void alarm(Alarm *);
  
};

class Alarm {
  
  bool _dead;
  bool _scheduled;
  Moment _moment;
  AlarmHooks *_hook;
  Alarm *_next;
  
  static Alarm *alarms;
  void unschedule();
  
 public:
  
  Alarm()
  : _dead( false),
    _scheduled(0),
    _moment(),
    _hook(0),
    _next(0)
  { }

  Alarm(AlarmHooks *h)
  : _dead( false),
    _scheduled(0),
    _moment(),
    _hook(h),
    _next(0)
  { }

  Alarm( const Alarm & other ) = delete;
  Alarm & operator=( const Alarm & other ) = delete;

  ~Alarm()				{ if (_scheduled) unschedule(); }
  
  const Moment &moment() const		{ return _moment; }
  bool dead() const			{ return _dead || !_scheduled; }
  
  void schedule(const Moment &);
  void kill()				{ _dead = true; }
  
  static void x_wait();
  
};

#endif
