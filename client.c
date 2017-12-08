#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#define SEM_KEY 22446

struct sembuf{
	short sem_op;
	short sem_num;
	short sem_flag;
}

int main(){
  int sem_id;
  sem_id = semget(SEM_KEY, 0, 0);

  struct sembuf sem_data;
  sem_data.sem_op = -1;
  sem_data.sem_num = 0;
  sem_data.sem_flags = SEM_UNDO;

  semop(sem_id, &sem_data, 1);
  char *input = (char *) calloc(500, sizeof(char));
  fgets(input, 500, stdin);
  
}
