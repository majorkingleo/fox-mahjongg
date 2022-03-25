/********************************************************************************
 *                                                                               *
 *                         Main Window                                           *
 *                                                                               *
 ********************************************************************************/
#include <vector>
#include <errno.h>
#include <format.h>
#include <main.h>
#include "panel.hh"
#include "matches.hh"
#include "button.hh"
#include "board.hh"
#include "solution.hh"
#include "counter.hh"
#include <colored_output.h>
#include <OutDebug.h>
#include <arg.h>
#include <cpp_util.h>
#include "tiles_thick.h"
#include "tiles_thin.h"
#include "tiles_small.h"
#include "tiles_gnome.h"
#include "tiles_gnome2.h"
#include "tiles_dorwhite.h"
#include "data_buttons.h"
#include "data_digits.h"
#include "data_xmahjongg.h"
#include "FXPixelBuffer.h"
#include <Magick++.h>
#include <alarm.hh>
#include "data_background_default.h"
#include "data_background_green.h"
#include "data_background_blue.h"
#include <string_utils.h>
#include <cppdir.h>
#include "FXRadioGroup.h"


using namespace Tools;

const int LEVEL_START = 0;
const unsigned TIMEOUT_VALUE = 100 * 1000000; // 100ms





// Message Map for the Scribble Window class
FXDEFMAP(MahjonggWindow) MahjonggWindowMap[]={

		FXMAPFUNC(SEL_LEFTBUTTONPRESS,   MahjonggWindow::ID_CANVAS, MahjonggWindow::onMouseDown),
		FXMAPFUNC(SEL_LEFTBUTTONRELEASE, MahjonggWindow::ID_CANVAS, MahjonggWindow::onMouseUp),
		FXMAPFUNC(SEL_KEYPRESS,          MahjonggWindow::ID_CANVAS, MahjonggWindow::onKeypress),

		FXMAPFUNC(SEL_TIMEOUT,           MahjonggWindow::ID_TIMER,  MahjonggWindow::onTimeout),
		FXMAPFUNC(SEL_CLOSE,             0,                         MahjonggWindow::onClose),

		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_BACKGROUND_DEFAULT,     	MahjonggWindow::onChangeBackgroundDefault),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_BACKGROUND_GREEN, 	    	MahjonggWindow::onChangeBackgroundGreen),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_BACKGROUND_BLUE, 	    	MahjonggWindow::onChangeBackgroundBlue),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_BACKGROUND_USER_IMAGE, 		MahjonggWindow::onChangeBackgroundUserImage),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_BACKGROUND_USER_IMAGE_DIR, 	MahjonggWindow::onChangeBackgroundUserImageDir),

		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_TILESET_THICK, 				MahjonggWindow::onChangeTilesetThick),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_TILESET_THIN, 				MahjonggWindow::onChangeTilesetThin),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_TILESET_SMALL, 				MahjonggWindow::onChangeTilesetSmall),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_TILESET_GNOME, 				MahjonggWindow::onChangeTilesetGnome),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_TILESET_GNOME2,				MahjonggWindow::onChangeTilesetGnome2),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_TILESET_DORWHITE,			MahjonggWindow::onChangeTilesetDorwhite),
};



// Macro for the ScribbleApp class hierarchy implementation
FXIMPLEMENT(MahjonggWindow,FXMainWindow,MahjonggWindowMap,ARRAYNUMBER(MahjonggWindowMap));


MahjonggWindow::MahjonggWindow()
: FXMainWindow(0,"",NULL,NULL,
		DECOR_TITLE | DECOR_CLOSE | DECOR_MINIMIZE,
		0,0,810,600),
  contents(0),
  canvasFrame(0),
  buttonFrame(0),
  canvas(0),
  mdflag(0),
  drawColor(0),
  move_mode(0),
  tileset(0),
  background(0),
  game(0),
  last_new_board(),
  solveable_boards( true ),
  panel(0),
  gifbuttons(0),
  matches(0),
  layout_name(0),
  config_dir(),
  imageByName(),
  nameByImagePtr(),
  menubar(0),
  icon_xmahjongg(0),
  radio_group_background_image(0),
  radio_group_tileset(0)
{}

