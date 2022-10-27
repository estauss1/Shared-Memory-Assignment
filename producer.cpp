#include "pc_structure.hpp"

int main(){
    
    int shared_mem_id = shmget((key_t)222, sizeof(shared_str), 0666|IPC_CREAT);
    created = true;
    if(shared_mem_id == -1){
        std::cerr << "shmget_prod\n";
        exit(EXIT_FAILURE);
    }

    shared_str *pc = (shared_str*)shmat(shared_mem_id, NULL, 0);
    
    if(sem_init(&(pc->sema), 1, 0) != 0){
        std::cerr << "sem_init";
        exit(EXIT_FAILURE);
    }
        std::cout << "Producer entering Crit section\n";
        pc->in = 0;
        pc->table[pc->in] = 'o';
        std::cout << "o placed on table in position" << pc->in;
        pc->in = (pc->in + 1) % 2;

    if(sem_post(&(pc->sema)) != 0){
        std::cerr << "sem_post";
        exit(EXIT_FAILURE);
    }

    if(sem_wait(&(pc->sema)) != 0){
        std::cerr << "sem_wait";
        exit(EXIT_FAILURE);
    }

        std::cout << "Producer entering Crit Section\n";
        pc->table[pc->in] = 'o';
        std::cout << "o placed on table in position" << pc->in << std::endl;
        pc->in = (pc->in + 1) % 2;

    if(sem_post(&(pc->sema)) != 0){
        std::cerr << "sem_post";
        exit(EXIT_FAILURE);
    }

}