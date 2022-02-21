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
#include "globals.h"

struct packet{
	int ID;
	char message[100];
} controlPacket;
void controlTest(void){
    printf("Control Test Pass! %d\n", getppid());
	char strv[] = "Test message to View";
	char strm[] = "Test message to Model";
	write(pip1[1], strm, strlen(strm)+1);
	write(pip2[1], strv, strlen(strv)+1);
}
