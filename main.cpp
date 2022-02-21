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
#include "globals.h"
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
		wait(NULL);
		printf("Parent done\n");
		return 0;
	}
	
	if(tempID == 1){
		close(pip1[1]);
		close(pip2[1]);
		close(pip2[0]); // modelTest() below here if read only from pip1[0]
		modelTest();
		close(pip1[0]);
		exit(0);
	}else if(tempID == 2){
		close(pip1[0]);
		close(pip2[0]); // controlTest() below here if write to both pip1[1] and pip2[1]
		controlTest();
		close(pip1[1]);
		close(pip2[1]);
		exit(0);
	}else if(tempID == 3){
		close(pip1[1]);
		close(pip2[1]);
		close(pip1[0]); // viewTest() below here if read only from pip2[0]
		viewTest();
		close(pip2[0]);
		exit(0);
	}
	close(pip1[0]);
	close(pip2[0]);
	close(pip1[1]);
	close(pip2[1]);
    return 0;
}
