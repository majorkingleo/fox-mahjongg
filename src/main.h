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
#include <map>


class Panel;
class Gif_Stream;
class MatchCount;
class Button;
class FXPixelBuffer;

// Main Window
class MahjonggWindow : public FXMainWindow {

	// Macro for class hierarchy declarations
	FXDECLARE(MahjonggWindow)

private:

	FXHorizontalFrame *contents;                // Content frame
	FXVerticalFrame   *canvasFrame;             // Canvas frame
	FXVerticalFrame   *buttonFrame;             // Button frame
	FXPixelBuffer     *canvas;                  // Canvas to draw into
	int                mdflag;                  // Mouse button down?
	FXColor            drawColor;               // Color for the line
	int               move_mode;

	Tileset *tileset;
	FXImage* background;
	Game *game;
	Moment last_new_board;
	bool solveable_boards;
	Panel *panel;
	Gif_Stream *gifbuttons;
	MatchCount *matches;
	char *layout_name;
	std::string config_dir;

	std::map<std::string,FXImage *> imageByName;
    std::map<FXImage*,std::string> nameByImagePtr; // just for debugging

    FXTabBook *tabbook;
    FXTabItem *tab_main;
    FXTabItem *tab_debug;


protected:
	MahjonggWindow();
	~MahjonggWindow();

	MahjonggWindow( const MahjonggWindow & other ) = delete;
	MahjonggWindow & operator=( const MahjonggWindow & other ) = delete;

public:

	// Message handlers
	long onMouseDown(FXObject*,FXSelector,void*);
	long onMouseUp(FXObject*,FXSelector,void*);
	long onTimeout(FXObject*,FXSelector,void*);
	long onClose(FXObject*,FXSelector,void*);

	void detach() override;
	void layout() override;

public:

	// Messages for our class
	enum{
		ID_CANVAS=FXMainWindow::ID_LAST,
		ID_TIMER,
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

	FXImage *getImageByName( const std::string & image );

    std::string getNameByImage( FXImage *img ) const {
        auto it = nameByImagePtr.find( img );

        if( it == nameByImagePtr.end() ) {
            return "unknown";
        }

        return it->second;
    }

    void registerNameByImage( FXImage *img, const std::string & name ) {
        nameByImagePtr[img] = name;
    }

private:
	Tileset *load_tileset(const char *tileset_name, const char *config_dir);
	FXImage* load_background(const char *background_name, const char *config_dir );

	void error( const std::string & error );
	void config_error( const std::string & error );

	void make_panel_images(Panel *p);
	Button* new_button(Panel *panel, const char *name);

	void loadButtonImages();
	void loadDigitImages();
	FXImage* createGifImage( const unsigned char* data, const std::string & name );
};



#endif /* SRC_MAIN_H_ */