// Construct a MahjonggWindow
MahjonggWindow::MahjonggWindow(FXApp *a)
: FXMainWindow(a,"FOX Mahjongg",NULL,NULL,
		DECOR_TITLE | DECOR_CLOSE | DECOR_ALL, // DECOR_MINIMIZE,
		0,0,1150,700),
  contents(0),
  canvasFrame(0),
  buttonFrame(0),
  canvas(0),
  mdflag(0),
  drawColor(0),
  move_mode(0),
  tileset(0),
  background(0),
  game(0),
  last_new_board(),
  solveable_boards( true ),
  panel(0),
  gifbuttons(0),
  matches(0),
  layout_name(0),
  config_dir(),
  imageByName(),
  nameByImagePtr(),
  menubar(0),
  icon_xmahjongg(0),
  radio_group_background_image(0),
  radio_group_tileset(0)
{
	known_image_extensions.insert( "GIF" );
	known_image_extensions.insert( "PNG" );
	known_image_extensions.insert( "JPG" );
	known_image_extensions.insert( "JPEG" );

	srand( time(0) );

	radio_group_background_image = new FXRadioGroup();
	radio_group_tileset 		 = new FXRadioGroup();

	icon_xmahjongg = new FXGIFIcon( getApp(), xmahjongg_gif, 0, IMAGE_ALPHAGUESS );
	setIcon( icon_xmahjongg );

	menubar=new FXMenuBar(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);
    FXMenuPane *filemenu=new FXMenuPane(this);
    new FXMenuCommand(filemenu,"&Quit the application",NULL,getApp(),FXApp::ID_QUIT);
    new FXMenuTitle(menubar,"&File",NULL,filemenu);


    FXMenuPane *background=new FXMenuPane(this);
    mc_background_default        = new FXMenuRadio(background,"Default",this,ID_BACKGROUND_DEFAULT);
    mc_background_green          = new FXMenuRadio(background,"Green",this,ID_BACKGROUND_GREEN);
    mc_background_blue           = new FXMenuRadio(background,"Blue",this,ID_BACKGROUND_BLUE);
    mc_background_user_image     = new FXMenuRadio(background,"User defined",this,ID_BACKGROUND_USER_IMAGE);
    mc_background_user_image_dir = new FXMenuRadio(background,"User defined image directory",this,ID_BACKGROUND_USER_IMAGE_DIR);

    radio_group_background_image->add( mc_background_default );
    radio_group_background_image->add( mc_background_green );
    radio_group_background_image->add( mc_background_blue );
    radio_group_background_image->add( mc_background_user_image );
    radio_group_background_image->add( mc_background_user_image_dir );

    new FXMenuTitle(menubar,"&Background",NULL,background);




    FXMenuPane *tileset = new FXMenuPane(this);
    mc_tileset_thick    = new FXMenuRadio(tileset,"Thick",this,ID_TILESET_THICK);
    mc_tileset_thin     = new FXMenuRadio(tileset,"Thin",this,ID_TILESET_THIN);
    mc_tileset_small    = new FXMenuRadio(tileset,"Small",this,ID_TILESET_SMALL);
    mc_tileset_gnome    = new FXMenuRadio(tileset,"Gnome",this,ID_TILESET_GNOME);
    mc_tileset_gnome2   = new FXMenuRadio(tileset,"Gnome2",this,ID_TILESET_GNOME2);
    mc_tileset_dorwhite = new FXMenuRadio(tileset,"Dorwhite",this,ID_TILESET_DORWHITE);

    radio_group_tileset->add( mc_tileset_thick );
    radio_group_tileset->add( mc_tileset_thin );
    radio_group_tileset->add( mc_tileset_small );
    radio_group_tileset->add( mc_tileset_gnome );
    radio_group_tileset->add( mc_tileset_gnome2 );
    radio_group_tileset->add( mc_tileset_dorwhite );

    new FXMenuTitle(menubar,"&Tileset",NULL,tileset);


	// LEFT pane to contain the canvas
	canvasFrame=new FXVerticalFrame(this,FRAME_SUNKEN|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT,
			0,0,0,0,0,0,0,0);

	// Drawing canvas
	canvas=new FXPixelBuffer(this,canvasFrame,this,ID_CANVAS,
			FRAME_SUNKEN|FRAME_THICK|LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,
			0, 0, 670, 550);


	// Initialize private variables
	drawColor=FXRGB(255,0,0);
	mdflag=0;
	move_mode = 0;

	solveable_boards = true;


	config_dir = "share";
	layout_name = 0;
}

