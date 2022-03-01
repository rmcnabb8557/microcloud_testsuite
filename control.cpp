/*
*
*   control.cpp
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

struct packet{
	int ID;
	char message[100];
};

void controlTest(int* model, int* view){
	packet *controlPacket = (struct packet*)malloc(sizeof(struct packet));
	//printf("%d\n",sizeof(*controlPacket));
	controlPacket->ID = 0;
	strcpy(controlPacket->message, "Tester");
	printf("Control Test Pass! %d\n", getppid());
	while(controlPacket->ID < 10){
		write(model[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		controlPacket->ID += 1;
		write(view[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		controlPacket->ID += 1;
	}
}
