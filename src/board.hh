#ifndef BOARD_HH
#define BOARD_HH

#include "game.hh"
#include "panel.hh"
#include "swwidget.hh"
#include "tile.hh"

class Hint;

class Board: public GameHooks, public SwWidget {
  
  Panel *_panel;
  Game *_game;
  Tileset *_tileset;
  bool _redraw_live;
  
  short _layout_x;
  short _layout_y;
  short _topmost_tile;
  short _botmost_tile;
  short _leftmost_tile;
  short _rightmost_tile;
  
  short _tile_width;
  short _tile_height;
  short _tile_xborder;
  short _tile_yborder;
  short _tile_shadow;
  Vector<short> _tile_flags;
  
  Tile *_masking_tile;
  Tile *_selected;
  
  Hint *_hint;
  
  Vector<Tile *> _display_order;

  void display_order_dfs(Game *, Tile *);
  
  void copy_buffer();
  void buffer_on(int x, int y);
  void buffer_off();

  void mark_mask_used(int);
  int lru_mask() const;

  void mark_around(Tile *, bool up, bool down);
  void draw_neighborhood(Tile *, int);
  
 public:
  
  enum TileFlag {
    fLit = 1,
    fKeepLit = 2,
  };
  
  Board( const Board & other ) = delete;
  Board & operator=( const Board & other ) = delete;

  Board(Panel *, Game *, Tileset *);
  virtual ~Board();

  Game *game() const				{ return _game; }
  
  int topmost_tile_y() const;
  void tile_layout_size(int *, int *) const;
    
  void set_tileset(Tileset *);
  void set_background(FXImage *background);
  void center_layout();
  
  void position(Tile *, short *x, short *y) const;
  void unposition(int x, int y, short *r, short *c) const;
  Tile *find_tile(short, short) const;
  
  // should be in a common widget structure
  void move(int, int);

  void set_tile_flag(Tile *, TileFlag, bool);
  bool tile_flag(Tile *, TileFlag) const;
  
  void light(Tile *t)				{ set_lit(t, true); }
  void unlight(Tile *t)				{ set_lit(t, false); }
  void set_lit(Tile *, bool);
  bool lit(Tile *t) const;
  
  void draw(Tile *);
  void draw_area(short rowtop, short colleft, short rowbot, short colright);
  void draw_marked();
  void draw_background();
  
  void draw_subimage(FXImage *source, FXBitmap *mask, int, int, int, int, int, int) override;
  
  void bell()					{ _panel->bell(); }
  void flush()					{ _panel->flush(); }
  
  Tile *selected() const			{ return _selected; }
  void select(Tile *);
  void deselect();
  
  void clear_traversal();
  Tile *traverse(int);
  
  Hint *hint() const				{ return _hint; }
  
  void layout_hook(Game *);
  void start_hook(Game *);
  void add_tile_hook(Game *, Tile *);
  void remove_tile_hook(Game *, Tile *);
  
};


#endif
