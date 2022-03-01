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
	bool terminate;
	char message[100];
};

void controlTest(int* model, int* view){
	packet *controlPacket = (struct packet*)malloc(sizeof(struct packet));
	//printf("%d\n",sizeof(*controlPacket));
	controlPacket->ID = 0;
	controlPacket->terminate = false;
	strcpy(controlPacket->message, "Tester");
	printf("Control Test Pass! %d\n", getppid());
	while(controlPacket->ID < 30){
		if(controlPacket->ID > 20){
			controlPacket->terminate = true;
		}
		write(model[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		controlPacket->ID += 1;
		controlPacket->terminate = false;
		write(view[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		controlPacket->ID += 1;
	}
}
