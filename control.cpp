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
	//printf("Control Test Pass! %d\n", getppid());
	while(controlPacket->ID < 20){
		if(controlPacket->ID > 10){
			controlPacket->terminate = true;
		}
		write(model[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		while(!read(model[0], controlPacket, sizeof(*controlPacket)));
		printf("Message received by control: %s\n", controlPacket->message);  //edit all of this
		
		controlPacket->ID += 1;
		controlPacket->terminate = false;
		write(view[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		controlPacket->ID += 1;
	}
	controlPacket->terminate = true;
	write(view[1], controlPacket, sizeof(*controlPacket));
	write(model[1], controlPacket, sizeof(*controlPacket));
	
}
