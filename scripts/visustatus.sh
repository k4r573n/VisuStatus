#!/bin/bash

#visualisiert den PC status auf der LED leiste
#
# * LED leiste
# *
# * * loged in User
# * * Recording
# * * converting job o.ä. running
# * * backup running
# * * Internet available
# * * Volkers PC an
# * * still alive - toggle



#Ob Noch wer angemeldet ist über exit code
/usr/local/sbin/checklogin.sh
led1_exit_code=$?
if [  "$led1_exit_code" -ne "0" ] 
then
	led1="-1"
else
	led1=" "
fi

#Internet (DNS Server der TU-BS)
led2=`/usr/local/sbin/checkping.sh sinus-cr1.apm.etc.tu-bs.de`
if [  -z "$led2" ] 
then
	led2="-2"
else
	led2=" "
fi

#erster DHCP nutzer des Netzwerkes
led3=`/usr/local/sbin/checkping.sh 192.168.111.100`
if [  -z "$led3" ] 
then
	led3="-3"
else
	led3=" "
fi

#ob mythtv etwas aufnimmt oder TV läuft
led4=`mythtv-status | grep "Recording Now"`
if [  -n "$led4" ] 
then
	led4="-4"
else
	led4=" "
fi

#ob der Process läuft
#(am ende wird ggf noch mals grep aus den funden entfernt)
led5=`ps ax | grep backintime | grep -v grep`
if [  -n "$led5" ] 
then
	led5="-5"
else
	led5=" "
fi

#led6=``
#led7=``
#led8=``

echo "LED 1: $led1"
echo "LED 2: $led2"
echo "LED 3: $led3"
echo "LED 4: $led4"
echo "LED 5: $led5"
echo "LED 6: $led6"
echo "LED 7: $led7"
echo "LED 8: $led8"

/usr/local/sbin/send2parport $led1 $led2 $led3 $led4 $led5 $led6 $led7 $led8