MahjonggWindow::~MahjonggWindow()
{
	for( auto it : imageByName ) {
		delete it.second;
	}

	imageByName.clear();

	releaseBoard();

	delete icon_xmahjongg;
	delete radio_group_background_image;
	delete radio_group_tileset;
}

void MahjonggWindow::detach()
{
	FXMainWindow::detach();

	for( auto it : imageByName ) {
		it.second->detach();
	}

	icon_xmahjongg->detach();
}

// Create and initialize 
void MahjonggWindow::create(){

	// Create the windows
	FXMainWindow::create();

	readRegistry();

	loadButtonImages();
	loadDigitImages();
	loadBackgroundImages();

	reloadBoard();

	// Make the main window appear
	show(PLACEMENT_SCREEN);
	getApp()->addTimeout( this, ID_TIMER, TIMEOUT_VALUE );
}

void MahjonggWindow::releaseBoard()
{
	if( panel ) {
		delete panel->board();
		delete panel->new_but;
		delete panel->undo_but;
		delete panel->quit_but;
		delete panel->hint_but;
		delete panel->clean_but;
	}

	delete panel;   panel = 0;
	delete game;    game = 0;
	delete tileset; tileset = 0;
	delete matches; matches = 0;

	canvas->clear();
}

void MahjonggWindow::reloadBoard()
{
	releaseBoard();

	if( mc_background_user_image_dir->getCheck() ) {
		loadRandomImageFromPath( background_image_path );
	}

	tileset = load_tileset("thick", config_dir.c_str());
	// background = load_background("default", config_dir.c_str());

	DEBUG( format( "background_image_name: %s", background_image_name ) );

	if( !background_image_name.empty() ) {
		background = load_background(background_image_name);
	}

	if( !background && !background_name.empty() ) {
		background = getImageByName( background_name );
	}

	if( !background ) {
		background = getImageByName( "background_default" );
	}

	game = new Game(tileset);

	background->create();


	DEBUG( format( "canvas window is %p", canvas));

	panel = new Panel(getApp(), canvas, this);

	make_panel_images(panel);
	matches->set_game(game);
	Board *board = new Board(panel, game, tileset);
	panel->set_board(board);
	panel->set_background(background);
	panel->set_solution(new SolutionDisplay(game, board));

	FancyTileCounter *tile_counter = new FancyTileCounter(panel);
	game->add_hook(tile_counter);
	panel->set_tile_count(tile_counter);


	// Lay out game.
	if (!layout_name) {
		game->layout_default();
	} else {
		int ok = game->layout_file(layout_name);
		if (ok < 0) {
			int len = strlen(layout_name) + strlen(config_dir.c_str()) + 10;
			char *buf = new char[len];
			sprintf(buf, "%s/layouts/%s", config_dir, layout_name);
			ok = game->layout_file(buf);
			delete[] buf;
		}
		if (ok < 0)
			fatal_error("layout %s: %s", layout_name, strerror(errno));
		else if (ok == 0)
			fatal_error("layout %s corrupted", layout_name);
	}


	int wid, hgt;
	board->tile_layout_size(&wid, &hgt);

	DEBUG( format( "Board size: %dx%d", wid, hgt ) );

	int width = wid + 38;
	int height = hgt + 38 + 56; // + Buttons
	// setWidth(width);
	// setHeight(height + menubar->getHeight());
	resize(width, height + menubar->getHeight());
	canvas->resize(width, height );

	// automatically done by panel->resize()
	// board->set_size(width, height - board->y_pos());
	// board->center_layout();
	panel->resize(width,height);

	game->start(time(0), solveable_boards );
	last_new_board = Moment::now();
	panel->set_visible( true );

	panel->redraw_all();
}

// Mouse button was pressed somewhere
long MahjonggWindow::onMouseDown(FXObject*,FXSelector,void* ptr){

	DEBUG( __FUNCTION__ );

	FXEvent *ev=(FXEvent*)ptr;
	panel->click( game, ev->win_x, ev->win_y, ev->state, ev->time, false );

	return 1;
}


// Mouse button was pressed somewhere
long MahjonggWindow::onMouseUp(FXObject*,FXSelector,void* ptr){

	DEBUG( __FUNCTION__ );

	FXEvent *ev=(FXEvent*)ptr;
	panel->click( game, ev->win_x, ev->win_y, ev->state, ev->time, true );

	return 1;
}



