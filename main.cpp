/*
*
*   main.cpp
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "pipe.h"
#include "model.h"
#include "control.h"
#include "view.h"

#define THREE 3

int main(){
	int pid[THREE];
	int tempID;
	//For both pipelines, pip[0] is reading end,
	//and pip[1] is writing end
	if(pipe(pip1) == -1){
		printf("\nPipeline Error\n");
		return 1;
	}
	if(pipe(pip2) == -1){
		printf("\nPipeline Error\n");
		return 1;
	}
	for(int i = 0; i < THREE; i++){
		pid[i] = fork();
		tempID = i + 1;
		if(!pid[i]){
			break;
		}
	}
	if(pid[0] && pid[1] && pid[2]){
		tempID = 0;
		for(int i = 0; i < THREE; i++){
			wait(NULL);
		}
		printf("Parent done\n");
	}
	
	int strlimit = 100;
	char newstr[strlimit];
	if(tempID == 1){
		modelTest();
		close(pip1[1]);
		close(pip2[1]);
		close(pip2[0]); //read only from pip1[0]
		wait(NULL);
		read(pip1[0], newstr, strlimit);
		printf("Received from ControlPipeline: %s\n", newstr);
		close(pip1[0]);
		exit(0);
	}else if(tempID == 2){
		controlTest();
		char strv[] = "Test message to View";
		char strm[] = "Test message to Model";
		close(pip1[0]);
		close(pip2[0]);//write to both pip1[1] and pip2[1]
		write(pip1[1],strm, strlen(strm)+1);
		write(pip2[1],strv, strlen(strv)+1);
		close(pip1[1]);
		close(pip2[1]);
		exit(0);
	}else if(tempID == 3){
		viewTest();
		close(pip1[1]);
		close(pip2[1]);
		close(pip1[0]); //read only from pip2[0]
		wait(NULL);
		read(pip2[0], newstr, strlimit);
		printf("Received from ControlPipeline: %s\n", newstr);
		close(pip2[0]);
		exit(0);
	}
	close(pip1[0]);
	close(pip2[0]);
	close(pip1[1]);
	close(pip2[1]);
    return 0;
}
