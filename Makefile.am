bin_PROGRAMS=fox-mahjongg

fox_mahjongg_SOURCES=\
		tools_config.h\
		src/colored_output.cc\
		src/colored_output.h\
		src/main.h\
		src/main.cc\
		src/OutDebug.cc\
		src/OutDebug.h\
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
		src/tiles_dorwhite.h \
		src/tiles_dorwhite.cc \
		src/tiles_dorothys.h \
		src/tiles_dorothys.cc \
		src/tiles_real.h \
		src/tiles_real.cc \
		src/FXPixelBuffer.h \
		src/FXPixelBuffer.cc \
		src/FXPixelBufferObject.h \
		src/FXPixelBufferObject.cc \
		src/FXRadioGroup.h \
		src/FXRadioGroup.cc \
		src/builtin_layouts.h \
		src/builtin_layouts.cc
		  	 
			  

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



generated/data_tiles_dorwhite.cc: share/tiles/dorwhite.gif
	reswrap -o generated/data_tiles_dorwhite.cc -i data_tiles_dorwhite.h --suffix _gif --prefix tiles_ share/tiles/dorwhite.gif
	reswrap -o generated/data_tiles_dorwhite.h -h --suffix _gif --prefix tiles_ share/tiles/dorwhite.gif
		
generated/data_tiles_dorwhite.h: generated/data_tiles_dorwhite.cc



generated/data_tiles_dorothys.cc: share/tiles/dorothys.gif
	reswrap -o generated/data_tiles_dorothys.cc -i data_tiles_dorothys.h --suffix _gif --prefix tiles_ share/tiles/dorothys.gif
	reswrap -o generated/data_tiles_dorothys.h -h --suffix _gif --prefix tiles_ share/tiles/dorothys.gif
		
generated/data_tiles_dorothys.h: generated/data_tiles_dorothys.cc




generated/data_tiles_real.cc: share/tiles/real.gif
	reswrap -o generated/data_tiles_real.cc -i data_tiles_real.h --suffix _gif --prefix tiles_ share/tiles/real*.gif
	reswrap -o generated/data_tiles_real.h -h --suffix _gif --prefix tiles_ share/tiles/real*.gif
		
generated/data_tiles_real.h: generated/data_tiles_real.cc



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

