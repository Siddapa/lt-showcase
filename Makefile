all: publish_test subscribe_test

publish_test: publish_test.o publish.o
	gcc obj/publish_test.o obj/publish.o -o bin/publish_test -lpaho-mqtt3c

subscribe_test: subscribe_test.o subscribe.o
	gcc obj/subscribe_test.o obj/subscribe.o -o bin/subscribe_test -lpaho-mqtt3c

publish_test.o: src/publish_test.c
	gcc -c src/publish_test.c -o obj/publish_test.o

subscribe_test.o: src/subscribe_test.c
	gcc -c src/subscribe_test.c -o obj/subscribe_test.o

publish.o: src/publish.c
	gcc -c src/publish.c -o obj/publish.o

subscribe.o: src/subscribe.c
	gcc -c src/subscribe.c -o obj/subscribe.o

clean:
	rm -rf bin/* obj/*

install:
	sudo apt-get install openssl
	wget https://github.com/eclipse-paho/paho.mqtt.c/archive/refs/tags/v1.3.14.tar.gz
	tar -xzvf v1.3.14.tar.gz
	cd paho.mqtt.c-1.3.14
	make
	sudo make install
	cd ..
	rm -f v1.3.14.tar.gz
	rm -rf paho.mqtt.c-v1.3.14
