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

if HAVE_DOXYGEN
directory = $(top_srcdir)/docs/man/man3/

# dist_man_MANS = $(directory)/man_page_1.3 $(directory)/man_page_2.3

$(directory)/man_page_1.3: doxyfile.stamp
$(directory)/man_page_2.3: doxyfile.stamp

doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_srcdir)/docs/man
	rm -rf $(top_srcdir)/docs/latex
	rm -rf $(top_srcdir)/docs/html

endif