void MahjonggWindow::layout()
{
	FXMainWindow::layout();

	if( canvas ) {
		canvas->resize(getWidth(), getHeight() - menubar->getHeight());
	}

	if( panel ) {
		panel->resize(getWidth(),getHeight() - menubar->getHeight());
		panel->redraw_all();
	}
}


long MahjonggWindow::onTimeout(FXObject*, FXSelector, void* ptr)
{
	Alarm::x_wait();

	if( canvas ) {
		canvas->redrawIfDirty();
	}

	getApp()->flush();
	getApp()->addTimeout( this, ID_TIMER, TIMEOUT_VALUE );
	return 1;
}


long MahjonggWindow::onClose(FXObject*obj,FXSelector sel,void* ptr )
{
	// autoRepeat(1);

	return FXMainWindow::onCmdClose( obj, sel, ptr );
}

// Close window
FXbool MahjonggWindow::close(FXbool notify)
{

  // Save settings
  writeRegistry();

  // Perform normal close stuff
  return FXMainWindow::close(notify);
}


void MahjonggWindow::error( const std::string & error )
{
	std::cerr << "Error: " << error << std::endl;
}

void MahjonggWindow::config_error( const std::string & error )
{
	std::cerr << "Config Error: " << error << std::endl;
}


Tileset* MahjonggWindow::load_tileset(const char *tileset_name, const char *config_dir)
{
#if 0
	int len = strlen(tileset_name) + strlen(config_dir) + 15;
	char *buf = new char[len];
	Gif_Stream *gfs;

	sprintf(buf, "%s/tiles/%s.gif", config_dir, tileset_name);
	FILE *f = fopen(buf, "rb");
	if (!f)
		f = fopen(tileset_name, "rb");
	if (!f) {
		gfs = 0;
		error(format("bad tileset `%s': %s", tileset_name, strerror(errno)));
	} else {
		gfs = Gif_FullReadFile(f, GIF_READ_COMPRESSED, 0, 0);
		fclose(f);
	}
#endif

	Tileset *tileset = 0;

	if( mc_tileset_thick->getCheck() ) {
		tileset = load_tileset_thick( this );
	} else  if( mc_tileset_thin->getCheck() ) {
		tileset = load_tileset_thin( this );
	} else  if( mc_tileset_small->getCheck() ) {
		tileset = load_tileset_small( this );
	} else  if( mc_tileset_gnome->getCheck() ) {
		tileset = load_tileset_gnome( this, canvas );
	} else  if( mc_tileset_gnome2->getCheck() ) {
		tileset = load_tileset_gnome2( this, canvas );
	} else  if( mc_tileset_dorwhite->getCheck() ) {
			tileset = load_tileset_dorwhite( this, canvas );
	} else {
		tileset = load_tileset_thick( this );
	}
	//tileset = load_tileset_thin( this );
#if 0
	// Xmahjongg tileset?
	if (gfs && !tileset && Gif_ImageCount(gfs) > 1)
		tileset = new Xmj3Tileset(gfs, gifx);
#endif
#if 0
	// Otherwise, check dimensions.
	int width = 0, height = 0;
	if (gfs && !tileset) {
		Gif_Image *gfi = Gif_GetImage(gfs, 0);
		width = (gfi ? Gif_ImageWidth(gfi) : 0);
		height = (gfi ? Gif_ImageHeight(gfi) : 0);
	}

	// Gnome tileset?
	if (gfs && !tileset && width > 2*height)
		tileset = new GnomeMjTileset(this);

	// KDE tileset?
	if (gfs && !tileset && width == 360 && height == 280) {
		tileset = new KDETileset(gfs, gifx);
		if (!tileset->ok()) {
			delete tileset;
			tileset = 0;
		}
	}

	// Kyodai tileset?
	if (gfs && !tileset)
		tileset = new KyodaiTileset(gfs, gifx);

	// Delete tileset if bad
	if (tileset && !tileset->ok()) {
		delete tileset;
		tileset = 0;
	}

	delete[] buf;
	if (gfs && !gfs->refcount)
		Gif_DeleteStream(gfs);
#endif

	// What if that's not a valid tileset?
	if (!tileset) {
		if (strcmp(tileset_name, "thick") == 0) {
			config_error("can't load `thick' tileset!");
		}
		/*else if (f != 0) {
			error(format("tileset `%s' is invalid", tileset_name));
		}*/
		error(format("using default tileset `thick'"));
		return load_tileset("thick", config_dir);
	}

	return tileset;
}

