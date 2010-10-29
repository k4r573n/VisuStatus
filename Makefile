########################
## Part of VisuStatus ##
########################

#should work with Ubuntu 10.10 or newer 
install: send2parport
	sudo cp ./scripts/* /usr/local/sbin/
	sudo cp ./send2parport/dist/Release/GNU-Linux-x86/send2parport /usr/local/sbin/
	sudo chmod +x /usr/local/sbin/send2parport
	sudo cp ./cron_script /etc/cron.d/visustatus

#calls the netbeans makefile
send2parport: 
	cd ./send2parport/ && make all && cd ..

all: install

remove:
	sudo rm /usr/local/sbin/send2parport
	sudo rm /etc/cron.d/visustatus
	sudo rm /usr/local/sbin/checklogin.sh
	sudo rm /usr/local/sbin/checkping.sh
	sudo rm /usr/local/sbin/visustatus.sh

