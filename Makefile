all: publish_test subscribe_test

publish_test: publish_test.o publish.o
	gcc publish_test.o publish.o -o publish_test -lpaho-mqtt3c

subscribe_test: subscribe_test.o subscribe.o
	gcc subscribe_test.o subscribe.o -o subscribe_test -lpaho-mqtt3c

publish_test.o: publish_test.c
	gcc -c publish_test.c

subscribe_test.o: subscribe_test.c
	gcc -c subscribe_test.c

publish.o: publish.c
	gcc -c publish.c

subscribe.o: subscribe.c
	gcc -c subscribe.c

clean:
	rm -f publish_test subscribe_test publish.o subscribe.o publish_test.o subscribe_test.o

install:
	sudo apt-get install openssl
	wget https://github.com/eclipse-paho/paho.mqtt.c/archive/refs/tags/v1.3.14.tar.gz
	tar -xzvf v1.3.14.tar.gz
	cd v1.3.14
	make
	sudo make install
	rm -f v1.3.14.tar.gz
	rm -rf v1.3.14
