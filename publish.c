#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "MQTTClient.h"


#define ADDRESS  "tcp://broker.emqx.io"
#define PORT     1883
#define USERNAME "emqx"
#define PASSWORD "public"
#define QOS      1
#define TIMEOUT  10000


int send_message(char client_id[], char topic[], char payload[]) {
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token;
	int rc;

	MQTTClient_create(&client, ADDRESS, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;

	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
		printf("Failed to connect: %d\n", rc);
		exit(-1);
	}
	pubmsg.payload = payload;
	pubmsg.payloadlen = strlen(payload);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	MQTTClient_publishMessage(client, topic, &pubmsg, &token);
	printf("Publishing '%s' on topic '%s' with client ID '%s'\n", payload, topic, client_id);
	rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
	MQTTClient_disconnect(client, 10000);
	MQTTClient_destroy(&client);
	return rc;
}
