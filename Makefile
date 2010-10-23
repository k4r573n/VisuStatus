########################
## Part of VisuStatus ##
########################

#should work with Ubuntu 10.10 or newer (should run as root)
install: all
	cp ./scripts/* /usr/local/sbin/
	cp ./send2parport/dist/Debug/GNU-Linux-x86/send2parport /usr/local/sbin/
	chmod +x /usr/local/sbin/send2parport
	cp ./cron_script /etc/cron.d/visustatus

#calls the netbeans makefile
all: 
	cd ./send2parport/ && make all && cd ..


