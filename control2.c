#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include "control.h"

void sem_value(){
  int sem_value = semget(SEM_KEY, 0,0);
  printf("sem value is:", semctl(sem_value,0, GETVAL));
}
void create_sem(char *x){
  int sem_value = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0664);
  if(sem_value==-1){
    printf("failed because sem already exists\n");
  }
 else{
    int z;
    scanf(x, "%d", &z);
    semctl(sem_value, 0, SETVAL, z);
    printf("sem created\n");
  }
}

void sem_remove(){
  int sem_value = semget(SEM_KEY,0,0);
  printf("sem removed", semctl(sem_value, 0, IPC_RMID));
}

int main(int c, char ** v){
  if (c< 2){
    printf("failed\n");
  }
  else{
    if(strcmp(v[1], "-r")==0){
      sem_remove();
    }
    if(strcmp(v[1], "-v")==0){
      sem_value();
    }
    if(strcmp(v[1],"-c")==0 && !(c <3)){
      create_sem(v[2]);
    }
    else {
      printf("failed\n");
    }
  }
  return 0;
}
