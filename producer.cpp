#include "pc_structure.hpp"

int main(){
    
    int shared_mem_id = shmget((key_t)222, sizeof(shared_str), 0666|IPC_CREAT);
    if(shared_mem_id == -1){
        std::cerr << "shmget_prod\n";
        exit(EXIT_FAILURE);
    }

    shared_str *pc = (shared_str*)shmat(shared_mem_id, NULL, 0);
    
    if(sem_init(&(pc->sema), 1, 0) != 0){                      //semaphore = 1 and shared by processes               
        std::cerr << "sem_init";
        exit(EXIT_FAILURE);
    }
        char next_char = 'A';                                  //put first item in table and ' ' in 2nd pos
        std::cout << std::endl << "Producer Entered Critical Section\n";
        pc->in = 0;
        pc->table[pc->in] = next_char;
        pc->table[1] = ' ';
        ++next_char;
        std::cout << "'"<< pc->table[pc->in] <<"' placed in table at position: " 
                  << pc->in << std::endl;
        pc->in = (pc->in + 1) % 2;

    if(sem_post(&(pc->sema)) != 0){                             //1st item in table and ++semaphore
        std::cerr << "sem_post";
        exit(EXIT_FAILURE);
    }

    int items_produced = 1;

    while(items_produced < 10){
        if(sem_wait(&(pc->sema)) != 0){                         //wait until semaphore > 0
            std::cerr << "sem_wait";
            exit(EXIT_FAILURE);
        }
          
        if(pc->table[pc->in] == ' '){
            ++items_produced;
            std::cout << "Producer Entered Critical Section\n";
            pc->table[pc->in] = next_char;
            std::cout <<"'" << pc->table[pc->in] << "' placed in table at position: " 
                      << pc->in << std::endl;
            ++next_char;
            pc->in = (pc->in + 1) % 2;
        }

        if(sem_post(&(pc->sema)) != 0){
            std::cerr << "sem_post";
            exit(EXIT_FAILURE);
        }
        sleep(1);                                            
    }
    
    if(sem_close(&(pc->sema)) != 0){                                //deallocate named semaphore
        std::cerr << "sem_close_prod\n";
        exit(EXIT_FAILURE);
    }

    if(shmdt(((void*)pc)) == -1){                               //detach shared memory
        std::cerr << "shmdt_prod\n";
        exit(EXIT_FAILURE);
    }
}