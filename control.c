#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include "control.h" 
int main(int argc, char *argv[]){
  int sem_id = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0777);
  int shm_id = shmget(SHM_KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0777);
  int story_file = open("story.txt", O_CREAT | O_EXCL | O_TRUNC | O_RDWR, 0777)
  if (argc == 1){
    printf("flags missing\n");
  }
  else if (! strcmp(argv[1], "-c")){
    if (sem_id == -1 || shm_id == -1 || story_file == -1){
      printf("error in sem, shm, and/or file\n");
    }
    close(story_file);
    else{
      //printf("semaphore created: %d\n", sem_id);
      semctl(sem_id, 0, SETVAL, val);
      //printf("value set: %d\n", semctl(sem_id, 0, GETVAL)) ;
      int *shmp;
      shm_p (int*)shmat(shm_id, 0, 0);
      if(shm_p == -1){
	printf("shm p error\n");
      }
      *shm_p = 0;
      int shm_d = shmdt(shm_p);
      if(d == -1){
	printf("shmdt error\n");
      }
      printf("story done");
    }
  }
  else if (! strcmp(argv[1], "-r")){
    sem_id = semget(SEM_KEY, 1, 0777);
    shm_id = shmget(SHM_KEY, sizeof(int), 0777);
    if(sem_id == -1 || shm_id == -1){
      printf("error\n");
    }
    else{
      struct sembuf buffer;
      buffer.semf_op = -1;
      buffer.sum_num = 0;
      buffer.sem_flg = SEM_UNDO;
      semop(sem_id, &buffer, 1);
      printf("story:\n");
      int f = fork();
      if(f){
	int s;
	wait(&s);
      }
      else{
	char *story_file[] = {" ", "story.txt", 0};
      execvp(story_file[0], story_file);
      }
      semctl(sem_id, 0, IPC_RMID, arg);
      shmctl(shm_id, IPC_RMID, NULL);
      remove("story.txt");
      printf("story removed: %d\n", semctl(semget(SEM_KEY, 0, 0), 0, IPC_RMID));
    }
  }
  else if (! strcmp(argv[1], "-v")){
    printf("story:\n");
    int f = fork();
    if(f){
      int s;
      wait(&s);
    }
    else{
      char *story_file[] = {" ", "story.txt", 0};
      execvp(story_file[0], story_file);
    }
  }
}

