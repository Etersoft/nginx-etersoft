#!/bin/sh

iptables -A INPUT -s $1 -j DROP
echo $1 >> $0.log
