bin_PROGRAMS=fox-mahjongg

fox_mahjongg_SOURCES=\
		src/colored_output.cc\
		src/main.h\
		src/main.cc\
		src/OutDebug.cc\
		src/DetectLocale.cc \
		src/DetectLocale.h \
		src/read_file.h \
		src/read_file.cc \
		src/alarm.cc \
		src/alarm.hh \
		src/board.hh \
		src/board.cc \
		src/button.hh \
		src/button.cc \
		src/counter.hh \
		src/counter.cc \
		src/game.hh \
		src/game.cc \
		src/gmjts.hh \
		src/gmjts.cc \
		src/hint.hh \
		src/hint.cc \
		src/kdets.hh \
		src/kdets.cc \
		src/kmjts.hh \
		src/kmjts.cc \
		src/matches.hh \
		src/matches.cc \
		src/moment.hh \
		src/moment.cc \
		src/panel.hh \
		src/panel.cc \
		src/solution.hh \
		src/solution.cc \
		src/solvable.hh \
		src/solvable.cc \
		src/swgeneral.hh \
		src/swgeneral.cc \
		src/swwidget.hh \
		src/swwidget.cc \
		src/tile.hh \
		src/tile.cc \
		src/tileset.hh \
		src/tileset.cc \
		src/traverse.hh \
		src/traverse.cc \
		src/xmj3ts.hh \
		src/xmj3ts.cc  \
		src/random.cc \
		src/tiles_thick.h \
		src/tiles_thick.cc \
		src/tiles_thin.h \
		src/tiles_thin.cc \
		src/tiles_small.h \
		src/tiles_small.cc \
		src/tiles_gnome.h \
		src/tiles_gnome.cc \
		src/tiles_gnome2.h \
		src/tiles_gnome2.cc \
		src/FXPixelBuffer.h \
		src/FXPixelBuffer.cc \
		src/FXPixelBufferObject.h \
		src/FXPixelBufferObject.cc \
		src/FXRadioGroup.h \
		src/FXRadioGroup.cc
		  	 
			  

generated/data_tiles_thick.cc: share/tiles/thick.gif
	mkdir -p share/tiles/thick
	convert share/tiles/thick.gif share/tiles/thick/tiles_thick_%02d.gif
	reswrap -o generated/data_tiles_thick.cc -i data_tiles_thick.h --suffix _gif share/tiles/thick/tiles_thick_*.gif
	reswrap -o generated/data_tiles_thick.h -h --suffix _gif share/tiles/thick/tiles_thick_*.gif
		
generated/data_tiles_thick.h: generated/data_tiles_thick.cc


generated/data_tiles_thin.cc: share/tiles/thin.gif
	mkdir -p share/tiles/thin
	convert share/tiles/thin.gif share/tiles/thin/tiles_thin_%02d.gif
	reswrap -o generated/data_tiles_thin.cc -i data_tiles_thin.h --suffix _gif share/tiles/thin/tiles_thin_*.gif
	reswrap -o generated/data_tiles_thin.h -h --suffix _gif share/tiles/thin/tiles_thin_*.gif
		
generated/data_tiles_thin.h: generated/data_tiles_thin.cc



generated/data_tiles_small.cc: share/tiles/small.gif
	mkdir -p share/tiles/small
	convert share/tiles/small.gif share/tiles/small/tiles_small_%02d.gif
	reswrap -o generated/data_tiles_small.cc -i data_tiles_small.h --suffix _gif share/tiles/small/tiles_small_*.gif
	reswrap -o generated/data_tiles_small.h -h --suffix _gif share/tiles/small/tiles_small_*.gif
		
generated/data_tiles_small.h: generated/data_tiles_small.cc





generated/data_tiles_gnome.cc: share/tiles/gnome.gif
	reswrap -o generated/data_tiles_gnome.cc -i data_tiles_gnome.h --suffix _gif --prefix tiles_ share/tiles/gnome.gif
	reswrap -o generated/data_tiles_gnome.h -h --suffix _gif --prefix tiles_ share/tiles/gnome.gif
		
