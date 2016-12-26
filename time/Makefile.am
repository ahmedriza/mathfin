AM_CPPFLAGS = -std=c++11 $(BOOST_CPPFLAGS)

this_includedir=${includedir}/${subdir}

this_include_HEADERS = \
	date.h \
	businessdayconvention.h

lib_LTLIBRARIES = libTime.la

libTime_la_SOURCES = \
	date.cpp \
	businessdayconvention.cpp

libTime_la_CXXFLAGS = -std=c++11 $(BOOST_CPPFLAGS)

libTime_la_LDFLAGS = -version-info 1:0:0

check_PROGRAMS = timeTest
timeTest_SOURCES = businessdayconventionTest.cpp
timeTest_LDADD =	libTime.la ${top_builddir}/base/libBase.la
TESTS = $(check_PROGRAMS)
EXTRA_DIST = $(TESTS)
