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
#include "tileset.hh"
#include <string>
#include <map>
#include <set>


class Panel;
class Gif_Stream;
class MatchCount;
class Button;
class FXPixelBuffer;
class FXRadioGroup;

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

    FXMenuBar *menubar;
    FXIcon *icon_xmahjongg;

    FXMenuRadio *mc_background_default;
    FXMenuRadio *mc_background_green;
    FXMenuRadio *mc_background_blue;
    FXMenuRadio *mc_background_user_image;
    FXMenuRadio *mc_background_user_image_dir;

    std::string background_name;
    std::string last_file_open_path;
    std::string background_image_name;
    std::string background_image_path;

    std::set<std::string> known_image_extensions;

    FXRadioGroup *radio_group_background_image;


    FXMenuRadio *mc_tileset_thick;
    FXMenuRadio *mc_tileset_thin;
    FXMenuRadio *mc_tileset_small;
    FXMenuRadio *mc_tileset_gnome;
    FXMenuRadio *mc_tileset_gnome2;
    FXMenuRadio *mc_tileset_dorwhite;

    FXRadioGroup *radio_group_tileset;

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
	long onKeypress(FXObject*,FXSelector,void*);
	long onChangeBackgroundDefault(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeBackgroundGreen(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeBackgroundBlue(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeBackgroundUserImage(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeBackgroundUserImageDir(FXObject* obj,FXSelector sel,void* ptr);

	long onChangeTilesetThick(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeTilesetThin(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeTilesetSmall(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeTilesetGnome(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeTilesetGnome2(FXObject* obj,FXSelector sel,void* ptr);
	long onChangeTilesetDorwhite(FXObject* obj,FXSelector sel,void* ptr);

	void detach() override;
	void layout() override;

	FXbool close(FXbool notify) override;

public:

	// Messages for our class
	enum{
		ID_CANVAS=FXMainWindow::ID_LAST,
		ID_TIMER,
		ID_BACKGROUND_DEFAULT,
		ID_BACKGROUND_GREEN,
		ID_BACKGROUND_BLUE,
		ID_BACKGROUND_USER_IMAGE,
		ID_BACKGROUND_USER_IMAGE_DIR,
		ID_TILESET_THICK,
		ID_TILESET_THIN,
		ID_TILESET_SMALL,
		ID_TILESET_GNOME,
		ID_TILESET_GNOME2,
		ID_TILESET_DORWHITE,
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

	FXImage *getImageByName( const std::string & image, bool throw_exception = true );

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
	FXImage* load_background(const std::string & background_image );

	void error( const std::string & error );
	void config_error( const std::string & error );

	void make_panel_images(Panel *p);
	Button* new_button(Panel *panel, const char *name);

	void loadButtonImages();
	void loadDigitImages();
	void loadBackgroundImages();
	FXImage* createGifImage( const unsigned char* data, const std::string & name, bool transparent = true );

	void readRegistry();
	void writeRegistry();

	bool loadRandomImageFromPath( const std::string & image_dir );

	std::string getFileExt( const std::string & file_name );

	void reloadBoard();
	void releaseBoard();
};



#endif /* SRC_MAIN_H_ */
