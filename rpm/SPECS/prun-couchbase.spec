Summary:	Prun job serialization library
Name:		prun-couchbase
Version:	0.1
Release:	1%{?dist}

License:	Apache License, Version 2.0
Group:		System Environment/Libraries
URL:		https://github.com/zhka/prun-couchbase
Source0:	%{name}-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:	cmake
BuildRequires:	boost-devel
BuildRequires:	libcouchbase-devel

Requires:       libcouchbase2-core
Requires:       prun-master

%description
Prun-couchbase is a prun job serialization library


%package prun-couchbase
Summary:	Prun job serialization library
Group:		System Environment/Libraries

%description prun-couchbase
Prun-couchbase is a prun job serialization library


%prep
%setup -q

%build
export DESTDIR="%{buildroot}"
cd build
%{cmake} ..
make


%install
rm -rf %{buildroot}
cd build
make install DESTDIR=%{buildroot}
rm -f %{buildroot}%{_libdir}/*.a
rm -f %{buildroot}%{_libdir}/*.la


%clean
rm -rf %{buildroot}


%files
%defattr(-,root,root,-)
%{_libdir}/lib*.so


%changelog
* Wed Nov 14 2018 Konstantin A Zhuravlev <zhukov@zhukov.int.ru> - 0.1
- Initial release.
