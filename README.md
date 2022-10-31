# Shared Memory Assignment for KSU OS Class 

## Producer program puts items in the table and consumer program reads items from the table

The producer and consumer programs use shared memory to communicate. The structure shared_str (defined in pc_structure.hpp) gives the shared memory segment structure. The shared_str defintion contains an unnamed semaphore which is used to prevent both processes from modifying the table at the same time. If the table is not full, the producer process puts a character in the table. If the table is not empty, the consumer process reads and outputs one of the characters in the table and then puts a blank character in it's place. The producer process puts a total of six characters in the table throughout it's execution and the consumer consumes the six characters.

## How to run

pc_structure.hpp must be used in order for proper execution since it contains the include directives needed for the programs and the structure definition.

Use the following commands:
1. g++ producer.cpp -pthread -lrt -o producer
2. g++ consumer.cpp -pthread -lrt -o consumer
3. ./producer & ./consumer &

after running you can use "rm producer consumer"