generated/data_builtin_layouts.h: generated/data_builtin_layouts.cc
generated/data_builtin_layouts.cc: share/layouts/*
	reswrap --ascii -o generated/data_builtin_layouts.cc -i data_builtin_layouts.h --prefix builtin_layout_ share/layouts/*
	reswrap --ascii -o generated/data_builtin_layouts.h -h --prefix builtin_layout_ share/layouts/*

generated/data_readme.h: generated/data_readme.cc
generated/data_readme.cc: README.md
	reswrap --ascii -o generated/data_readme.cc -i data_readme.h --prefix data_ README.md LICENSE
	reswrap --ascii -o generated/data_readme.h -h --prefix data_  README.md LICENSE

AM_CPPFLAGS = -I$(top_srcdir)/tools \
	-I$(top_srcdir)/cpputils/cpputilsshared  \
	-I$(top_srcdir)/cpputils/cpputilsshared/cpputilsformat \
	-I$(top_srcdir)/src  \
	-DNOWAMAS \
	-I$(top_srcdir)/liblcdf \
	-I$(top_srcdir)/generated \
	$(LIBFOX_CFLAGS)  \
	$(LIBMAGICK_CFLAGS) \
	-std=c++11 \
	-fopenmp \
	-DLOCALEDIR=\"$(localedir)\"

noinst_LIBRARIES=tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a \
	liblcdf/liblcdf.a \
	generated/libgenerated.a

tools_libtools_a_SOURCES= \
	tools/arg.cpp \
	tools/arg.h \
	tools/database.cpp \
	tools/database.h \
	tools/db.cpp \
	tools/db.h \
	tools/dbi.cpp \
	tools/dbi.h \
	tools/debug.cpp \
	tools/debug.h \
	tools/mysql_db.cpp \
	tools/mysql_db.h \
	tools/odbc_db.cpp \
	tools/odbc_db.h \
	tools/oracle_db.cpp \
	tools/oracle_db.h \
	tools/pairs.cpp \
	tools/pairs.h \
	tools/theme.cpp \
	tools/theme.h \
	tools/thread.cpp \
	tools/thread.h


cpputils_cpputilsshared_libcpputilsshared_a_SOURCES= \
		cpputils/cpputilsshared/backtrace.cc \
		cpputils/cpputilsshared/backtrace.h \
		cpputils/cpputilsshared/cppdir.cc \
		cpputils/cpputilsshared/cppdir.h \
		cpputils/cpputilsshared/leoini.cc \
		cpputils/cpputilsshared/leoini.h \
		cpputils/cpputilsshared/string_utils.cc \
		cpputils/cpputilsshared/string_utils.h \
		cpputils/cpputilsshared/xml.cc \
		cpputils/cpputilsshared/xml.h \
		cpputils/cpputilsshared/stderr_exception.h \
		cpputils/cpputilsshared/ref.h \
		cpputils/cpputilsshared/range.h \
		cpputils/cpputilsshared/stderr_exception.h \
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
	cpputils/cpputilsshared/cpputilsformat/format.h \
	cpputils/cpputilsshared/cpputilsformat/cformat.h \
	cpputils/cpputilsshared/cpputilsformat/wformat2.cc \
	cpputils/cpputilsshared/cpputilsformat/wformat2.h \
	cpputils/cpputilsshared/cpputilsformat/cwformat.h \
	cpputils/cpputilsshared/cpputilsformat/cwformat.cc

liblcdf_liblcdf_a_SOURCES= \
    liblcdf/vector.hh \
    liblcdf/vectorv.cc
    


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
	generated/data_tiles_dorwhite.h \
	generated/data_tiles_dorwhite.cc \
	generated/data_tiles_dorothys.h \
	generated/data_tiles_dorothys.cc \
	generated/data_tiles_real.h \
	generated/data_tiles_real.cc \
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
	generated/data_background_blue.cc \
	generated/data_builtin_layouts.h \
	generated/data_builtin_layouts.cc \
	generated/data_readme.h \
	generated/data_readme.cc
	
BUILT_SOURCES=\
	 $(generated_libgenerated_a_SOURCES)
		
fox_mahjongg_LDADD = \
	tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a \
	liblcdf/liblcdf.a \
	generated/libgenerated.a

LIBS= \
	$(LIBFOX_LIBS) \
	$(LIBMAGICK_LIBS)	
	
AM_LDFLAGS= -fopenmp	
	
if MINGW
AM_LDFLAGS += -mwindows
# with -std=c++11 WIN32 is disabled (_WIN32) would be the valid one, so we define it in mingw.
AM_CPPFLAGS += -DWIN32
else
AM_LDFLAGS += -lX11
endif


if USE_NLS
PO_SUBDIR = po
LIBS += $(LTLIBINTL)
AM_CPPFLAGS += -DENABLE_NLS
endif

SUBDIRS = $(PO_SUBDIR)

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = m4/ChangeLog \
	images/buttons.gif \
	images/digits.gif \
	images/xmahjongg.gif \
	images/xmahjongg.ico \
	share/backgrounds/blue.gif \
	share/backgrounds/green.gif \
	share/backgrounds/default.gif \
	share/tiles/dorothys.gif \
	share/tiles/dorwhite.gif \
	share/tiles/gnome2.gif \
	share/tiles/gnome.gif \
	share/tiles/real_background.gif \
	share/tiles/real.gif \
	share/tiles/small.gif \
	share/tiles/thick.gif \
	share/tiles/thin.gif \
	share/layouts/arena \
	share/layouts/arrow \
	share/layouts/boar \
	share/layouts/bridge \
	share/layouts/ceremonial \
	share/layouts/deepwell \
	share/layouts/default \
	share/layouts/dog \
	share/layouts/dragon \
	share/layouts/farandole \
	share/layouts/hare \
	share/layouts/horse \
	share/layouts/hourglass \
	share/layouts/monkey \
	share/layouts/ox \
	share/layouts/papillon \
	share/layouts/ram \
	share/layouts/rat \
	share/layouts/rooster \
	share/layouts/schoon \
	share/layouts/snake \
	share/layouts/theater \
	share/layouts/tiger \
	share/layouts/wedges \
	README.md \
	README \
	LICENSE \
	liblcdf/vector.cc
	
	
	
	
