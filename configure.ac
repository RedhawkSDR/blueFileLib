# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
#
# This file is part of REDHAWK blueFileLib.
#
# REDHAWK blueFileLib is free software: you can redistribute
# it and/or modify it under the terms of the GNU General Public License as 
# published by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# REDHAWK blueFileLib is distributed in the hope that it 
# will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this 
# program.  If not, see http://www.gnu.org/licenses/.
#
AC_PREREQ([2.63])
AC_INIT(blueFileLib, [1.0.0])

AC_USE_SYSTEM_EXTENSIONS

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])

AM_PROG_LIBTOOL

#################### CXXFLAGS ####################
# Save the old settings
OLD_CXXFLAGS="$CXXFLAGS"

# Test using the c++ compiler
AC_LANG(C++)

# Search for which compiler to use
AC_PROG_CXX("CC" "g++")

CXXFLAGS=$OLD_CXXFLAGS

################ Strict Building #################
CXXFLAGS="$CXXFLAGS -Wall -Werror"

################# Check Headers ##################
AC_CHECK_HEADERS([stdint.h sys/types.h])

################## Check Types ###################
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT8_T
AC_TYPE_UINT8_T
AC_TYPE_INT16_T
AC_TYPE_UINT16_T
AC_TYPE_INT32_T
AC_TYPE_UINT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT64_T
AC_TYPE_SIZE_T

################# Check Functions ################
AC_CHECK_FUNCS([memcpy memset])

################### ENDIANNESS ###################
AC_C_BIGENDIAN(	[AC_DEFINE(BIG_ENDIAN, 1, [Big endian machine])],
		[AC_DEFINE(LITTLE_ENDIAN, 1, [Little endian machine])], [], [])

AC_PREFIX_DEFAULT(${SDRROOT})
#change this number to reflect the variation you are creating for this library
AC_SUBST([spkg_variation],['v1'])
#name of the impl the package should use
AC_SUBST([spkg_base],[cpp])
AC_SUBST([OS_NAME],[`uname -s`])
AC_SUBST([ARCH],[`uname -p`])
AC_SUBST([spkg_dir],['${prefix}'/dom/deps/${PACKAGE_NAME}_${spkg_variation}])
AC_SUBST([spkg_impl],[${spkg_base}])
AC_SUBST([spkg_impl2],['${spkg_base}'])
AC_SUBST([spkg_lib],[lib])
AC_SUBST([spkg_impldir],['${spkg_dir}/${spkg_impl}'])
AC_SUBST([spkg_libdir],['${spkg_dir}/${spkg_impl}/${spkg_lib}'])
AC_SUBST([spkg_pkgconfig_dir],['${spkg_libdir}/pkgconfig'])
AC_SUBST([spkg_includedir],['${spkg_dir}/${spkg_impl}/include'])

AC_CONFIG_FILES([Makefile
                 blue/Makefile
                 utils/Makefile])
AC_CONFIG_FILES([${PACKAGE_NAME}_${spkg_variation}.pc:packageName.pc.in])
AC_CONFIG_FILES([${PACKAGE_NAME}_${spkg_variation}.spd.xml:packageName.spd.xml.in])

AC_OUTPUT

