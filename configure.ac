
dnl @synopsis CXX_FLAGS_CHECK [compiler flags]                                        
dnl @summary check whether compiler supports given C++ flags or not                   
AC_DEFUN([CXX_FLAGS_CHECK],                                                            
[dnl                                                                                  
  AC_MSG_CHECKING([if $CXX supports $1])
  AC_LANG_PUSH([C++])
  ac_saved_cxxflags="$CXXFLAGS"                                                       
  CXXFLAGS="-Werror $1"                                                               
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],                                            
    [AC_MSG_RESULT([yes])],                                                           
    [AC_MSG_ERROR([no])]                                                              
  )                                                                                   
  CXXFLAGS="$ac_saved_cxxflags"                                                       
  AC_LANG_POP([C++])
])

dnl @synopsis LD_FLAGS_CHECK [compiler flags]                                        
dnl @summary check whether linker supports given C++ flags or not                   
AC_DEFUN([LD_FLAGS_CHECK],                                                            
[dnl                                                                                  
  AC_MSG_CHECKING([if $CXX supports $1])
  AC_LANG_PUSH([C++])
  ac_saved_ldflags="$LDFLAGS"                                                       
  LDFLAGS="-Werror $1"                                                               
  AC_LINK_IFELSE([AC_LANG_PROGRAM([])],                                            
    [AC_MSG_RESULT([yes])],                                                           
    [AC_MSG_ERROR([no])]                                                              
  )                                                                                   
  LDFLAGS="$ac_saved_ldflags"                                                       
  AC_LANG_POP([C++])
])


AC_INIT(fox-mahjongg, 0.4)
AM_INIT_AUTOMAKE([subdir-objects -Wall])


AC_CANONICAL_HOST
case $host_os in
  *mingw*) mingw=true ;;
  *) mingw=false ;;
esac
AM_CONDITIONAL([MINGW], [test x$mingw = xtrue])


AC_PROG_CC
AC_CONFIG_FILES([ po/Makefile.in
Makefile
])
AC_PROG_RANLIB
AM_PROG_AR
AC_PROG_CXX
AC_LANG(C++)
AC_PROG_INSTALL

ac_extra_cxxx_flags=""
EXTRA_LDFLAGS=""

CXX_FLAGS_CHECK([-std=c++11])
CXX_FLAGS_CHECK([-fopenmp])


AC_ARG_WITH([fox16],
  [AS_HELP_STRING([--with-fox16],[use FOX-Toolkit 1.6])],
  [],
  [with_fox16=no]
)

AC_ARG_WITH([fox17],
  [AS_HELP_STRING([--with-fox17],[use FOX-Toolkit 1.7])],
  [],
  [with_fox17=no]
)

AS_IF([test "x$with_fox16" != "xno"],
    [PKG_CHECK_MODULES([LIBFOX], [fox16],[FOX16="yes"],[FOX16="no"])]
)
  
AS_IF([test "x$with_fox17" != "xno"],
    [PKG_CHECK_MODULES([LIBFOX], [fox17],[FOX17="yes"],[FOX17="no"])]
)
    
AS_IF([test "x${FOX16}x${FOX17}" == "xx" ],
	PKG_CHECK_MODULES([LIBFOX], [fox])
)





AC_ARG_WITH([magick6],
  [AS_HELP_STRING([--with-magick6],[use ImageMagick 6])],
  [],
  [with_magick6=no]
)

AC_ARG_WITH([magick7],
  [AS_HELP_STRING([--with-magick7],[use ImageMagick 7])],
  [],
  [with_magick7=no]
)

AS_IF([test "x$with_magick6" != "xno"],
    [PKG_CHECK_MODULES([LIBMAGICK], [Magick++-6.Q16],[MAGICK6="yes"],[MAGICK6="no"])]
) 
  
AS_IF([test "x$with_magick7" != "xno"],
    [PKG_CHECK_MODULES([LIBMAGICK], [Magick++-7.Q16HDRI],[MAGICK7="yes"],[MAGICK7="no"])]
)   
    
AS_IF([test "x${MAGICK6}x${MAGICK7}" == "xx" ],
    [PKG_CHECK_MODULES([LIBMAGICK], [Magick++])]
) 




AM_GNU_GETTEXT([external])
AM_CONDITIONAL([USE_NLS], [test "x${USE_NLS}" = "xyes"])

AC_OUTPUT
