/*
 * main.h
 *
 *  Created on: 24.02.2022
 *      Author: martin
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#if defined WIN32 || defined _WIN32
#  include <windows.h>
#else
#  include <X11/Xlib.h>
#endif
#include "moment.hh"
#include "fx.h"
#include "game.hh"
#include <xmj3ts.hh>
#include <gmjts.hh>
#include <kdets.hh>
#include <kmjts.hh>
#include "tileset.hh"
#include <string>

// Main Window
class MahjonggWindow : public FXMainWindow {

	// Macro for class hierarchy declarations
	FXDECLARE(MahjonggWindow)

private:

	FXHorizontalFrame *contents;                // Content frame
	FXVerticalFrame   *canvasFrame;             // Canvas frame
	FXVerticalFrame   *buttonFrame;             // Button frame
	FXCanvas          *canvas;                  // Canvas to draw into
	int                mdflag;                  // Mouse button down?
	FXColor            drawColor;               // Color for the line
	// Ref<Level>         level;
	int                running;
	int                level_count;
	int                retry_count;
	FXLabel          *level_label;
	FXLabel          *retry_label;

	int               move_mode;

	Gif_XContext *gifx;
	Tileset *tileset;
	Pixmap background;
	Game *game;
	Moment last_new_board;
	bool solveable_boards;

protected:
	MahjonggWindow(){}

public:

	// Message handlers
	long onPaint(FXObject*,FXSelector,void*);
	long onMouseDown(FXObject*,FXSelector,void*);
	long onMouseMove(FXObject*,FXSelector,void*);
	long onCmdClear(FXObject*,FXSelector,void*);
	long onTimeout(FXObject*,FXSelector,void*);
	long openurl(FXObject*,FXSelector,void*);
	long onkeypress(FXObject*,FXSelector,void*);
	long onkeyrelease(FXObject*,FXSelector,void*);
	long onClose(FXObject*,FXSelector,void*);

	// void pause() { level->pause(); running = 0; move_mode = 0; }
	// void cont() { level->run(); running = 1; }
	// Ref<Level> get_next_level( bool force = false );

	// void autoRepeat(int state);

public:

	// Messages for our class
	enum{
		ID_CANVAS=FXMainWindow::ID_LAST,
		ID_CLEAR,
		ID_TIMER,
		ID_TITLE,
		ID_QUIT,
		ID_LAST
	};

public:

	// MahjonggWindow's constructor
	MahjonggWindow(FXApp* a);

	// Initialize
	virtual void create();

	const Moment & getLastNewBoard() const {
		return last_new_board;
	}

	void setLastNewBoard( const Moment & m ) {
		last_new_board = m;
	}

	bool getSolveableBoards() {
		return solveable_boards;
	}

	void setSolveableBoards( bool value ) {
		solveable_boards = value;
	}

private:
	Tileset *load_tileset(const char *tileset_name, const char *config_dir);
	Pixmap load_background(const char *background_name, const char *config_dir,Gif_XContext *gfx);

	void error( const std::string & error );
	void config_error( const std::string & error );
};



#endif /* SRC_MAIN_H_ */