generated/data_tiles_gnome.h: generated/data_tiles_gnome.cc



generated/data_tiles_gnome2.cc: share/tiles/gnome2.gif
	reswrap -o generated/data_tiles_gnome2.cc -i data_tiles_gnome2.h --suffix _gif --prefix tiles_ share/tiles/gnome2.gif
	reswrap -o generated/data_tiles_gnome2.h -h --suffix _gif --prefix tiles_ share/tiles/gnome2.gif
		
generated/data_tiles_gnome2.h: generated/data_tiles_gnome2.cc


generated/data_buttons.cc: images/buttons.gif
	mkdir -p images/buttons
	convert images/buttons.gif images/buttons/button_%02d.gif
	reswrap -o generated/data_buttons.cc -i data_buttons.h --suffix _gif images/buttons/button_*.gif
	reswrap -o generated/data_buttons.h -h --suffix _gif images/buttons/button_*.gif

generated/data_buttons.h: generated/data_buttons.cc

generated/data_digits.cc: images/digits.gif
	mkdir -p images/digits
	convert images/digits.gif images/digits/digit_%02d.gif
	reswrap -o generated/data_digits.cc -i data_digits.h --suffix _gif images/digits/digit_*.gif
	reswrap -o generated/data_digits.h -h --suffix _gif images/digits/digit_*.gif

generated/data_digits.h: generated/data_digits.cc

generated/data_xmahjongg.h: generated/data_xmahjongg.cc
generated/data_xmahjongg.cc: images/xmahjongg.gif
	reswrap -o generated/data_xmahjongg.cc -i data_xmahjongg.h --suffix _gif images/xmahjongg.gif
	reswrap -o generated/data_xmahjongg.h -h --suffix _gif images/xmahjongg.gif
	
	
generated/data_background_default.h: generated/data_background_default.cc
generated/data_background_default.cc: share/backgrounds/default.gif
	reswrap -o generated/data_background_default.cc -i data_background_default.h --suffix _gif --prefix background_ share/backgrounds/default.gif
	reswrap -o generated/data_background_default.h -h --suffix _gif --prefix background_ share/backgrounds/default.gif	

generated/data_background_green.h: generated/data_background_green.cc
generated/data_background_green.cc: share/backgrounds/green.gif
	reswrap -o generated/data_background_green.cc -i data_background_green.h --suffix _gif --prefix background_ share/backgrounds/green.gif
	reswrap -o generated/data_background_green.h -h --suffix _gif --prefix background_ share/backgrounds/green.gif


generated/data_background_blue.h: generated/data_background_blue.cc
generated/data_background_blue.cc: share/backgrounds/blue.gif
	reswrap -o generated/data_background_blue.cc -i data_background_blue.h --suffix _gif --prefix background_ share/backgrounds/blue.gif
	reswrap -o generated/data_background_blue.h -h --suffix _gif --prefix background_ share/backgrounds/blue.gif

AM_CPPFLAGS = -I$(top_srcdir)/tools \
	-I$(top_srcdir)/cpputils/cpputilsshared  \
	-I$(top_srcdir)/cpputils/cpputilsshared/cpputilsformat \
	-I$(top_srcdir)/src  \
	-DNOWAMAS \
	-I$(top_srcdir)/liblcdf \
	-I$(top_srcdir)/generated \
	$(AUXLIBS_CFLAGS)  \
	$(LIBMAGICK_CFLAGS) \
	-std=c++11 \
	-fopenmp

noinst_LIBRARIES=tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a \
	liblcdf/liblcdf.a \
	generated/libgenerated.a

tools_libtools_a_SOURCES= \
	tools/arg.cpp \
	tools/database.cpp \
	tools/db.cpp \
	tools/dbi.cpp \
	tools/debug.cpp \
	tools/mysql_db.cpp \
	tools/odbc_db.cpp \
	tools/oracle_db.cpp \
	tools/pairs.cpp \
	tools/theme.cpp \
	tools/thread.cpp


