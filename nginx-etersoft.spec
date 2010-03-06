Name: nginx-etersoft
Version: 0.1
Release: alt1

Summary: Additional Nginx templates and functions

License: AGPLv3
Group: Development/Other
#Url: http://freesource.info/wiki/korinf

Packager: Vitaly Lipatov <lav@altlinux.ru>

# git-clone http://git.altlinux.org/people/lav/packages/%name.git
# git-clone http://git.etersoft.ru/people/lav/packages/%name.git
Source: %name-%version.tar

BuildArchitectures: noarch

%description
Additional Nginx templates and functions.

%prep
%setup

%install
mkdir -p %buildroot%_sysconfdir/nginx/include/
install -m644 include/* %buildroot%_sysconfdir/nginx/include/

%files
%dir %_sysconfdir/nginx/include/
%config(noreplace) %_sysconfdir/nginx/include/*

%changelog
* Sat Mar 06 2010 Vitaly Lipatov <lav@altlinux.ru> 0.1-alt1
- initial build

