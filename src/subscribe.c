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

void lost_conn(void* context, char* cause) {
	printf("Connection lost because of %s\n", cause);
}

int found_msg(void* context, char* topic_name, int topic_len, MQTTClient_message* message) {
	printf("Topic: %s\n", topic_name);

	char* payload_ptr = message->payload;
	for (int i = 0; i < message->payloadlen; i++) {
		putchar(*payload_ptr++);
	}
	putchar('\n');

	MQTTClient_freeMessage(&message);
	MQTTClient_free(topic_name);
	return 1;
}

void delivered(void* context, MQTTClient_deliveryToken dt) {
	printf("Delivery confirmed for token %d\n", dt);
}


int listen(char client_id[], char topic[]) {
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	int rc;

	MQTTClient_create(&client, ADDRESS, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;

	MQTTClient_setCallbacks(client, NULL, lost_conn, found_msg, delivered);

	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
		printf("Failed to connect: %d\n", rc);
		exit(-1);
	}
	printf("Subscribing to topics '%s' for client '%s' using QOS '%d'\n", topic, client_id, QOS);
	MQTTClient_subscribe(client, topic, QOS);

	int ch;
	do {
		ch = getchar();
	} while (ch != 'q' && ch != 'q');

	MQTTClient_disconnect(client, 10000);
	MQTTClient_destroy(&client);
	return rc;
}