FXImage* MahjonggWindow::load_background(const char *background_name, const char *config_dir )
{

	int len = strlen(background_name) + strlen(config_dir) + 21;
	char *buf = new char[len];

	sprintf(buf, "%s/backgrounds/%s.gif", config_dir, background_name);

	FXImage *img = new FXGIFImage(getApp(),nullptr,IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);

	FXFileStream stream;

	if(stream.open(buf,FXStreamLoad)){
		getApp()->beginWaitCursor();
		img->loadPixels(stream);
		stream.close();
		getApp()->endWaitCursor();
	}

	return img;
}

std::string MahjonggWindow::getFileExt( const std::string & file_name )
{
	std::string::size_type pos = file_name.rfind( '.' );

	if( pos == std::string::npos || file_name.size() - pos > 5 ) {
		return "";
	}

	std::string ext = toupper(file_name.substr( pos + 1 ));

	return ext;
}

FXImage* MahjonggWindow::load_background(const std::string & background_image )
{
	std::string ext = getFileExt( background_image );

	FXImage *img = 0;

	if( ext == "GIF" ) {
		img = new FXGIFImage(getApp(),nullptr,IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);
	} else if( ext == "PNG" ) {
		img = new FXPNGImage(getApp(),nullptr,IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);
	} else if( ext == "JPG" || ext == "JPEG" ) {
		img = new FXJPGImage(getApp(),nullptr,IMAGE_KEEP|IMAGE_SHMI|IMAGE_SHMP);
	} else {
		return 0;
	}

	FXFileStream stream;

	if(stream.open(background_image.c_str(),FXStreamLoad)){
		getApp()->beginWaitCursor();
		img->loadPixels(stream);
		stream.close();
		getApp()->endWaitCursor();
	}

	return img;
}


void MahjonggWindow::make_panel_images(Panel *p)
{
  matches = new MatchCount(p, "rock");
  p->set_match_count(matches);

  p->new_but = new_button(p, "new");
  p->undo_but = new_button(p, "undo");
  p->quit_but = new_button(p, "quit");
  p->hint_but = new_button(p, "hint");
  p->clean_but = new_button(p, "clean");
}

Button *MahjonggWindow::new_button(Panel *panel, const char *name)
{
  char buf[100];
  Button *but = new Button(panel);
  but->set_normal(name);
  sprintf(buf, "%s-lit", name);
  but->set_lit(buf);
  return but;
}

FXImage *MahjonggWindow::getImageByName( const std::string & image_name, bool throw_exception )
{
	auto it = imageByName.find( image_name );

	if( it == imageByName.end() ) {
		if( !throw_exception ) {
			DEBUG( format( "cannot find image: %s", image_name ) );
			return 0;
		} else {
			throw REPORT_EXCEPTION( format( "no Button named %s", image_name ) );
		}
	}

	return it->second;
}


FXImage* MahjonggWindow::createGifImage( const unsigned char* data, const std::string & name, bool transparent )
{
	FXImage* img = 0;

	if( !transparent ) {
	 img = new FXGIFImage( getApp(), data, IMAGE_KEEP | IMAGE_SHMI | IMAGE_SHMP  );
	} else {
	 img = new FXGIFIcon( getApp(), data, 0, IMAGE_KEEP | IMAGE_ALPHAGUESS | IMAGE_SHMI | IMAGE_SHMP  );
	}

	img->create();

    if( !name.empty() ) {
        nameByImagePtr[img] = name;
    }
    
	return img;
}

void MahjonggWindow::loadButtonImages()
{
	imageByName["hint"]       = createGifImage( button_00_gif, "hint" );
	imageByName["new"]     	  = createGifImage( button_01_gif, "new" );
	imageByName["quit"]    	  = createGifImage( button_02_gif, "quit" );
	imageByName["rock"]       = createGifImage( button_03_gif, "rock" );
	imageByName["undo"]       = createGifImage( button_04_gif, "undo" );
	imageByName["clean"]      = createGifImage( button_05_gif, "clean" );
	imageByName["clean-lit"]  = createGifImage( button_06_gif, "clean-lit" );
	imageByName["hint-lit"]   = createGifImage( button_07_gif, "hint-lit" );
	imageByName["new-lit"]    = createGifImage( button_08_gif, "new-lit" );
	imageByName["quit-lit"]   = createGifImage( button_09_gif, "quit-lit" );
	imageByName["undo-lit"]   = createGifImage( button_10_gif, "undo-lit" );
}

