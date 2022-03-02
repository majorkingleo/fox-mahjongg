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
		src/data_tiles_thick.cc \
		src/data_tiles_thick.h \
		src/tiles_thick.h \
		src/tiles_thick.cc \
		src/data_buttons.h \
		src/data_buttons.cc \
		src/data_digits.h \
		src/data_digits.cc \
		src/FXPixelBuffer.h \
		src/FXPixelBuffer.cc \
		src/FXPixelBufferObject.h \
		src/FXPixelBufferObject.cc
		
BUILT_SOURCES=src/data_tiles_thick.cc \
			  src/data_tiles_thick.h \
			  src/data_buttons.h \
			  src/data_buttons.cc \
			  src/data_digits.h \
			  src/data_digits.cc
			  

src/data_tiles_thick.cc: share/tiles/thick.gif
	mkdir -p share/tiles/thick
	convert share/tiles/thick.gif share/tiles/thick/tiles_thick_%02d.gif
	reswrap -o src/data_tiles_thick.cc -i data_tiles_thick.h --suffix _gif share/tiles/thick/tiles_thick_*.gif
	reswrap -o src/data_tiles_thick.h -h --suffix _gif share/tiles/thick/tiles_thick_*.gif
		
src/data_tiles_thick.h: src/data_tiles_thick.cc

src/data_buttons.cc: images/buttons.gif
	mkdir -p images/buttons
	convert images/buttons.gif images/buttons/button_%02d.gif
	reswrap -o src/data_buttons.cc -i data_buttons.h --suffix _gif images/buttons/button_*.gif
	reswrap -o src/data_buttons.h -h --suffix _gif images/buttons/button_*.gif

src/data_buttons.h: src/data_buttons.cc

src/data_digits.cc: images/digits.gif
	mkdir -p images/digits
	convert images/digits.gif images/digits/digit_%02d.gif
	reswrap -o src/data_digits.cc -i data_digits.h --suffix _gif images/digits/digit_*.gif
	reswrap -o src/data_digits.h -h --suffix _gif images/digits/digit_*.gif

src/data_digits.h: src/data_digits.cc

AM_CPPFLAGS = -I$(top_srcdir)/tools \
	-I$(top_srcdir)/cpputils/cpputilsshared  \
	-I$(top_srcdir)/cpputils/cpputilsshared/cpputilsformat \
	-I$(top_srcdir)/src  \
	-DNOWAMAS \
	-std=c++11 \
	-I$(top_srcdir)/liblcdf \
	$(AUXLIBS_CFLAGS)  \
	$(LIBMAGICK_CFLAGS)

noinst_LIBRARIES=tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a \
	liblcdf/liblcdf.a	

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
	liblcdf/clp.c \
    liblcdf/fmalloc.c \
    liblcdf/giffunc.c \
	liblcdf/gifread.c \
	liblcdf/gifx.c \
    liblcdf/permstr.hh \
    liblcdf/permstr.cc \
    liblcdf/straccum.hh \
    liblcdf/straccum.cc \
    liblcdf/string.hh \
    liblcdf/string.cc \
    liblcdf/vector.hh \
    liblcdf/vectorv.cc \
	liblcdf/gif.h \
	liblcdf/gifx.h 
	

fox_mahjongg_LDADD = \
	tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a \
	liblcdf/liblcdf.a

LIBS= \
	$(AUXLIBS_LIBS) \
	$(LIBMAGICK_LIBS)

if MINGW
AM_LDFLAGS = -mwindows
else
AM_LDFLAGS = -lX11
endif
