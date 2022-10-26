#include "pc_structure.hpp"


int main(){
    shared_str *pc;
    int fd;

    fd = shm_open("/sharedmem", O_CREAT | O_RDWR, 0);
    if (fd == -1){
        std::cerr << "smh_open";
        exit(EXIT_FAILURE);
    }

    if(ftruncate(fd, sizeof(shared_str)) == -1) {
        std::cerr << "ftruncate";
        exit(EXIT_FAILURE);
    }

    pc = (shared_str*)mmap(NULL, sizeof(shared_str), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(pc == MAP_FAILED){
        std::cerr << "mmap";
        exit(EXIT_FAILURE);
    }
    
    if(shm_unlink("/sharedmem") == -1){
        std::cerr << "shm_unlink";
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}