SUBDIRS =	\
		blue \
	  	utils \
		.

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libblueFileLib.la
libdir = $(spkg_libdir)

pkgconfigdir = $(spkg_pkgconfig_dir)/
pkgconfig_DATA = blueFileLib_v1.pc

xmldir = $(spkg_dir)/
dist_xml_DATA = blueFileLib_v1.spd.xml


datadir = $(spkg_impldir)

incdir = $(spkg_includedir)

libblueFileLib_la_SOURCES = \
libblue.la \
libutils.la

dist_inc_DATA = \
blue/*.h \
utils/*.h

libblueFileLib_la_LDFLAGS = -version-info 1:0:0

libblueFileLib_la_LIBADD = \
$(top_builddir)/blue/libblue.la \
$(top_builddir)/utils/libutils.la

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
