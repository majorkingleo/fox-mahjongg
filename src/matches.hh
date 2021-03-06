#ifndef MATCHES_HH
#define MATCHES_HH

#include "swwidget.hh"
#include "game.hh"
#include <vector>

class MatchCount: public SwWidget, public GameHooks {

  Game *_game;
  
  FXImage* _one_image;
  std::vector<FXPixelBufferObject*> _objects;

  int _one_width;
  int _one_height;

  int _count;
  
  void draw(int, bool fast_display);
  
 public:
  
  MatchCount(SwWindow *, const char *);
  
  MatchCount( const MatchCount & other ) = delete;
  MatchCount & operator=( const MatchCount & other ) = delete;

  void set_game(Game *);
  
  void change(int m)				{ draw(m, true); }
  void draw()					{ draw(_count, false); }
  
  void start_hook(Game *);
  void move_made_hook(Game *);
  
};

#endif
