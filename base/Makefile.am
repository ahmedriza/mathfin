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
