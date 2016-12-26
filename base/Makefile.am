# Copyright (C) 2016 Ahmed Riza

# This file is part of MathFin.

# This program is free software: you  can redistribute it and/or modify it
# under the  terms of the GNU  General Public License as  published by the
# Free Software Foundation,  either version 3 of the License,  or (at your
# option) any later version.

# This  program  is distributed  in  the  hope  that  it will  be  useful,
# but  WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
# Public License for more details.

# You should have received a copy  of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>.


AM_CPPFLAGS = -std=c++11 $(BOOST_CPPFLAGS)

LDADD = libBase.la

this_includedir=${includedir}/${subdir}

this_include_HEADERS = \
	error.h

lib_LTLIBRARIES = libBase.la

libBase_la_SOURCES = \
	error.cpp

libBase_la_CXXFLAGS = $(BOOST_CPPFLAGS)

libBase_la_LDFLAGS = -version-info 1:0:0

check_PROGRAMS = baseTest
baseTest_SOURCES = errorTest.cpp
baseTest_LDADD =	$(LDADD)
TESTS = $(check_PROGRAMS)
EXTRA_DIST = $(TESTS)
