#include <semaphore.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

struct shared_str {
  sem_t  sema;
  char   table[2];
  int    in;
  int    out;
};