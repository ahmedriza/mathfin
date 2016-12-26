
lib_LTLIBRARIES = libMath.la

libMath_la_SOURCES = math.cpp

libMath_la_LDFLAGS = -version-info 1:0:0

check_PROGRAMS = mathTest
mathTest_SOURCES = mathTest.cpp
mathTest_LDADD =	$(LDADD)
TESTS = $(check_PROGRAMS)
EXTRA_DIST = $(TESTS)
