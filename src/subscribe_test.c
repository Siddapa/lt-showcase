#include "subscribe.h"
#include <stdio.h>


int main() {
	char client_id[50], topic[50];

	printf("Specify client id: ");
	scanf("%s", client_id);

	printf("Specify topic: ");
	scanf("%s", topic);

	listen(client_id, topic);
}