void MahjonggWindow::loadDigitImages()
{
	imageByName["0"]       = createGifImage( digit_00_gif, "0" );
	imageByName["1"]       = createGifImage( digit_01_gif, "1" );
	imageByName["2"]       = createGifImage( digit_02_gif, "2" );
	imageByName["3"]       = createGifImage( digit_03_gif, "3" );
	imageByName["4"]       = createGifImage( digit_04_gif, "4" );
	imageByName["5"]       = createGifImage( digit_05_gif, "5" );
	imageByName["6"]       = createGifImage( digit_06_gif, "6" );
	imageByName["7"]       = createGifImage( digit_07_gif, "7" );
	imageByName["8"]       = createGifImage( digit_08_gif, "8" );
	imageByName["9"]       = createGifImage( digit_09_gif, "9" );
}

void MahjonggWindow::loadBackgroundImages()
{
	imageByName["background_default"]= createGifImage( background_default_gif, "background_default", false );
	imageByName["background_green"]= createGifImage( background_green_gif, "background_green", false );
	imageByName["background_blue"]= createGifImage( background_blue_gif, "background_blue", false );
}

long MahjonggWindow::onKeypress(FXObject*,FXSelector,void* ptr){

	DEBUG( __FUNCTION__ );

	FXEvent *ev=(FXEvent*)ptr;
	panel->key_press( game, ev->code, ev->state );

	return 1;
}

long MahjonggWindow::onChangeBackgroundDefault(FXObject* obj,FXSelector sel, void* ptr)
{
	FXRadioGroup::SavePoint save_point( radio_group_background_image->getSavePoint() );

	if( panel ) {
		panel->set_background(getImageByName("background_default"));
		radio_group_background_image->setCheck( mc_background_default );
		save_point.commit();
	}
	return 1;
}

long MahjonggWindow::onChangeBackgroundGreen(FXObject* obj,FXSelector sel, void* ptr)
{
	FXRadioGroup::SavePoint save_point( radio_group_background_image->getSavePoint() );

	if( panel ) {
		panel->set_background(getImageByName("background_green"));
		radio_group_background_image->setCheck( mc_background_green );
		save_point.commit();
	}
	return 1;
}

long MahjonggWindow::onChangeBackgroundBlue(FXObject* obj,FXSelector sel, void* ptr)
{
	FXRadioGroup::SavePoint save_point( radio_group_background_image->getSavePoint() );

	if( panel ) {
		panel->set_background(getImageByName("background_blue"));
		radio_group_background_image->setCheck( mc_background_blue );
		save_point.commit();
	}
	return 1;
}

long MahjonggWindow::onChangeBackgroundUserImage(FXObject* obj,FXSelector sel, void* ptr)
{
	FXRadioGroup::SavePoint save_point( radio_group_background_image->getSavePoint() );

	if( panel ) {
		FXString s = FXFileDialog::getOpenFilename( this, "Choose Background Image",
													last_file_open_path.c_str(),
													"*");
		if( s == FXString::null || s.text() == last_file_open_path ) {
			return 0;
		}

		FXImage *img = load_background( s.text() );

		if( img ) {
			img->create();
			last_file_open_path = s.text();
			background_image_name = s.text();
			imageByName[s.text()] = img;
			panel->set_background(img);
			radio_group_background_image->setCheck( mc_background_user_image );
			save_point.commit();
		}
	}
	return 1;
}

long MahjonggWindow::onChangeBackgroundUserImageDir(FXObject* obj,FXSelector sel, void* ptr)
{
	DEBUG( __FUNCTION__ );
	FXRadioGroup::SavePoint save_point( radio_group_background_image->getSavePoint() );

	if( panel ) {
		FXString s = FXFileDialog::getOpenDirectory( this, "Choose Background Image",
													last_file_open_path.c_str());

		DEBUG( format( "directory: %s", s.text() ));

		if( s == FXString::null ) {
			return 0;
		}


		if( loadRandomImageFromPath( s.text() ) ) {
			background_image_path = s.text();

			FXImage *img = load_background( background_image_name );

			if( img ) {
				img->create();
				last_file_open_path = s.text();
				background_image_path = s.text();
				imageByName[s.text()] = img;
				panel->set_background(img);
				radio_group_background_image->setCheck( mc_background_user_image_dir );
				save_point.commit();
			}

		}


	}
	return 1;
}

