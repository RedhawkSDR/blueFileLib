#!/usr/bin/env python
#
# This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this 
# source distribution.
# 
# This file is part of REDHAWK blueFileLib library.
# 
# REDHAWK blueFileLib library is free software: you can redistribute it and/or modify it under the terms of 
# the GNU General Public License as published by the Free Software Foundation, either 
# version 3 of the License, or (at your option) any later version.
# 
# REDHAWK blueFileLib library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
# PURPOSE.  See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with this 
# program.  If not, see http://www.gnu.org/licenses/.
#
%{!?_sdrroot: %define _sdrroot /var/redhawk/sdr}
%define _prefix %{_sdrroot}

Name:           blueFileLib
Version:        1.0.0
Release:        1%{?dist}
Summary:        Component Library %{name}

Group:          REDHAWK/Dependencies
License:        GPLv3+
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

Requires(pre):  redhawk
BuildRequires:  autoconf automake libtool

%description
BLUE/MIDAS File Helper Library %{name}
 * Commit: __REVISION__
 * Source Date/Time: __DATETIME__

%package devel
Summary:        %{name} development package
Group:          REDHAWK/Dependencies
Requires:       %{name} = %{version}

%description devel
Development headers and libraries for %{name}

%prep
%setup -q

%build
export SDRROOT=%{_sdrroot}
./reconf
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,redhawk,redhawk)
%dir %{_prefix}/dom/deps/blueFileLib_v1
%{_prefix}/dom/deps/blueFileLib_v1/blueFileLib_v1.spd.xml
%dir %{_prefix}/dom/deps/blueFileLib_v1/cpp
%dir %{_prefix}/dom/deps/blueFileLib_v1/cpp/lib
%{_prefix}/dom/deps/blueFileLib_v1/cpp/lib/libblueFileLib_v1.so*
%dir %{_prefix}/dom/deps/blueFileLib_v1/cpp/lib/pkgconfig
%{_prefix}/dom/deps/blueFileLib_v1/cpp/lib/pkgconfig/blueFileLib_v1.pc

%files devel
%defattr(-,redhawk,redhawk)
%{_prefix}/dom/deps/blueFileLib_v1/cpp/lib/libblueFileLib_v1.a
%{_prefix}/dom/deps/blueFileLib_v1/cpp/lib/libblueFileLib_v1.la
%dir %{_prefix}/dom/deps/blueFileLib_v1/cpp/include
%dir %{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/ByteSwap.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/ExtendedHeader.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/Format.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/HeaderControlBlock.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/InternalKeywordBase.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/InternalKeyword.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/Keyword.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/MartesKey.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/MidasKey.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/blue/UnitCode.h
%dir %{_prefix}/dom/deps/blueFileLib_v1/cpp/include/utils
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/utils/utilsByteSwap.h
%{_prefix}/dom/deps/blueFileLib_v1/cpp/include/utils/utilsError.h
