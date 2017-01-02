
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

AM_CPPFLAGS = -std=c++11 $(BOOST_CPPFLAGS) -I$(top_srcdir) -I$(top_builddir)

this_includedir=${includedir}/${subdir}

this_include_HEADERS = \
	actual360.hpp \
	actualactual.hpp

# noinst_LTLIBRARIES = libDayCounters.la
# libDayCounters_la_SOURCES = actualactual.cpp
# libDayCounters_la_CXXFLAGS = -std=c++11 $(BOOST_CPPFLAGS)

check_PROGRAMS = daycountersTest
daycountersTest_SOURCES = actualactualTest.cpp
daycountersTest_LDADD = ../libTime.la ${top_builddir}/base/libBase.la
TESTS = $(check_PROGRAMS)
EXTRA_DIST = $(TESTS)