void MahjonggWindow::writeRegistry()
{
	getApp()->reg().writeBoolEntry("SETTINGS","background_default", mc_background_default->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","background_green", mc_background_green->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","background_blue", mc_background_blue->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","background_user_image", mc_background_user_image->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","background_user_image_dir", mc_background_user_image_dir->getCheck() );
	getApp()->reg().writeStringEntry( "SETTINGS", "last_file_open_path", last_file_open_path.c_str() );
	getApp()->reg().writeStringEntry( "SETTINGS", "background_image_name", background_image_name.c_str() );
	getApp()->reg().writeStringEntry( "SETTINGS", "background_image_path", background_image_path.c_str() );

	getApp()->reg().writeBoolEntry("SETTINGS","tileset_thick", 		mc_tileset_thick->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","tileset_thin", 		mc_tileset_thin->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","tileset_small", 		mc_tileset_small->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","tileset_gnome", 		mc_tileset_gnome->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","tileset_gnome2",   	mc_tileset_gnome2->getCheck() );
	getApp()->reg().writeBoolEntry("SETTINGS","tileset_dorwhite",	mc_tileset_dorwhite->getCheck() );
}

void MahjonggWindow::readRegistry()
{
	if( getApp()->reg().readBoolEntry("SETTINGS","background_default", false ) ) {
		radio_group_background_image->setCheck( mc_background_default );
		background_name = "background_default";
		background_image_name = "";
	}

	if( getApp()->reg().readBoolEntry("SETTINGS","background_green", false ) ) {
		radio_group_background_image->setCheck( mc_background_green );
		background_name = "background_green";
		background_image_name = "";
	}

	if( getApp()->reg().readBoolEntry("SETTINGS","background_blue", true ) ) {
		radio_group_background_image->setCheck( mc_background_blue );
		background_name = "background_blue";
		background_image_name = "";
	}

	if( getApp()->reg().readBoolEntry("SETTINGS","background_user_image", false ) ) {
		background_name = "";

		background_image_name = getApp()->reg().readStringEntry( "SETTINGS", "background_image_name", "" );

		if( !background_image_name.empty() ) {
			radio_group_background_image->setCheck( mc_background_user_image );
		}
	}

	if( getApp()->reg().readBoolEntry("SETTINGS","background_user_image_dir", false ) ) {
		background_name = "";

		background_image_path = getApp()->reg().readStringEntry( "SETTINGS", "background_image_path", "" );

		if( !background_image_path.empty() ) {

			if( loadRandomImageFromPath( background_image_path ) ) {
				radio_group_background_image->setCheck( mc_background_user_image_dir );
			}
		}
	}

	last_file_open_path   = getApp()->reg().readStringEntry( "SETTING", "last_file_open_path", "" );


	if( getApp()->reg().readBoolEntry("SETTINGS","tileset_thick", true ) ) {
		radio_group_tileset->setCheck( mc_tileset_thick );
	}
	else if( getApp()->reg().readBoolEntry("SETTINGS","tileset_thin", false ) ) {
		radio_group_tileset->setCheck( mc_tileset_thin );
	}
	else if( getApp()->reg().readBoolEntry("SETTINGS","tileset_small", false ) ) {
		radio_group_tileset->setCheck( mc_tileset_small );
	}
	else if( getApp()->reg().readBoolEntry("SETTINGS","tileset_gnome", false ) ) {
		radio_group_tileset->setCheck( mc_tileset_gnome );
	}
	else if( getApp()->reg().readBoolEntry("SETTINGS","tileset_gnome2", false ) ) {
		radio_group_tileset->setCheck( mc_tileset_gnome2 );
	}
	else if( getApp()->reg().readBoolEntry("SETTINGS","tileset_dorwhite", false ) ) {
		radio_group_tileset->setCheck( mc_tileset_dorwhite );
	}
}

