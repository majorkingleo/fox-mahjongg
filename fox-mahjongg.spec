#
# spec file for package fox-mahjongg
#
# Copyright (c) 2022 by Martin Oberzalek.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#


Name:           fox-mahjongg
Version:        0.4
Release:        kingleo.1
Summary:        Free portable Mahjongg game 
License:        GPL3
Group:          Games
Url:            https://sourceforge.net/projects/fox-mahjongg/

Source0:        fox-mahjongg-%version.tar.gz
BuildRequires:  gcc-c++
BuildRequires:  fox16-devel
BuildRequires:  pkgconfig
%if 0%{?suse_version} > 1220
BuildRequires:  pkgconfig(glu)
%endif
BuildRoot:      %{_tmppath}/%{name}-v-%{version}-build
Requires:		libFOX-1_6-0

%description
This Mahjongg version runs on Windows as Linux. The intention was creating an ad free and no "annoying in game payments" version of mahjongg. It is a xmahjongg clone that was reworked to run on different plattforms. 

%package -n %version
Summary:        Free portable Mahjongg game
Group:          Games
Provides:       fox-mahjongg = %version

%description -n %version

%prep
%setup -q -n fox-mahjongg-%{version}

%build
%configure

make %{?_smp_mflags}

%install
%makeinstall DESTDIR=$RPM_BUILD_ROOT

%files 
%defattr(-,root,root)
%{_bindir}/fox-mahjongg
%{_datadir}/locale

