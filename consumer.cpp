#include "pc_structure.hpp"

int main(){
    // while(created == false);
    int shared_mem_id = shmget((key_t)222, sizeof(shared_str), 0666);
    if(shared_mem_id == -1){
        std::cerr << "shmget_con\n";
        exit(EXIT_FAILURE);
    }

    shared_str *pc = (shared_str*)shmat(shared_mem_id, NULL, 0);

    pc->out = 0;

    if(sem_wait(&(pc->sema)) != 0){
        std::cerr << "sem_wait";
        exit(EXIT_FAILURE);
    }

        std::cout << "Consumer Entered Crit Section\n";
        std::cout << pc->table[pc->out] << "read from table \n";
        pc->table[pc->out] = ' ';
        pc->out = (pc->out + 1) % 2;

    if(sem_post(&(pc->sema)) != 0){
        std::cerr << "sem_post";
        exit(EXIT_FAILURE);
    }



}