bool MahjonggWindow::loadRandomImageFromPath( const std::string & image_dir )
{
	CppDir::Directory dir( image_dir );

	if( !dir ) {
		DEBUG( format( "not a directory %s", background_image_path ));
		return false;
	}

	std::vector<std::string> usable_files;

	for( auto & file : dir.get_files() ) {
		std::string ext = getFileExt( file.get_name() );

		if( known_image_extensions.find( ext ) == known_image_extensions.end() ) {
			continue;
		}

		std::string image_file = file.get_full_path();

		DEBUG( format( "found image: %s", image_file ) );

		usable_files.push_back( image_file );
	}

	if( usable_files.empty() ) {
		return false;
	}

	int max = usable_files.size() - 1;
	int min = 0;

	const int range = max - min + 1;
	int num = rand() % range + min;

	background_image_name = usable_files.at(num);

	return true;
}


long MahjonggWindow::onChangeTilesetThick(FXObject* obj,FXSelector sel,void* ptr)
{
	radio_group_tileset->setCheck( mc_tileset_thick );
	reloadBoard();
	return 1;
}

long MahjonggWindow::onChangeTilesetThin(FXObject* obj,FXSelector sel,void* ptr)
{
	radio_group_tileset->setCheck( mc_tileset_thin );
	reloadBoard();
	return 1;
}

long MahjonggWindow::onChangeTilesetSmall(FXObject* obj,FXSelector sel,void* ptr)
{
	radio_group_tileset->setCheck( mc_tileset_small );
	reloadBoard();
	return 1;
}

long MahjonggWindow::onChangeTilesetGnome(FXObject* obj,FXSelector sel,void* ptr)
{
	radio_group_tileset->setCheck( mc_tileset_gnome );
	reloadBoard();
	return 1;
}

long MahjonggWindow::onChangeTilesetGnome2(FXObject* obj,FXSelector sel,void* ptr)
{
	radio_group_tileset->setCheck( mc_tileset_gnome2 );
	reloadBoard();
	return 1;
}

long MahjonggWindow::onChangeTilesetDorwhite(FXObject* obj,FXSelector sel,void* ptr)
{
	radio_group_tileset->setCheck( mc_tileset_dorwhite );
	reloadBoard();
	return 1;
}

void
fatal_error(const char *message, ...)
{
  va_list val;
  va_start(val, message);
  fprintf(stderr, "%s: ", "TODO");
  vfprintf(stderr, message, val);
  fputc('\n', stderr);
  exit(1);
}

static void usage( const std::string & prog )
{
    std::cerr << "usage: "
              << prog << " [-debug]\n";
}


// Here we begin
int main(int argc,char *argv[]){

	Magick::InitializeMagick(*argv);

	ColoredOutput colored_output;

    Arg::Arg arg( argc, argv );

    arg.addPrefix( "-" );
    arg.addPrefix( "--" );

    Arg::OptionChain oc_info;
    arg.addChainR( &oc_info );
    oc_info.setMinMatch( 1 );
    oc_info.setContinueOnMatch( false );
    oc_info.setContinueOnFail( true );

    Arg::FlagOption o_help( "h" );
    o_help.addName( "help" );
    o_help.setDescription( "Show this page" );
    oc_info.addOptionR( &o_help );

    Arg::FlagOption o_version( "v" );
    o_version.addName( "version" );
    o_version.setDescription( "Show replace version number" );
    oc_info.addOptionR( &o_version );

    Arg::FlagOption o_debug("debug");
    o_debug.setDescription("print debugging messages");
    o_debug.setRequired(false);
    arg.addOptionR( &o_debug );

    const unsigned int console_width = 80;

    if( !arg.parse() )
    {
        if( o_version.getState() )
        {
            std::cout << format("%s version %s\n", argv[0], VERSION);
            return 0;
        } else {
            usage(argv[0]);
            std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
            return 1;
        }
    }

    if( o_help.getState() )
    {
        // usage(argv[0]);
        std::cout << arg.getHelp(5,20,30, console_width ) << std::endl;
        return 0;
    }

    if( o_debug.getState() )
    {
        Tools::x_debug = new OutDebug();
    }


	// Make application
	FXApp application("FOX-Mahjongg","majorleo");

	// Start app
	application.init(argc,argv);

	// Scribble window
	new MahjonggWindow(&application);

	// Create the application's windows
	application.create();

	// Run the application
	return application.run();
}


