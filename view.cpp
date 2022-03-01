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
	char message[100];
};

void viewTest(int* view){
	packet *viewPacket;
	viewPacket = (struct packet *) malloc(sizeof(struct packet));
    	printf("View Test Pass! %d\n", getppid());
	do{
		wait(NULL);
		if(!read(view[0], viewPacket, sizeof(*viewPacket))){
			break;
		}
		printf("View from ControlPipeline: %s %d\n", viewPacket->message, viewPacket->ID);
	}while(viewPacket->ID < 10);
}
