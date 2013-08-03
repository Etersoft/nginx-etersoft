Name: nginx-etersoft
Version: 0.2.3
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

Requires: nginx >= 1.1.8

%description
Additional Nginx templates and functions.

%prep
%setup

%install
mkdir -p %buildroot%_sysconfdir/nginx/include/limits/
install -m644 include/*.conf %buildroot%_sysconfdir/nginx/include/
install -m644 include/*.inc %buildroot%_sysconfdir/nginx/include/
install -m644 include/limits/* %buildroot%_sysconfdir/nginx/include/limits/

mkdir -p %buildroot%_sysconfdir/nginx/httpconf-enabled.d/

mkdir -p %buildroot%_sysconfdir/nginx/httpconf-available.d/
install -m644 httpconf-available.d/* %buildroot%_sysconfdir/nginx/httpconf-available.d/

mkdir -p %buildroot%_sysconfdir/nginx/examples/
install -m644 examples/* %buildroot%_sysconfdir/nginx/examples/

mkdir -p %buildroot%_datadir/%name/images/
install -m644 share/images/* %buildroot%_datadir/%name/images/

mkdir -p %buildroot%webserver_htdocsdir/maintenance/
install -m644 www/* %buildroot%webserver_htdocsdir/maintenance/

%files
%dir %_sysconfdir/nginx/include/
%config(noreplace) %_sysconfdir/nginx/include/*
%dir %_sysconfdir/nginx/httpconf-available.d/
%dir %_sysconfdir/nginx/httpconf-enabled.d/
%config(noreplace) %_sysconfdir/nginx/httpconf-available.d/*
%_sysconfdir/nginx/examples/
%_datadir/%name/
%webserver_htdocsdir/maintenance/

%changelog
* Sat Mar 23 2013 Vitaly Lipatov <lav@altlinux.ru> 0.2.3-alt1
- add trans-admin-proxy.conf
- deny.conf: forbids sql and .hg
- stop-crack.conf: slow login pages for WordPress and Joomla
- add limits for media
- move admin limits to separate files

* Fri Jan 04 2013 Vitaly Lipatov <lav@altlinux.ru> 0.2.2-alt1
- add static-stub and images for it
- add no_cache example
- create_nginx_from_apache: do not update config if not changed

* Sat Nov 24 2012 Vitaly Lipatov <lav@altlinux.ru> 0.2.1-alt1
- add nodelay to limit_req
- add initial stop-injection.conf

* Wed Mar 21 2012 Vitaly Lipatov <lav@altlinux.ru> 0.2.0-alt1
- moved to nginx >= 1.1.8
- too many incompatible changes

* Thu Mar 15 2012 Vitaly Lipatov <lav@altlinux.ru> 0.1.7-alt1
- add subst-site.conf for site.ru/subdir -> some.site.ru proxying

* Mon Nov 07 2011 Vitaly Lipatov <lav@altlinux.ru> 0.1.6-alt1
- add static-fallback.conf, mark as obsoleted static, static-images

* Thu Oct 20 2011 Vitaly Lipatov <lav@altlinux.ru> 0.1.5-alt1
- add logdefine.conf
- add reproxy.conf for internal redirect
- small static update

* Thu Jun 09 2011 Vitaly Lipatov <lav@altlinux.ru> 0.1.4-alt1
- add static-images.conf

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

