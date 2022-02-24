bin_PROGRAMS=fox-mahjongg

fox_mahjongg_SOURCES=\
		src/colored_output.cc\
		src/main.cc\
		src/OutDebug.cc\
		src/DetectLocale.cc \
		src/DetectLocale.h \
		src/read_file.h \
		src/read_file.cc 

AM_CPPFLAGS = -I$(top_srcdir)/tools \
	-I$(top_srcdir)/cpputils/cpputilsshared  \
	-I$(top_srcdir)/cpputils/cpputilsshared/cpputilsformat \
	-I$(top_srcdir)/src  \
	-DNOWAMAS \
	-std=c++11

noinst_LIBRARIES=tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a

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
		cpputils/cpputilsshared/aes_crypt_util.cc \
		cpputils/cpputilsshared/backtrace.cc \
		cpputils/cpputilsshared/blockupdate.cc \
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

fox_mahjongg_LDADD = tools/libtools.a cpputils/cpputilsshared/libcpputilsshared.a cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a
