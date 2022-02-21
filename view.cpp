/*
*
*   view.cpp
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "globals.h"

struct packet{
	int ID;
	char message[100];
} viewPacket;
void viewTest(void){
    printf("View Test Pass! %d\n", getppid());
    packet viewPacket;
	int strlimit = 100;
	char newstr[strlimit];
	wait(NULL);
	read(pip2[0], newstr, strlimit);
	printf("Received from ControlPipeline: %s\n", newstr);
}
