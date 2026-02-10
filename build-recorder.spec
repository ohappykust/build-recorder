Name:           build-recorder
Version:        1.0.3
Release:        1%{?dist}
Summary:        Record build process interactions to RDF Turtle format

License:        LGPL-2.1-or-later
URL:            https://github.com/ohappykust/build-recorder
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make
BuildRequires:  autoconf
BuildRequires:  automake
BuildRequires:  openssl-devel

Requires:       openssl-libs

%description
build-recorder is a command line tool for Linux 5.3+ that records
information about build processes. It achieves this by running transparently
in the background while the build process is running, tracing it
and extracting all relevant information, which it then stores in the output
file in RDF Turtle format.

%prep
%autosetup

%build
autoreconf -i
%configure
%make_build

%install
%make_install

%files
%license LICENSE
%doc README.md CONTRIBUTING.md
%{_bindir}/build-recorder
%{_datadir}/build-recorder/build-recorder-schema.ttl

%changelog
* Mon Feb 10 2026 Kirill Nikolaevskiy <me@happykust.dev> - 1.0.3-1
- Suppress error messages for virtual filesystem access (/sys, /proc, /dev)
- Fix segmentation fault when renaming nonexistent files
- Handle inaccessible files gracefully in file open operations
- Handle PTRACE race conditions when processes exit quickly
- All fixes make build-recorder resilient to package managers like pnpm

* Sat Feb 10 2026 Kirill Nikolaevskiy <me@happykust.dev> - 1.0.2-1
- Fix memory corruption bugs when accessing inaccessible /sys files
- Fix file descriptor leak in hash.c when mmap fails
- Fix NULL pointer dereference in record.c
- Fix double-free in tracer.c with deep copy and proper cleanup

* Mon Feb 10 2026 Kirill Nikolaevskiy <me@happykust.dev> - 1.0-1
- Initial RPM release
- Add CI/CD support
- Add static build support
