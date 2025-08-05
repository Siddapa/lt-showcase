#include "publish.h"
#include <stdio.h>


int main() {
	char client_id[50], topic[50], message[1024];
	char empty;

	printf("Specify client id: ");
	scanf("%s", client_id);

	printf("Specify topic: ");
	scanf("%s%c", topic, &empty);

	printf("Specify message: ");
	scanf("%[^\n]s", message);

	// User inputted message
	send_message(client_id, topic, message);


	// Sequential correct sends
	for (int i = 70; i < 80; i++) {
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "Setting temperature to %d", i);
		send_message("ExamplePublisher",
			     "lt-showcase",
			     &buffer);
	}

	// Mismatched topics with subscriber
	send_message("ExamplePublisher", "lt-failing-showcase", "Should fail!");
}
