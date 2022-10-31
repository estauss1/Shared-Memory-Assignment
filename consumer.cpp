#include "pc_structure.hpp"

#define     shared_table    pc->table
#define     out_pos         pc->out

int main(){

    int shared_mem_id = shmget((key_t)222, sizeof(shared_str), 0666);
    if(shared_mem_id == -1){
        std::cerr << "shmget_con\n";
        exit(EXIT_FAILURE);
    }

    shared_str *pc = (shared_str*)shmat(shared_mem_id, NULL, 0);

    int items_consumed = 0;
    out_pos = 0;

    while(items_consumed < 6){
        if(sem_wait(&(pc->sema)) != 0){
            std::cerr << "sem_wait";
            exit(EXIT_FAILURE);
        }

        if(shared_table[out_pos] != ' '){
            ++items_consumed;
            std::cout << "Consumer Entered Critical Section\n"
                      << "The character '" << shared_table[out_pos] 
                      << "' was read from table position: " 
                      << out_pos << std::endl << std::endl;
            shared_table[out_pos] = ' ';
            out_pos = (out_pos + 1) % 2;
        }

        if(sem_post(&(pc->sema)) != 0){
            std::cerr << "sem_post";
            exit(EXIT_FAILURE);
        }
    }

    //destroy unnamed semaphore
    if(sem_destroy(&(pc->sema)) == -1){        
        std::cerr << "sem_destroy";
        exit(EXIT_FAILURE);
    }
    
    //detach shared memory
     if(shmdt(((void*)pc)) == -1){                                  
        std::cerr << "shmdt_con\n";
        exit(EXIT_FAILURE);
     }
    
    //destroy shared memory
     if(shmctl(shared_mem_id, IPC_RMID, NULL) == -1){
        std::cerr << "shmctl\n";
        exit(EXIT_FAILURE);
     }
}