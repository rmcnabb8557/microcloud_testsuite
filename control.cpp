/*
*
*   control.cpp
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void controlTest(void){
    printf("Control Test Pass! %d\n", getppid());
}
