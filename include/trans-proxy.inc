
# by default will rewrite Location and Refresh
#proxy_redirect off;

# http://nginx.org/ru/docs/http/ngx_http_proxy_module.html#proxy_buffering
proxy_buffering on;
proxy_buffers 50 8k;
# http://www.lexa.ru/nginx-ru/msg25572.html
# http://phpsuxx.blogspot.com/2009/11/upstream-sent-too-big-header-while.html
proxy_buffer_size 64k;
#proxy_cache_min_uses 3;

# http://www.pentarh.com/wp/2008/07/18/using-nginx-apache/
# lav 01.07.09
proxy_set_header Connection  close;

proxy_set_header X-Real-IP $remote_addr;

# Нужно для модуля RPAF в Apache, в котором указывается RPAFheader X-Forwarded-For
# http://padlik.ru/entries/86.html
proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;

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

# Чтобы апач не пытался ничего сжимать (нужно для sub_filter и вообще)
proxy_set_header Accept-Encoding "";
