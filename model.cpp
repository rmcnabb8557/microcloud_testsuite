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
	bool terminate;
	char message[100];
} *modelPacket;

void msend(char* message, int *model){
	modelPacket->ID ++;
	strcpy(modelPacket->message, message);
	write(model[1], modelPacket, sizeof(*modelPacket));
}

packet* mreceive(int *model){
	packet *tempPacket;
	tempPacket = (struct packet *) malloc(sizeof(struct packet));
	while(!read(model[0], tempPacket, sizeof(*tempPacket)));
	return tempPacket;
}

void modelTest(int* model){
	//packet *modelPacket;
	modelPacket = (struct packet *) malloc(sizeof(struct packet));
    	//printf("Model Test Pass! %d\n", getppid());
    	char* testMsg = "Test message from Model";
	do{
		wait(NULL);
		modelPacket = mreceive(model);
		if(modelPacket->terminate){
			printf("Model Process Terminated\n");
			break;
		}
		printf("Model from ControlPipeline: %s %d\n", modelPacket->message, modelPacket->ID);
		
		msend(testMsg, model);
	}while(1);
}
