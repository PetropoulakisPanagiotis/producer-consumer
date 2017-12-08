#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include "myLibrary/task.h"

int main(int argc, char*argv[]){
    int array_length; // Length of data
    int number_of_processes;
    int *array; // Data
    pid_t pid;
    int i,j;
    key_t buffer_key = 1,empty_key = 2,full_key = 3,mutex_key = 4;
    int buffer_id,empty_id,full_id,mutex_id;
    int *buffer;
    int error; // Keep errors

    // Invalid arguments //
    if(argc != 3)
        return -1;

    // Convert command line arguments //
    array_length = atoi(argv[1]);
    number_of_processes = atoi(argv[2]);

    if((array_length <= 3000) || (number_of_processes <= 0))
        return -1;

    // Initialize seed //
    srand(time(NULL));

    // Create array //
    array = malloc(sizeof(int) * array_length);
    if(array == NULL)
        return -1;

    // Initialize array with random numbers //
    for(i = 0; i < array_length; i++)
        array[i] = (rand() % 11);

    // Initialize shared memory segment   //
    // Buffer: our data                   //
    error = initialize_shared_mem(buffer_key,&buffer_id);
    if(error == -1)
        return -1;

    // Get shared memory //
    buffer = memGet(buffer_id);

    // Initialize semaphores                                 //
    // Empty: Feeder should write new data in buffer         //
    // Full: Every child procces should read only once       //
    // every same data from buffer                           //
    // Mutex: protect oparations in file                     //
    error = initialize_sem(empty_key,&empty_id,full_key,&full_id,mutex_key,&mutex_id);
    if(error == -1)
        return -1;

    // Feeder creates childs. Childs perform calculations //
    for(i = 0; i < number_of_processes; i++){

        pid = fork();

        if(pid == 0){
            child_work(buffer,array_length,number_of_processes,mutex_id,full_id,empty_id);
            exit(0);
        }
    } // End for

    // Keep current time //
    struct timeval start;

    // Feeder                   //
    for(i = 0; i < array_length; i++){

        // Copy in buffer current number and time //
        memcpy(buffer,&array[i],sizeof(int));
        buffer += sizeof(int);

        // Fix time //
        gettimeofday(&start,NULL);

        memcpy(buffer,&start,sizeof(struct timeval));
        buffer -= sizeof(int); // Move buffer pointer at the beginning

        // Buffer writes new content. Childs should read this content //
        // We have n childs -> n reads. Fedder waits n reads          //
        semOpN(full_id,0,number_of_processes);
        semOpN(empty_id,0,number_of_processes);

        // Wait until all childs have read current content //
        // At the beginning empty is N and at the end is 0 //
        semWaitUntilZero(empty_id,0);
    } // End for

    // Wait all childs //
    wait(NULL);

    // Detach pointers from shared memory segments //
    error = memDetach(buffer);
    if(error == -1)
        return -1;

    // Destroy shared memory segment and semaphores //
    error = destory_shared_mem(buffer_id);
    if(error == -1)
        return -1;

    error = destroy_sem(empty_id,full_id,mutex_id);
    if(error == -1)
        return -1;

    // Delete array of feeder //
    free(array);

    return 0;
}

// Editor:
// Panagiotis Petropoulakis
// sdi1500129
