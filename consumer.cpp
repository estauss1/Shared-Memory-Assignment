#include "pc_structure.hpp"

int main(){

    int shared_mem_id = shmget((key_t)222, sizeof(shared_str), 0666);
    if(shared_mem_id == -1){
        std::cerr << "shmget_con\n";
        exit(EXIT_FAILURE);
    }

    shared_str *pc = (shared_str*)shmat(shared_mem_id, NULL, 0);

    int items_consumed = 0;
    pc->out = 0;
    while(items_consumed < 10){
        if(sem_wait(&(pc->sema)) != 0){
            std::cerr << "sem_wait";
            exit(EXIT_FAILURE);
        }
        if(pc->table[pc->out] != ' '){
            ++items_consumed;
            std::cout << "Consumer Entered Critical Section\n";
            std::cout << "The character '" << pc->table[pc->out] << "' was read from table position: " 
                      << pc->out << std::endl;
            pc->table[pc->out] = ' ';
            pc->out = (pc->out + 1) % 2;
        }

        if(sem_post(&(pc->sema)) != 0){
            std::cerr << "sem_post";
            exit(EXIT_FAILURE);
        }
    }

    if(sem_close(&(pc->sema)) != 0){
        std::cerr << "sem_close_con\n";
        exit(EXIT_FAILURE);
    }

}