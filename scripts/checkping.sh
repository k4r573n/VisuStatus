#!/bin/bash

#copied from
#http://www.cyberciti.biz/tips/simple-linux-and-unix-system-monitoring-with-ping-command-and-scripts.html

#HOSTS="192.168.111.1 192.168.111.2"
HOSTS=$1

COUNT=4

for myHost in $HOSTS
do
  ping -c $COUNT $myHost > /tmp/$myHost 2>&1
#  echo `cat /tmp/$myHost`
  bla=`cat /tmp/$myHost | grep "unknown host"`
  if [ -n "$bla" ]; then
    echo "Host: $myHost is unknown (ping failed) at $(date)"
  else

    count=`cat /tmp/$myHost | grep 'received' | awk -F',' '{ print $2 }' | awk '{ print $1 }'`
    if [ $count -eq 0 ]; then
      # 100% failed 
      echo "Host : $myHost is down (ping failed) at $(date)"
    fi
  fi
  rm /tmp/$myHost
done
