       # Ещё нужно кэширование без игнорирования всех заголовков

       # TODO: сделать по этому сценарию
       # http://habrahabr.ru/blogs/nginx/76315/
       # http://valera.ws/2009.01.26~nginx-magic/
       # Cookie
       #http://n2.nabble.com/Help-cache-or-not-by-cookie-td3124462.html

       #proxy_redirect off;

       # http://dklab.ru/chicken/nablas/56.html
       proxy_cache             ngcache;

       # если страница уже запрошена, ждать результата, а не пытаться параллельно запросить
       # https://trac.nginx.org/nginx/ticket/130
       proxy_cache_lock on;
       proxy_cache_lock_age 200s;
       proxy_cache_lock_timeout 300s;

       proxy_cache_key "$scheme$proxy_host$request_uri";
       # pseudo default, can run in recursion with /// access
       #proxy_cache_key          "$scheme$host$uri$is_args$args";

       proxy_cache_use_stale error timeout updating http_500 http_502 http_503 http_504;

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
       # Видимо, также обращает внимание и на Set-Cookie
       # FIXME: invalid value "Pragma" ??
       # http://www.serverphorums.com/read.php?5,18350,18356,quote=1
       proxy_ignore_headers "Cache-Control" "Expires" "X-Accel-Expires" "Set-Cookie";

       proxy_hide_header "X-Powered-By";

       # Гарантируем, что разные пользователи не получат одну и ту же сессионную Cookie
       # TODO: А как же админка работает?
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


       # Pass through cache
       add_header X-Cache $upstream_cache_status;

       proxy_cache_background_update on;

       # WordPress admin
       set $skipcache 0;
       if ($http_cookie ~ "wordpress_logged_in") {
           set $skipcache 1;
       }

       # TODO: other dynamic
       # Check for Set-Cookie??

       # Pass cache when X-Update or cookie
       proxy_cache_bypass $http_x_update $skipcache;
       proxy_no_cache $skipcache;

       # можно будет принудительно обновлять кэш страницы при необходимости:
       #curl -s -o /dev/null  -H "X-Update: 1" www.example.com


# SSL using
# https://github.com/dmikusa-pivotal/cf-php-apache-buildpack/issues/6
# default method:
# in apache config: SetEnvIf X-Forwarded-Proto https HTTPS=on
# PerlPassEnv HTTPS
# # a2enmod setenvif
# php: if (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] == 'on') 

# latest common method
# http://stackoverflow.com/questions/1175096/how-to-find-out-if-youre-using-https-without-serverhttps
# php: if (!empty($_SERVER['HTTP_X_FORWARDED_PROTO']) && $_SERVER['HTTP_X_FORWARDED_PROTO'] == 'https')

# set X-Forwarded from $scheme or from upstream nginx
set $ourscheme $scheme;
if ( $http_x_forwarded_proto != "") {
    set $ourscheme $http_x_forwarded_proto;
}
proxy_set_header  X-Forwarded-Proto $ourscheme;

# Чтобы апач не пытался ничего сжимать
proxy_set_header Accept-Encoding "";
