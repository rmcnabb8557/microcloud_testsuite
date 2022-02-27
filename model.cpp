/*
*
*   model.cpp
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

void modelTest(int* model){
	packet *modelPacket;
	modelPacket = (struct packet *) malloc(sizeof(struct packet));
    	printf("Model Test Pass! %d\n", getppid());
	wait(NULL);
	read(model[0], modelPacket, sizeof(*modelPacket));
	printf("Received from ControlPipeline: %s %d\n", modelPacket->message, modelPacket->ID);
}
