Name: nginx-etersoft
Version: 0.1.3
Release: alt1

Summary: Additional Nginx templates and functions

License: AGPLv3
Group: Development/Other
Url: http://www.altlinux.org/Nginx-etersoft

Packager: Vitaly Lipatov <lav@altlinux.ru>

# git-clone http://git.altlinux.org/people/lav/packages/%name.git
# git-clone http://git.etersoft.ru/people/lav/packages/%name.git
Source: %name-%version.tar

BuildArchitectures: noarch

Requires: nginx >= 0.8.0

%description
Additional Nginx templates and functions.

%prep
%setup

%install
mkdir -p %buildroot%_sysconfdir/nginx/include/
install -m644 include/* %buildroot%_sysconfdir/nginx/include/

mkdir -p %buildroot%_sysconfdir/nginx/examples/
install -m644 examples/* %buildroot%_sysconfdir/nginx/examples/

%files
%dir %_sysconfdir/nginx/include/
%config(noreplace) %_sysconfdir/nginx/include/*
%_sysconfdir/nginx/examples/

%changelog
* Thu Nov 11 2010 Vitaly Lipatov <lav@altlinux.ru> 0.1.3-alt1
- fix robots.txt rewrite for set-mainhost

* Thu Nov 11 2010 Vitaly Lipatov <lav@altlinux.ru> 0.1.2-alt1
- correct ignore www rewrite for robots.txt
- hold scheme when set main host
- set proxy_buffer_size in all proxy
- use relate path instead full

* Sun Mar 07 2010 Vitaly Lipatov <lav@altlinux.ru> 0.1.1-alt1
- add examples, add ssl configs

* Sat Mar 06 2010 Vitaly Lipatov <lav@altlinux.ru> 0.1-alt1
- initial build

