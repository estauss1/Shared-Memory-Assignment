#include "pc_structure.hpp"

#define     shared_table    pc->table
#define     in_pos          pc->in

int main(){
    
    int shared_mem_id = shmget((key_t)222, sizeof(shared_str), 0666|IPC_CREAT);
    if(shared_mem_id == -1){
        std::cerr << "shmget_prod\n";
        exit(EXIT_FAILURE);
    }

    shared_str *pc = (shared_str*)shmat(shared_mem_id, NULL, 0);
    
    //semaphore = 1 and shared by processes  
    if(sem_init(&(pc->sema), 1, 0) != 0){              
        std::cerr << "sem_init";
        exit(EXIT_FAILURE);
    }
        //put first item in table                             
        std::cout << std::endl << std::endl 
                  << "Producer Entered Critical Section\n";
        char next_char = 'A';   
        in_pos = 0;
        shared_table[in_pos] = next_char;
        shared_table[1] = ' ';
        ++next_char;
        std::cout << "'"<< shared_table[in_pos] <<"' placed in table at position: " 
                  << in_pos << std::endl << std::endl;
        in_pos = (in_pos + 1) % 2;

    if(sem_post(&(pc->sema)) != 0){                            
        std::cerr << "sem_post";
        exit(EXIT_FAILURE);
    }

    int items_produced = 1;

    while(items_produced < 6){
        
        if(sem_wait(&(pc->sema)) != 0){ 
            std::cerr << "sem_wait";
            exit(EXIT_FAILURE);
        }
          
        if(shared_table[in_pos] == ' '){
            std::cout << "Producer Entered Critical Section\n";
            ++items_produced;
            shared_table[in_pos] = next_char;
            std::cout <<"'" << shared_table[in_pos] << "' placed in table at position: " 
                      << in_pos << std::endl << std::endl;
            ++next_char;
            in_pos = (in_pos + 1) % 2;
        }

        if(sem_post(&(pc->sema)) != 0){
            std::cerr << "sem_post";
            exit(EXIT_FAILURE);
        }
        sleep(1);                                            
    }
    
    //detach shared memory
    if(shmdt(((void*)pc)) == -1){                               
        std::cerr << "shmdt_prod\n";
        exit(EXIT_FAILURE);
    }
}