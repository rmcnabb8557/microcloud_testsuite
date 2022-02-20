/*
*
*   main.cpp
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
#include "model.h"
#include "control.h"
#include "view.h"

#define THREE 3

int main(){
	int pid[THREE];
	int tempID;
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
	if(tempID == 1){
		modelTest();
		exit(0);
	}else if(tempID == 2){
		controlTest();
		exit(0);
	}else if(tempID == 3){
		viewTest();
		exit(0);
	}
    return 0;
}
