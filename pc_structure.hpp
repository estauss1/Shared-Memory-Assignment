#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

struct shared_str {
  sem_t  sema;
  char   table[2];
  int    in;
  int    out;
};