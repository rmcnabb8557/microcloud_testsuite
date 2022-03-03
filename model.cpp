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

void modelTest(int* model, int* mtocontrol){
	//packet *modelPacket;
	modelPacket = (struct packet *) malloc(sizeof(struct packet));
    	printf("Model Test Pass! %d\n", getpid());
    	char* testMsg = "Test message from Model";
    	modelPacket->terminate = false;
	do{
		while(!read(model[0], modelPacket, sizeof(*modelPacket))){
			wait(NULL);
		}
		printf("model: %s\n",modelPacket->message);
		
		//vv testsuite logic for model vv
		
		
		modelPacket->ID++;
		strcpy(modelPacket->message, testMsg);
		
		
		//^^ testsuite logic for model ^^
		
		write(mtocontrol[1], modelPacket, sizeof(*modelPacket));
	}while(!modelPacket->terminate);
	printf("Model Done\n");
	exit(0);
}
