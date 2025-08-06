# MQTT Showcase
This small project provides an example for creating a synchronous publisher and asynchronous subscriber that communicates temperature data via a public EMQX MQTT broker. The clients are built using the `eclipse-paho` MQTTClient library for handling the TCP connections.


# Installation
```
make install
make
```


# Testing
The testing suite is broken up into `publish_test` and `subscribe_test` binaries. To test the integreation between both tests, `subscribe_test` should be run first with `publish_test` running in a separate process.
```
# First Process
./bin/subscribe_test

# Second Process
./bin/publish_test
```
