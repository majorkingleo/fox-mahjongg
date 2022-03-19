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
#include "data_buttons.h"
#include "data_digits.h"
#include "FXPixelBuffer.h"
#include <Magick++.h>
#include <alarm.hh>

using namespace Tools;

const int LEVEL_START = 0;
const unsigned TIMEOUT_VALUE = 2000;





// Message Map for the Scribble Window class
FXDEFMAP(MahjonggWindow) MahjonggWindowMap[]={

		FXMAPFUNC(SEL_LEFTBUTTONPRESS,   MahjonggWindow::ID_CANVAS, MahjonggWindow::onMouseDown),
		FXMAPFUNC(SEL_LEFTBUTTONRELEASE, MahjonggWindow::ID_CANVAS, MahjonggWindow::onMouseUp),

		FXMAPFUNC(SEL_TIMEOUT,           MahjonggWindow::ID_TIMER,  MahjonggWindow::onTimeout),
		FXMAPFUNC(SEL_CLOSE,             0,                         MahjonggWindow::onClose),
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
  nameByImagePtr()
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
  nameByImagePtr()
{
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
}

void MahjonggWindow::detach()
{
	FXMainWindow::detach();

	for( auto it : imageByName ) {
		it.second->detach();
	}
}

// Create and initialize 
void MahjonggWindow::create(){

	// Create the windows
	FXMainWindow::create();

	loadButtonImages();
	loadDigitImages();


	tileset = load_tileset("thick", config_dir.c_str());
	background = load_background("default", config_dir.c_str());
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

#if 1
    int wid, hgt;
    board->tile_layout_size(&wid, &hgt);

    DEBUG( format( "Board size: %dx%d", wid, hgt ) );

    int width = wid + 38;
    int height = hgt + 38 + 56; // + Buttons
    setWidth(width);
    setHeight(height);
    canvas->resize(width, height );
   
    // automatically done by panel->resize()
    // board->set_size(width, height - board->y_pos());
    // board->center_layout();
    panel->resize(width,height);
#else
    canvas->resize(getWidth(), getHeight() );
    panel->resize(getWidth(),getHeight());
#endif
    game->start(time(0), solveable_boards );
    last_new_board = Moment::now();
    panel->set_visible( true );

	panel->redraw_all();

	// Make the main window appear
	show(PLACEMENT_SCREEN);
	getApp()->addTimeout( this, ID_TIMER, TIMEOUT_VALUE );

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
		canvas->resize(getWidth(), getHeight());
	}

	if( panel ) {
		panel->resize(getWidth(),getHeight());
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

	tileset = load_tileset_thick( this );
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

FXImage *MahjonggWindow::getImageByName( const std::string & image_name )
{
	auto it = imageByName.find( image_name );

	if( it == imageByName.end() ) {
		throw REPORT_EXCEPTION( format( "no Button named %s", image_name ) );
	}

	return it->second;
}


FXImage* MahjonggWindow::createGifImage( const unsigned char* data, const std::string & name )
{
	FXImage* img = new FXGIFIcon( getApp(), data, 0, IMAGE_KEEP | IMAGE_ALPHAGUESS | IMAGE_SHMI | IMAGE_SHMP  );
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
              << prog << " [URL] [clock.png]\n";
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




