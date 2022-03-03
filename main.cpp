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
#include "model.h"
#include "control.h"
#include "view.h"

#define THREE 3

int main(){
	int pid[THREE];
	int tempID;
	int model[2];
	int mtocontrol[2];
	int view[2];
	int vtocontrol[2];
	//For all pipelines, pip[0] is reading end,
	//and pip[1] is writing end
	if(pipe(model) == -1){
		printf("\nPipeline Error\n");
		return 1;
	}
	if(pipe(mtocontrol) == -1){
		printf("\nPipeline Error\n");
		return 1;
	}
	if(pipe(view) == -1){
		printf("\nPipeline Error\n");
		return 1;
	}
	if(pipe(vtocontrol) == -1){
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
		close(model[0]);
		close(view[0]);
		close(model[1]);
		close(view[1]);
		close(mtocontrol[0]);
		close(vtocontrol[0]);
		close(mtocontrol[1]);
		close(vtocontrol[1]);
		return 0;
	}
	
	if(tempID == 1){
		close(view[1]);
		close(view[0]); 
		close(vtocontrol[0]);
		close(vtocontrol[1]);
		close(model[1]);
		close(mtocontrol[0]);
		modelTest(model, mtocontrol); // modelTest()
		close(model[0]);
		close(mtocontrol[1]);
		exit(0);
	}else if(tempID == 2){
		close(model[0]);
		close(view[0]); 
		close(vtocontrol[1]);
		close(mtocontrol[1]);
		controlTest(model, view, vtocontrol, mtocontrol); // controlTest()
		close(vtocontrol[0]);
		close(mtocontrol[0]);
		close(model[1]);
		close(view[1]);
		exit(0);
	}else if(tempID == 3){
		close(model[1]);
		close(model[0]); 
		close(view[1]);
		close(vtocontrol[0]);
		close(mtocontrol[0]);
		close(mtocontrol[1]);
		viewTest(view, vtocontrol);// viewTest()
		close(view[0]);
		close(vtocontrol[1]);
		exit(0);
	}
	close(model[0]);
	close(view[0]);
	close(model[1]);
	close(view[1]);
	close(mtocontrol[0]);
	close(vtocontrol[0]);
	close(mtocontrol[1]);
	close(vtocontrol[1]);
    return 0;
}
