       # Ещё нужно кэширование без игнорирования всех заголовков

       # TODO: сделать по этому сценарию
       # http://habrahabr.ru/blogs/nginx/76315/
       # http://valera.ws/2009.01.26~nginx-magic/
       # Cookie
       #http://n2.nabble.com/Help-cache-or-not-by-cookie-td3124462.html

       #proxy_redirect off;

       # http://dklab.ru/chicken/nablas/56.html
       # http://n2.nabble.com/proxy-cache-does-not-work-td2986064.html
       proxy_cache             ngcache;

       # this is default value
       proxy_cache_key          "$scheme$host$uri$is_args$args";

       proxy_cache_use_stale http_502 http_503 http_504;

       # cache.conf in conf-available.d
       #proxy_cache_path /var/spool/nginx/cache levels=1:2 keys_zone=onepr:20m inactive=1d max_size=200m;
       #proxy_temp_path /var/spool/nginx/tmp/proxy;

       # Need for work
       # http://www.lexa.ru/nginx-ru/msg25572.html
       # TODO: move to separate
       proxy_buffering on;
       proxy_buffers 50 8k;
       proxy_buffer_size 64k;
       proxy_store off;

       # TODO php: check for cookie!

       #proxy_set_header  Last-Modified: $date_gmt;
       #proxy_set_header  Cache-Control: public;
       # override broken Pragma directive
       #add_header Pragma cache;
       proxy_hide_header Pragma;

       # Заставляем nginx кэшировать страницу в любом случае, независимо от
       # заголовков кэширования, выставляемых в PHP.
       # Сервер nginx обращает внимание на заголовки Cache-Control, Expires и Pragma, которые выдает PHP.
       # FIXME: invalid value "Pragma" ??
       # http://www.serverphorums.com/read.php?5,18350,18356,quote=1
       proxy_ignore_headers "Cache-Control" "Expires" "X-Accel-Expires";

       # Гарантируем, что разные пользователи не получат одну и ту же сессионную Cookie.
       proxy_hide_header "Set-Cookie";

       #proxy_buffering off;
       #proxy_buffers 50 4k;
       #proxy_cache_min_uses 3;


       # http://www.pentarh.com/wp/2008/07/18/using-nginx-apache/
       # lav 01.07.09
       proxy_set_header  Connection  close;
       proxy_set_header Host $host;

       # Нужно для модуля RPAF в Apache, в котором указывается RPAFheader X-Forwarded-For
       # http://padlik.ru/entries/86.html
       proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
