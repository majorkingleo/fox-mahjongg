/********************************************************************************
 *                                                                               *
 *                         Main Window                                           *
 *                                                                               *
 ********************************************************************************/
#include "fx.h"
#include <vector>


#ifdef WIN32
#  include <windows.h>
#else
#  include <X11/Xlib.h>
#endif


const int LEVEL_START = 0;
const unsigned TIMEOUT_VALUE = 20;

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
};



// Message Map for the Scribble Window class
FXDEFMAP(MahjonggWindow) MahjonggWindowMap[]={

		//________Message_Type_____________________ID____________Message_Handler_______
		FXMAPFUNC(SEL_PAINT,             MahjonggWindow::ID_CANVAS, MahjonggWindow::onPaint),
		FXMAPFUNC(SEL_LEFTBUTTONPRESS,   MahjonggWindow::ID_CANVAS, MahjonggWindow::onMouseDown),
		FXMAPFUNC(SEL_MOTION,            MahjonggWindow::ID_CANVAS, MahjonggWindow::onMouseMove),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_CLEAR,  MahjonggWindow::onCmdClear),
		// FXMAPFUNC(SEL_TIMEOUT,           MahjonggWindow::ID_TIMER,  MahjonggWindow::onTimeout),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_TITLE,  MahjonggWindow::openurl),
		// FXMAPFUNC(SEL_KEYPRESS,          0,                         MahjonggWindow::onkeypress),
		// FXMAPFUNC(SEL_KEYRELEASE,        0,                         MahjonggWindow::onkeyrelease),
		FXMAPFUNC(SEL_CLOSE,             0,                         MahjonggWindow::onClose),
		FXMAPFUNC(SEL_COMMAND,           MahjonggWindow::ID_QUIT,   MahjonggWindow::onClose),
};



// Macro for the ScribbleApp class hierarchy implementation
FXIMPLEMENT(MahjonggWindow,FXMainWindow,MahjonggWindowMap,ARRAYNUMBER(MahjonggWindowMap));



// Construct a MahjonggWindow
MahjonggWindow::MahjonggWindow(FXApp *a):FXMainWindow(a,"austromobil.at Breakout",NULL,NULL,
		DECOR_TITLE | DECOR_CLOSE | DECOR_MINIMIZE,
		0,0,810,600)
{

	contents=new FXHorizontalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);

	// LEFT pane to contain the canvas
	canvasFrame=new FXVerticalFrame(contents,FRAME_SUNKEN|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT,
			0,0,0,0,10,10,10,10);

	// Label above the canvas
	new FXButton(canvasFrame,"www.austromobil.at",NULL, this, ID_TITLE, JUSTIFY_CENTER_X|LAYOUT_FILL_X|FRAME_NONE);

	// Horizontal divider line
	new FXHorizontalSeparator(canvasFrame,SEPARATOR_GROOVE|LAYOUT_FILL_X);

	// Drawing canvas
	canvas=new FXCanvas(canvasFrame,this,ID_CANVAS,
			FRAME_SUNKEN|FRAME_THICK|LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,
			0, 0, 670, 550);

	// RIGHT pane for the buttons
	buttonFrame=new FXVerticalFrame(contents,FRAME_SUNKEN|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT,
			0,0,0,0,10,10,10,10);

	// Label above the buttons
	new FXLabel(buttonFrame,"Breakout",NULL,JUSTIFY_CENTER_X|LAYOUT_FILL_X);

	// Horizontal divider line
	new FXHorizontalSeparator(buttonFrame,SEPARATOR_RIDGE|LAYOUT_FILL_X);

	// Button to clear
	new FXButton(buttonFrame,"&New Game",NULL,this,ID_CLEAR,
			FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,5,5);

	// Exit button
	new FXButton(buttonFrame,"&Exit",NULL,this,ID_QUIT,
			FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,5,5);

	new FXHorizontalSeparator(buttonFrame,SEPARATOR_GROOVE|LAYOUT_FILL_X);

	level_label = new FXLabel( buttonFrame, "Level: ", NULL,JUSTIFY_LEFT | LAYOUT_FILL_X | FRAME_SUNKEN );
	retry_label = new FXLabel( buttonFrame, "Retries: ", NULL,JUSTIFY_LEFT | LAYOUT_FILL_X | FRAME_SUNKEN );

	// level = new LevelStartup( canvas, getApp() );


	// Initialize private variables
	drawColor=FXRGB(255,0,0);
	mdflag=0;
	running=0;
	level_count = LEVEL_START;
	move_mode = 0;
}



