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
	do{
		wait(NULL);
		if(!read(model[0], modelPacket, sizeof(*modelPacket))){
			break;
		}
		printf("Model from ControlPipeline: %s %d\n", modelPacket->message, modelPacket->ID);
	}while(modelPacket->ID < 10);
}
