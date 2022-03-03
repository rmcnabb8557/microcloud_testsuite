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
}*controlPacket;

void controlTest(int* model, int* view, int* vtocontrol, int* mtocontrol){
	packet *controlPacket = (struct packet*)malloc(sizeof(struct packet));
	//printf("%d\n",sizeof(*controlPacket));
	controlPacket->ID = 0;
	controlPacket->terminate = false;
	char* testmsg = "Tester control";
	printf("Control Test Pass! %d\n", getpid());
	while(controlPacket->ID < 20){
		
		//vv testsuite logic for control vv
		
		strcpy(controlPacket->message, testmsg);
		
		//^^ testsuite logic for control ^^
		
		controlPacket->ID ++;
		write(view[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		controlPacket->ID ++;
		write(model[1], controlPacket, sizeof(*controlPacket));
		wait(NULL);
		//write section ^^
		//read section vv
		while(!read(vtocontrol[0], controlPacket, sizeof(*controlPacket))){
			wait(NULL);
		}
		printf("control: %s\n", controlPacket->message);
		while(!read(mtocontrol[0], controlPacket, sizeof(*controlPacket))){
			wait(NULL);
		}
		printf("control: %s\n", controlPacket->message);
	}
	controlPacket->terminate = true;
	strcpy(controlPacket->message, (char*)"Terminate from Control!");
	write(view[1], controlPacket, sizeof(*controlPacket));
	write(model[1], controlPacket, sizeof(*controlPacket));
	printf("Control Done\n");
	exit(0);
}
