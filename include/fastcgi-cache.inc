
        fastcgi_intercept_errors on;
        try_files  $uri = 404;
        # FIXME: cache??
        fastcgi_index index.php;

        fastcgi_read_timeout 4000;
        fastcgi_temp_file_write_size 256k;

        fastcgi_ignore_client_abort off;

        fastcgi_cache  fastcgicache;
        fastcgi_cache_key $scheme$host$request_uri$request_method;
        fastcgi_cache_valid 200 301 302 5m;
        fastcgi_cache_valid any 10m;
        fastcgi_cache_use_stale updating error timeout invalid_header http_500;

        fastcgi_cache_lock on;
        fastcgi_cache_lock_timeout 40s;

        #fastcgi_pass_header Set-Cookie;
        #fastcgi_pass_header Cookie;
        fastcgi_hide_header Set-Cookie;
        fastcgi_ignore_headers Cache-Control Expires Set-Cookie;

        # cookie_nocache: we can now tell Nginx if the value "nocache" in Cookie is set disable the cache.
        # http_pragma: obsoleted Pragma: no-cache
        #fastcgi_no_cache $cookie_nocache $arg_nocache$arg_comment;
        #fastcgi_no_cache $http_pragma    $http_authorization;
        #fastcgi_cache_bypass $cookie_nocache $arg_nocache$arg_comment;
        #fastcgi_cache_bypass $http_pragma    $http_authorization;

        fastcgi_no_cache $skipcache;
        fastcgi_cache_bypass $skipcache;

        add_header X-Cache $upstream_cache_status;