// Create and initialize 
void MahjonggWindow::create(){

	// Create the windows
	FXMainWindow::create();

	/*
	level->create();
	running = 1;
	level->run();
	*/

	// Make the main window appear
	show(PLACEMENT_SCREEN);
	// getApp()->addTimeout( TIMEOUT_VALUE, this, ID_TIMER );

	// autoRepeat(0);
}



// Mouse button was pressed somewhere
long MahjonggWindow::onMouseDown(FXObject*,FXSelector,void*){

	running = !running;

	if( running )
	{
		canvas->grab();
		// level->run();
	} else {
		// level->pause();
	}


	return 1;
}



// The mouse has moved, draw a line
long MahjonggWindow::onMouseMove(FXObject*, FXSelector, void* ptr){
	FXEvent *ev=(FXEvent*)ptr;

	// level->move_board( ev->win_x );

	return 1;
}



// Paint the canvas
long MahjonggWindow::onPaint(FXObject*,FXSelector,void* ptr){

	// level->paint();

	return 1;
}


// Handle the clear message
long MahjonggWindow::onCmdClear(FXObject*,FXSelector,void*){

	// pause();

	retry_count = 2;
	level_count = LEVEL_START;
	// level = get_next_level( true );

	return 1;
}
/*
long MahjonggWindow::onTimeout(FXObject*, FXSelector, void* ptr)
{
	if( running )
	{
		if( move_mode < 0 )
		{
			level->move_board_left( abs( move_mode-- ) );

			if( move_mode < -20 )
				move_mode = -20;
		}
		else if( move_mode > 0 )
		{
			level->move_board_right( abs( move_mode++ ) );

			if( move_mode > 20 )
				move_mode = 20;
		}
	}

	level->timeout();

	if( level->finished() )
	{
		pause();
		level = get_next_level();
	}

	getApp()->flush();

	getApp()->addTimeout( TIMEOUT_VALUE, this, ID_TIMER );
	return 1;
}
*/

/*
Ref<Level> MahjonggWindow::get_next_level( bool force )
{
	if( !force )
	{
		if( !level->finished() || !level->succeeded() )
		{
			retry_count--;

			if( retry_count < 0 )
			{
				level_count = 2;
				retry_label->setText( "Retries:  " );
				move_mode = 0;
			} else {
				retry_label->setText( FXString().format( "Retries: %d", retry_count ) );
				level->reset();
				move_mode = 0;
				return level;
			}

		}
	}

	switch( level_count )
	{
		case 0: level = new LevelAki( canvas, getApp() ); level_count++; break;
		case 1: level = new LevelRotane( canvas, getApp() ); level_count++; break;
		default:
			level = new LevelStartup( canvas, getApp() ); level_count = 0; break;
	}

	level_label->setText( FXString().format( "Level: %d", level_count - 1 ) );
	retry_count++;
	retry_label->setText( FXString().format( "Retries: %d", retry_count ) );

	level->create();
	level->paint();
	move_mode = 0;

	return level;
}
*/
long MahjonggWindow::openurl(FXObject*,FXSelector,void*)
{
#ifdef WIN32
	ShellExecute( NULL, "open", "http://www.austromobil.at", "", "", SW_SHOWNORMAL );
#endif
	return 1;
}

/*
long MahjonggWindow::onkeypress(FXObject*,FXSelector,void* ptr)
{
	FXEvent *ev = (FXEvent*) ptr;

#ifndef WIN32
	if( ev->code == KEY_Left )
		move_mode = -5;
	else if( ev->code == KEY_Right )
		move_mode = 5;
#else
	if( ev->code == KEY_Left )
	{
		if( move_mode >= 0 )
			move_mode = -5;
	}
	else if( ev->code == KEY_Right )
	{
		if( move_mode <= 0 )
			move_mode = 5;
	}
#endif

if( ev->code == KEY_space )
{
	if( running )
		pause();
	else
		cont();
}

return 1;
}
*/

/*
long MahjonggWindow::onkeyrelease(FXObject*,FXSelector,void* ptr)
{
	FXEvent *ev = (FXEvent*) ptr;

	if( ev->code == KEY_Left ||
			ev->code == KEY_Right )
	{
		move_mode = 0;
	}

	return 1;
}
*/

/*
void MahjonggWindow::autoRepeat(int state)
{
	if ((state<0) || (state>1))
		return;

#ifndef WIN32
	XKeyboardControl values;
	values.auto_repeat_mode = state;
	values.key = -1;         // ALL keys
	XChangeKeyboardControl((Display*)getApp()->getDisplay(), KBAutoRepeatMode, &values);
#endif
}
*/

long MahjonggWindow::onClose(FXObject*obj,FXSelector sel,void* ptr )
{
	// autoRepeat(1);

	return FXMainWindow::onCmdClose( obj, sel, ptr );
}

// Here we begin
int main(int argc,char *argv[]){

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




