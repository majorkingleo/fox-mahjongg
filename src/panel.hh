#ifndef PANEL_HH
#define PANEL_HH

#include "swgeneral.hh"
class Tileset;
class Button;
class Hint;
class Tile;
class Game;
class Board;
class MatchCount;
class FancyCounter;
class SolutionDisplay;
class Traversal;
class MahjonggWindow;

class Panel: public SwClippedWindow {

  bool _visible;
  
  short _window_width;
  short _window_height;
  
  Board *_board;
  FXImage *_background;
  FancyCounter *_tile_count;
  MatchCount *_match_count;
  SolutionDisplay *_solution;
  Traversal *_traversal;
  
  short _scan_mark_x;
  short _scan_mark_y;

  int _redraw_left;
  int _redraw_top;
  int _redraw_right;
  int _redraw_bottom;
  bool _need_redraw;
  
  enum Command {
    comNone,
    comHint,
    comUndo,
    comRedo,
    comNew,
    comQuit,
    comClean,
    comSolve,
    comDeselect,
    comCheckSolve,
  };
  enum TraversalCommand {
    comTravLeft  = 0,
    comTravRight = 1,
    comTravUp    = 2,
    comTravDown  = 3,
    comTravAnchor,
    comTravTake,
  };
  
  void tile_command(Game *, Tile *);
  void command(Game *, Command, Button *, bool, FXuint = 0);
  void traversal_command(Game *, TraversalCommand);
  void traversal_take_command(Game *, bool);
  
 public:
  
  Button *new_but;
  Button *undo_but;
  Button *quit_but;
  Button *hint_but;
  Button *clean_but;
  
 public:
  
  Panel(FXApp *app, FXPixelBuffer *window, MahjonggWindow *parent );
  
  Panel( const Panel & other ) = delete;
  Panel & operator=( const Panel & other ) = delete;

  Board *board() const				{ return _board; }
  void set_board(Board *);
  void set_background(FXImage *background);
  void set_tile_count(FancyCounter *);
  void set_match_count(MatchCount *);
  void set_solution(SolutionDisplay *);
  
  // drawing and beeping
  bool visible() const				{ return _visible; }
  void invalidate(int x, int y, int w, int h);
  void redraw();
  void redraw_all();
  
  // scan
  void scan_mark(int, int);
  void scan_dragto(int, int);
  
  void draw_controls();
  
  void bell() const;
  void flush() const {}
  
  // events
  void key_press(Game *, FXint key, FXint state);
  void click(Game *, int, int, FXint state, FXuint when, bool mouseUp );
  
  void set_visible( bool state ) {
	  _visible = state;
  }

  void resize(int, int);

};

#endif
