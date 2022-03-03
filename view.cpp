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

void viewTest(int* view, int* vtocontrol){
	//packet *viewPacket;
	viewPacket = (struct packet *) malloc(sizeof(struct packet));
    	printf("View Test Pass! %d\n", getpid());
    	char* testMsg = "Test message from View";
    	viewPacket->terminate = false;
	do{
		while(!read(view[0], viewPacket, sizeof(*viewPacket))){
			wait(NULL);
		}
		printf("view: %s\n",viewPacket->message);
		
		//vv testsuite logic for view vv
		
		
		viewPacket->ID++;
		strcpy(viewPacket->message, testMsg);
		
		
		//^^ testsuite logic for model ^^
		
		write(vtocontrol[1], viewPacket, sizeof(*viewPacket));
	}while(!viewPacket->terminate);
	printf("View Done\n");
	exit(0);
}
