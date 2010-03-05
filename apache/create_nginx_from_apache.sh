#!/bin/sh

VHOSTSDIR=/etc/httpd/conf/vhosts.d
NGINXSITES=/etc/nginx/sites-enabled.d/generated

mkdir -p $NGINXSITES

. ./list_print_nginx_conf.sh

get_var()
{
	grep -i "^ *$2 " "$1" | head -n 1 | sed -e "s/^[ \t]*$2[ \t]*//g" | sed -e 's/"//g'
}

# TODO: add www for all domains?
filter_domains()
{
	local SITE=$1 SITES
	echo $(xargs -n1 echo | sort -u | grep -v "^$SITE\$" | grep -v "^www.$SITE\$")
}

> $0.log
for i in $VHOSTSDIR/*.conf ; do
	SITE=$(get_var $i ServerName)
	DROOT=$(get_var $i DocumentRoot)
	ALIASLIST=$(get_var $i ServerAlias | xargs -n1 echo | sort -u | grep -v "^$SITE\$" | grep -v "^www.$SITE\$" | xargs echo)
	UDIR=$(dirname "$DROOT") ; UDIR=$(dirname "$UDIR") ; UDIR=$(basename "$UDIR")

	echo "Read from $i, main site: $SITE, USER: $UDIR, ALIASLIST: $ALIASLIST"
	# comment it for debug
	#continue
	if [ "$VHOSTSDIR/$SITE.conf" != "$i" ] ; then
		echo "Warning: server name $SITE is not compat with file name"
		echo "Warning: server name $SITE is not compat with file name $i" >> $0.log
	fi
	if [ ! -d "$DROOT" ] ; then
		echo "Error: DocumentRoot $DROOT does not exists"
		echo "Error: DocumentRoot $DROOT does not exists in file $i" >> $0.log
	fi

	if [ -r $NGINXSITES/../$SITE.conf ] ; then
		echo "Warning: Skip $SITE.conf as already exists"
		echo "Warning: Skip $SITE.conf as already exists" >> $0.log
		continue
	fi

	if [ "$UDIR" = "pobedish" ] ; then
		print_nginx_pobedish_conf 87.249.47.44 $DROOT $SITE "$ALIASLIST" >$NGINXSITES/$SITE.conf
	else
		print_nginx_conf 87.249.47.44 $DROOT $SITE "$ALIASLIST" >$NGINXSITES/$SITE.conf
	fi

done