cpputils_cpputilsshared_libcpputilsshared_a_SOURCES= \
		cpputils/cpputilsshared/backtrace.cc \
		cpputils/cpputilsshared/cppdir.cc \
		cpputils/cpputilsshared/leoini.cc \
		cpputils/cpputilsshared/logtool2.cc \
		cpputils/cpputilsshared/string_utils.cc \
		cpputils/cpputilsshared/vec_utils.cc \
		cpputils/cpputilsshared/xml.cc \
		cpputils/cpputilsshared/utf8.h \
		cpputils/cpputilsshared/utf8/core.h \
		cpputils/cpputilsshared/utf8/checked.h \
		cpputils/cpputilsshared/utf8/unchecked.h \
		cpputils/cpputilsshared/utf8/cpp11.h \
		cpputils/cpputilsshared/utf8/cpp17.h \
		cpputils/cpputilsshared/utf8_util.h \
		cpputils/cpputilsshared/utf8_util.cc


cpputils_cpputilsshared_cpputilsformat_libcpputilsformat_a_SOURCES= \
	cpputils/cpputilsshared/cpputilsformat/format1.cc \
	cpputils/cpputilsshared/cpputilsformat/format2.cc \
	cpputils/cpputilsshared/cpputilsformat/format2.h \
	cpputils/cpputilsshared/cpputilsformat/format1.h \
	cpputils/cpputilsshared/cpputilsformat/cformat.h \
	cpputils/cpputilsshared/cpputilsformat/wformat2.cc \
	cpputils/cpputilsshared/cpputilsformat/wformat2.h \
	cpputils/cpputilsshared/cpputilsformat/cwformat.h \
	cpputils/cpputilsshared/cpputilsformat/cwformat.cc

liblcdf_liblcdf_a_SOURCES= \
    liblcdf/vector.hh \
    liblcdf/vectorv.hh \
    liblcdf/vectorv.cc
    
BUILT_SOURCES=\
	generated/data_tiles_thick.cc \
	generated/data_tiles_thick.h \
	generated/data_tiles_thin.cc \
	generated/data_tiles_thin.h \
	generated/data_tiles_small.cc \
	generated/data_tiles_small.h \
	generated/data_tiles_gnome.h \
	generated/data_tiles_gnome.cc \
	generated/data_tiles_gnome2.h \
	generated/data_tiles_gnome2.cc \
	generated/data_buttons.h \
	generated/data_buttons.cc \
	generated/data_digits.h \
	generated/data_digits.cc \
	generated/data_xmahjongg.h \
	generated/data_xmahjongg.cc \
	generated/data_background_default.h \
	generated/data_background_default.cc \
	generated/data_background_green.h \
	generated/data_background_green.cc \
	generated/data_background_blue.h \
	generated/data_background_blue.cc	    

generated_libgenerated_a_SOURCES=\
	generated/data_tiles_thick.h \
	generated/data_tiles_thick.cc \
	generated/data_tiles_thin.h \
	generated/data_tiles_thin.cc \
	generated/data_tiles_small.h \
	generated/data_tiles_small.cc \
	generated/data_tiles_gnome.h \
	generated/data_tiles_gnome.cc \
	generated/data_tiles_gnome2.h \
	generated/data_tiles_gnome2.cc \
	generated/data_buttons.h \
	generated/data_buttons.cc \
	generated/data_digits.h \
	generated/data_digits.cc \
	generated/data_xmahjongg.h \
	generated/data_xmahjongg.cc \
	generated/data_background_default.h \
	generated/data_background_default.cc \
	generated/data_background_green.h \
	generated/data_background_green.cc \
	generated/data_background_blue.h \
	generated/data_background_blue.cc
		
fox_mahjongg_LDADD = \
	tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a \
	liblcdf/liblcdf.a \
	generated/libgenerated.a

LIBS= \
	$(AUXLIBS_LIBS) \
	$(LIBMAGICK_LIBS)	
	
AM_LDFLAGS= -fopenmp	
	
if MINGW
AM_LDFLAGS += -mwindows
# with -std=c++11 WIN32 is disabled (_WIN32) would be the valid one, so we define it in mingw.
AM_CPPFLAGS += -DWIN32
else
AM_LDFLAGS += -lX11
endif
