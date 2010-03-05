#!/bin/sh

# path site
print_nginx_conf()
{
	local IP=$1 ROOT=$2 DOMAIN=$3 ALIASLIST="$4"
cat <<EOF
   server {
        listen $IP;
        server_name $DOMAIN www.$DOMAIN $ALIASLIST;

        # http://rt.etersoft.ru:80/Ticket/Display.html?id=13058
        # http://help.yandex.ru/webmaster/?id=996567#996574
        include /etc/nginx/rewrite-www.conf;

        # direct read all static
        set \$rootdir $ROOT;
        include /etc/nginx/static.conf;

        # always cache main page
        location = / {
                proxy_pass http://127.0.0.1:80;
                include /etc/nginx/store-proxy.conf;
        }

        # hack for pobedish
        #location /main/ {
        #        proxy_pass http://127.0.0.1:80;
        #        include /etc/nginx/store-proxy.conf;
        #}

        # cache html/possibly generated pages
        location ~* \.(htm|html|shtml)$ {
              proxy_pass http://127.0.0.1:80;
              include /etc/nginx/store-proxy.conf;
        }

#        if (\$query_string) {
#              return 412;
#        }

        if (\$request_method = "POST" ) {
              return 412;
        }

        error_page 412 = @nocached;

        location @nocached {
            proxy_pass http://127.0.0.1:80;
            include         /etc/nginx/trans-proxy.conf;
        }

        # default
        location / {
            proxy_pass http://127.0.0.1:80;
            include         /etc/nginx/trans-proxy.conf;
        }

#       access_log off;
        error_log   /var/log/nginx/eterhost.ru-error.log crit;

    }
EOF

}


# path site
print_nginx_pobedish_conf()
{
	local IP=$1 ROOT=$2 DOMAIN=$3 ALIASLIST="$4"
cat <<EOF
   server {
        listen $IP;
        server_name $DOMAIN www.$DOMAIN $ALIASLIST;

        # direct read all static
        set \$rootdir $ROOT;
        include /etc/nginx/static.conf;

        # include /etc/nginx/rewrite-www.conf;


#        if (\$query_string) {
#              return 412;
#        }

        if (\$request_method = "POST" ) {
              return 412;
        }

        error_page 412 = @nocached;

        location @nocached {
            proxy_pass http://127.0.0.1:80;
            include         /etc/nginx/trans-proxy.conf;
        }

        # default
        location / {
            proxy_pass http://127.0.0.1:80;
            include         /etc/nginx/trans-proxy.conf;
        }

#       access_log off;
        error_log   /var/log/nginx/eterhost.ru-error.log crit;

    }
EOF

}

