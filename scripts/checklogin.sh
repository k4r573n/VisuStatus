#!/bin/bash
# Check to see if anyone is currently logged in. Return zero if not and 1 if so.
# Echoed text appears in log file. It can be removed and --quiet added to the 
# grep command once you are satisfied that mythTV is working properly

# Get a date/time stamp to add to log output
DATE=`date +%F\ %T\.%N`
DATE=${DATE:0:23}

if 
  # The leading space is important!
  w | grep " 0 users"
  then
    echo $DATE Noone is logged in, ok to shut down.
    exit 0
  else
    echo $DATE Someone is still logged in, don\'t shut down! 
    exit 1
fi

