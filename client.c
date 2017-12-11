#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define SEM_KEY 22446
#define SHM_KEY 13377

int main(){
  //configuring semaphore
  int sem_id;
  sem_id = semget(SEM_KEY, 0, 0);

  struct sembuf sem_data;
  sem_data.sem_op = -1;
  sem_data.sem_num = 0;
  sem_data.sem_flg = SEM_UNDO;

  semop(sem_id, &sem_data, 1);

  //accessing shared memory
  int shm_id = shmget(SHM_KEY, sizeof(int), 0);
  int *shmp;
  shmat(shm_id, shmp, 0);

  //using shared memory to offset and print last line
  int fd = open("./story.txt", 0644, O_APPEND | O_CREAT | O_RDWR);
  char *output = (char *)calloc(*shmp, sizeof(int));
  lseek(fd, SEEK_CUR, *shmp);
  read(fd, output, *shmp);
  printf("%s", output);
  free(output);
  lseek(fd, SEEK_END, 0);
  
  printf("Please write your next line:\n");
  char *input = (char *) calloc(500, sizeof(char));
  fgets(input, 500, stdin);

  write(fd, input, 500);

  
  //altering shared memory
  //printf("shmp\n");
  *shmp = strlen(input);
  
  //detaching shared memory
  //printf("det\n");
  shmdt(shmp);

  //printf("sem\n");
  sem_data.sem_op = 1;
  semop(sem_id, &sem_data, 1);
}
