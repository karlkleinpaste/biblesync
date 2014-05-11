# ---------------------------------------------------------------------
# Initialisation
# ---------------------------------------------------------------------

# Version change: Change line 8 only !
# Change it immediately after a release

AC_INIT(biblesync, 0.0.1, biblesync@kleinpaste.org, biblesync, https://github.com/karlkleinpaste/biblesync)
AC_CONFIG_SRCDIR(biblesync-v1.png)
AC_PREREQ(2.52)
AC_REVISION($Revision: 1.45 $)

AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE

AM_CONFIG_HEADER(include/config.h)

AC_CONFIG_MACRO_DIR([m4])

case $host_os in
     mingw*)
	   # both lines necessary to convince gcc to build dll
	   LIBS="$LIBS -no-undefined";
	   export lt_cv_deplibs_check_method=pass_all;
	   ;;
esac

# ---------------------------------------------------------------------
# Check Programs
# ---------------------------------------------------------------------
CFLAGS=" $CFLAGS"
CXXFLAGS=" $CXXFLAGS"
AC_LANG(C++)
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AC_C_BIGENDIAN


# ---------------------------------------------------------------------
# Enable options
# ---------------------------------------------------------------------
AC_ARG_ENABLE(debug,
	AC_HELP_STRING([--enable-debug],[build debug library (default=no)]),,enable_debug=no)
AC_ARG_ENABLE(warnings,
	AC_HELP_STRING([--enable-warnings],[build with compiler warnings as errors (default=no)]),,enable_warnings=no)
AM_MAINTAINER_MODE

# ---------------------------------------------------------------------
# Debug and profile
# ---------------------------------------------------------------------

# these are first because the SET AM_C.*FLAGS, not just append
if test x$enable_debug = xyes; then
  GCJFLAGS="-g -O0"
  if test x$ac_cv_prog_cc_g = xyes; then
    AM_CFLAGS="-g3 -O0 -Wall -Werror"
  else
    AM_CFLAGS="-O0 -Wall -Werror"
  fi
  if test x$ac_cv_prog_cxx_g = xyes; then
    AM_CXXFLAGS="-g3 -O0 -Wall -Werror -Woverloaded-virtual"
  else
    AM_CXXFLAGS="-O0 -Wall -Werror -Woverloaded-virtual"
  fi
else
  AM_CFLAGS="-O3"
  AM_CXXFLAGS="-O3"
fi

AM_CFLAGS="$AM_CFLAGS -fPIC"
AM_CXXFLAGS="$AM_CXXFLAGS -fPIC"

# ---------------------------------------------------------------------
# Find CppUnit
# ---------------------------------------------------------------------
# Locate CppUnit (minimum version 1.8.0) for testing.  
AM_PATH_CPPUNIT(1.8.0)

# You can set up an automake conditional and use it to conditionally
# build cppunit-using test programs.
AM_CONDITIONAL(HAVE_CPPUNIT, test "$CPPUNIT_LIBS")


# ---------------------------------------------------------------------
# Find pkg-config
# ---------------------------------------------------------------------
use_pkgconfig=yes
AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
if test x$PKG_CONFIG = xno ; then
  AC_MSG_WARN([*** pkg-config not found. See http://www.freedesktop.org/software/pkgconfig/])
  AC_MSG_WARN([not using pkg-config])
  use_pkgconfig=no
fi

if $PKG_CONFIG --atleast-pkgconfig-version 0.14 ; then
  :
else
  AC_MSG_WARN([*** pkg-config too old; version 0.14 or better required.])
  AC_MSG_WARN([not using pkg-config])
  use_pkgconfig=no
fi

AM_CXXFLAGS="$AM_CXXFLAGS -ftemplate-depth-25"

if test x$enable_warnings = xyes; then
  AM_CFLAGS="$AM_CFLAGS -Werror"
  AM_CXXFLAGS="$AM_CXXFLAGS -Werror -Woverloaded-virtual"
fi

# ---------------------------------------------------------------------
# Alter global conf directory only if not /etc
# ---------------------------------------------------------------------

changequote(<<,>>)
V1=`expr $VERSION : '\([0-9]*\)\.[0-9]*\.*[0-9]*\.*[0-9]*'`
V2=`expr $VERSION : '[0-9]*\.\([0-9]*\)\.*[0-9]*\.*[0-9]*'`
V3=`expr $VERSION : '[0-9]*\.[0-9]*\.*\([0-9]*\)\.*[0-9]*'`
V4=`expr $VERSION : '[0-9]*\.[0-9]*\.*[0-9]*\.*\([0-9]*\)'`
changequote([,])

BIBLESYNC_VERSION_STR=$VERSION
BIBLESYNC_VERSION_MAJOR=$V1
BIBLESYNC_VERSION_MINOR=$V2
BIBLESYNC_VERSION_MICRO=$V3
if test "$V4" = "" ; then V4=0; fi
BIBLESYNC_VERSION_NANO=$V4

if test "$V2" -le 9 ; then V2=0$V2 ; fi
if test "$V3" -le 9 ; then V3=00$V3 ; elif test "$V3" -le 99 ; then V3=0$V3 ; fi
if test "$V4" -le 9 ; then V4=00$V4 ; elif test "$V4" -le 99 ; then V4=0$V4 ; fi
BIBLESYNC_VERSION_NUM=$V1$V2$V3$V4

AC_SUBST(BIBLESYNC_VERSION_NUM)
AC_SUBST(BIBLESYNC_VERSION_STR)
AC_SUBST(BIBLESYNC_VERSION_MAJOR)
AC_SUBST(BIBLESYNC_VERSION_MINOR)
AC_SUBST(BIBLESYNC_VERSION_MICRO)
AC_SUBST(BIBLESYNC_VERSION_NANO)



# ---------------------------------------------------------------------
# Substitute variables into makefiles
# ---------------------------------------------------------------------
AC_SUBST(CC)
AC_SUBST(enable_debug)

AC_SUBST(AM_CXXFLAGS)
AC_SUBST(AM_CFLAGS)

AC_SUBST(target_cpu)
AC_SUBST(target_vendor)
AC_SUBST(target_os)

AC_SUBST(target_system)
AC_SUBST(target_mingw32)


# ---------------------------------------------------------------------
# Conditional variables
# ---------------------------------------------------------------------

AM_CONDITIONAL(SHAREDLIB, test x$enable_shared = xyes)
AM_CONDITIONAL(USE_PKGCONF, test x$use_pkgconfig = xyes)

# ---------------------------------------------------------------------
# Final output
# ---------------------------------------------------------------------
AC_CONFIG_FILES(Makefile lib/Makefile src/Makefile biblesync.pc include/biblesync-version.hh biblesync.spec)
AC_OUTPUT

echo
echo "Configuration:"
echo "  libdir:   $libdir"
echo "  debug:    $enable_debug"
echo "  warnings: $enable_warnings"
echo
