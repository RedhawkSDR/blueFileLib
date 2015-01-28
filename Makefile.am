#
# This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this 
# source distribution.
# 
# This file is part of REDHAWK blueFileLib.
# 
# REDHAWK blueFileLib is free software: you can redistribute it and/or modify it under the terms of 
# the GNU General Public License as published by the Free Software Foundation, either 
# version 3 of the License, or (at your option) any later version.
# 
# REDHAWK blueFileLib is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
# PURPOSE.  See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with this 
# program.  If not, see http://www.gnu.org/licenses/.
#
SUBDIRS =	\
		blue \
	  	utils \
		.

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libblueFileLib_v1.la

libblueFileLib_v1_la_SOURCES = \
libblue.la \
libutils.la

libblueFileLib_v1_la_LDFLAGS = -version-info 1:0:0

libdir = $(spkg_libdir)

pkgconfigdir = $(spkg_pkgconfig_dir)/
pkgconfig_DATA = blueFileLib_v1.pc

xmldir = $(spkg_dir)/
dist_xml_DATA = blueFileLib_v1.spd.xml

incdir = $(spkg_includedir)/
nobase_dist_inc_DATA = \
blue/ByteSwap.h \
blue/ExtendedHeader.h \
blue/Format.h \
blue/HeaderControlBlock.h \
blue/InternalKeywordBase.h \
blue/InternalKeyword.h \
blue/Keyword.h \
blue/MartesKey.h \
blue/MidasKey.h \
blue/UnitCode.h \
utils/utilsByteSwap.h \
utils/utilsError.h

distclean-local:
	rm -rf config.*
	rm -rf autom4te.cache
	rm -f acinclude.m4
	rm -f aclocal.m4
	rm -f configure
	rm -f depcomp
	rm -f install-sh
	rm -f ltmain.sh
	rm -f Makefile.in
	rm -f blue/Makefile.in
	rm -f utils/Makefile.in
	rm -f missing
	rm -rf .deps
	rm -rf m4
