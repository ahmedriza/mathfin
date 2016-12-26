AC_CONFIG_MACRO_DIRS([m4])

AC_INIT([MathFin], [1.0], [ahmed.riza@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_LIBTOOL

AC_ENABLE_SHARED
AC_DISABLE_STATIC

BOOST_REQUIRE

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  base/Makefile
  math/Makefile
  time/Makefile
  ])
AC_OUTPUT
