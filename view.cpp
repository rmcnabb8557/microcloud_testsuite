/*
*
*   view.cpp
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
} *viewPacket;

void vsend(char* message, int *view){
	viewPacket->ID ++;
	strcpy(viewPacket->message, message);
	write(view[1], viewPacket, sizeof(*viewPacket));
}

packet* vreceive(int *view){
	packet *tempPacket;
	tempPacket = (struct packet *) malloc(sizeof(struct packet));
	while(!read(view[0], tempPacket, sizeof(*tempPacket)));
	return tempPacket;
}

void viewTest(int* view){
	//packet *viewPacket;
	viewPacket = (struct packet *) malloc(sizeof(struct packet));
    	//printf("View Test Pass! %d\n", getppid());
    	char* testMsg = "Test message from View"
	do{
		wait(NULL);
		viewPacket = vreceive(view);
		if(viewPacket->terminate){
			printf("View Process Terminated\n");
			break;
		}
		printf("View from ControlPipeline: %s %d\n", viewPacket->message, viewPacket->ID);
		
		vsend(testMsg, view);
	}while(1);
}
