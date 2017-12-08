#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include "control.h"

int main(int argc, char *argv[]){
  int val = 0;
  if (argc > 2){
    //printf("%d\n", argv[2]);
    if(! strcmp(argv[1], "-c")){	
      sscanf(argv[2], "%d", &val);
      //printf("%d\n", val);
    }
  }
  //printf("%s\n", argv[1]);
  if (! strcmp(argv[1], "-c")){
    int id = semget(SEM_KEY, 0, 0644 | IPC_CREAT | IPC_EXCL);
    if (id == -1){
      printf("semaphore already exists\n");
    }
    else{
      printf("semaphore created: %d\n", id);
      semctl(id, 0, SETVAL, val);
      printf("value set: %d\n", semctl(id, 0, GETVAL)) ;
    }
  }

  if (! strcmp(argv[1], "-r")){
    printf("semaphore removed: %d\n", semctl(semget(SEM_KEY, 0, 0), 0, IPC_RMID));
  }
	
  if (! strcmp(argv[1], "-v")){
    int v = semctl(semget(SEM_KEY, 0, 0), 0, GETVAL);
    printf("semaphore value: %d\n", v);
    //printf("%s\n", strerror(errno));
		
  }
}
