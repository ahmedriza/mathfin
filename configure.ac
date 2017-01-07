dnl Autoconf script for MathFin
dnl To rebuild the 'configure' script from this, execute the command
dnl     autogen
dnl in the directory containing this script.
dnl
dnl Copyright (C) 2016 Ahmed Riza
dnl
dnl This file is part of MathFin.
dnl
dnl This program is free software: you  can redistribute it and/or modify it
dnl under the  terms of the GNU  General Public License as  published by the
dnl Free Software Foundation,  either version 3 of the License,  or (at your
dnl option) any later version.
dnl
dnl This  program  is distributed  in  the  hope  that  it will  be  useful,
dnl but  WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
dnl Public License for more details.
dnl
dnl You should have received a copy  of the GNU General Public License along
dnl with this program. If not, see <http://www.gnu.org/licenses/>.

AC_CONFIG_MACRO_DIR([m4])

AC_INIT([MathFin], [1.0], [ahmed.riza@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects foreign])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_LIBTOOL

AC_ENABLE_SHARED
AC_DISABLE_STATIC

BOOST_REQUIRE

AC_CHECK_PROGS([DOXYGEN], [doxygen])
  if test -z "$DOXYGEN";
    then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
  fi

AM_CONDITIONAL([HAVE_DOXYGEN],
  [test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN],
  [AC_CONFIG_FILES([docs/Doxyfile])])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  base/Makefile
  docs/Makefile
  math/Makefile
  time/Makefile
  time/daycounters/Makefile
  time/calendars/Makefile
  ])
AC_OUTPUT
