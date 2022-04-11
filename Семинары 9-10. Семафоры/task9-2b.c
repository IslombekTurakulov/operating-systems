#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
  int *array;
  int shmid, semid;
  int new = 1;
  long i;
  char pathname[] = "task9-2a.c";
  key_t key;
  struct sembuf mybuf;
  if ((key = ftok(pathname, 0)) < 0) {
    printf("[Error 9-2b.c] can\'t generate key\n");
    exit(-1);
  }
  if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("[Error 9-2b.c] can\'t create shared memory\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
        printf("[Error 9-2b.c] can\'t find shared memory\n");
        exit(-1);
      }
      new = 0;
    }
  }
  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("[Error 9-2b.c] can\'t attach shared memory\n");
    exit(-1);
  }
  if ((semid = semget(key, 1, 0666)) < 0) {
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
      printf("[Error 9-2b.c] can\'t create semaphore set\n");
      exit(-1);
    }
    mybuf.sem_num = 0;
    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    if (semop(semid, &mybuf, 1) < 0) {
      printf("[Error 9-2b.c] can\'t wait for condition\n");
      exit(-1);
    }
  }
  if (new) {
    array[0] = 0;
    array[1] = 1;
    array[2] = 1;
    printf("[Success 9-2b.c]\nprogram 1 was spawn %d times, program 2 - %d "
           "times, total - %d times\n",
           array[0], array[1], array[2]);
  } else {
    mybuf.sem_num = 0;
    mybuf.sem_op = -1;
    mybuf.sem_flg = 0;
    if (semop(semid, &mybuf, 1) < 0) {
      printf("[Error 9-2b.c] can\'t wait for condition\n");
      exit(-1);
    }
    array[1] += 1;
    for (i = 0; i < 2000000000L; i++)
      ;
    array[2] += 1;
    printf("[Success 9-2b.c]\nprogram 1 was spawn %d times, program 2 - %d "
           "times, total - %d times\n",
           array[0], array[1], array[2]);
    mybuf.sem_num = 0;
    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    if (semop(semid, &mybuf, 1) < 0) {
      printf("[Error 9-2b.c] can\'t wait for condition\n");
      exit(-1);
    }
  }
  if (shmdt(array) < 0) {
    printf("[Error 9-2b.c] can\'t detach shared memory\n");
    exit(-1);
  }
  return 0;
}