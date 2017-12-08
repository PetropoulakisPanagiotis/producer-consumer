#include "task.h"
#include <string.h>

// Every child procces reads all numbers and fixes it's running average //
// At the end every child writes in a file it's result                  //
int child_work(int *buffer, int array_length, int number_of_processes, int mutex_id, int full_id, int empty_id){
    int* data; // Keep data
    double running_average; // Running average of current child
    struct timeval stop,start;
    int i;

    if((buffer == NULL) ||(array_length <= 0) || (number_of_processes <= 0))
        return -1;

    if((mutex_id < 0) || (full_id < 0) || (empty_id < 0))
        return -1;

    // Create array to keep data //
    data = malloc(sizeof(int) * array_length);
    if(data == NULL)
        return -1;

    // Read all data //
    for(i = 0; i  < array_length; i++){

        // Read from buffer - Only if current data is not the same like the previous one //
        // N childs can read the same data                                               //
        semDown(full_id,0);

        data[i] = (*buffer); // Keep number

        gettimeofday(&stop,NULL); // Get current time

        // Get old time //
        memcpy(&start,(buffer + sizeof(int)),sizeof(struct timeval));

        // Fix current running_average                    //
        // At the end we will divide it with array_length //
        running_average += ((double)(stop.tv_sec - start.tv_sec) * 1000) + ((double)(stop.tv_usec - start.tv_usec) / 1000);

        // Last loop call: handle_results //
        if(i == array_length - 1){

            // Fix running_average //
            running_average = running_average / (double)array_length;

            // Every child writes it's results in file //
            // We should protect this operation        //
            // Note: Current child writes at the end   //
            // of file                                 //
            semDown(mutex_id,0);
            handle_results(data,array_length,running_average);
            semUp(mutex_id,0);
        }

        // Wait all childs to finish //
        semWaitUntilZero(full_id,0);

        // Every child has read current content        //
        // When the last child down empty semaphore    //
        // fedder will be released and he will add new //
        // content in buffer                           //
        semDown(empty_id,0);
    } // End for

    // Delete array //
    free(data);

    return 0;
}

// Every child handle it's results                   //
// Write in file its pid, values and running average //
// Also print in stdout pid and running average      //
int handle_results(int* data,int array_length,double running_average){
    FILE* fp = fopen("results.txt","a");
    int i,error;

    if((fp == NULL) || (data == NULL) || (array_length <= 0))
       return -1;

    error = fprintf(fp,"Process pid: %d\n",getpid());
    if(error < 0)
        return -1;

    for(i = 0; i < array_length; i ++){
        if(i == 0){
            error = fprintf(fp,"Content: \n");
            if(error < 0)
                return -1;
        }

        error = fprintf(fp,"%d ",data[i]);
        if(error < 0)
            return -1;

        if(i % 42 == 0){
            error = fprintf(fp,"\n");
            if(error < 0)
                return -1;
        }
    } // End for

    error = fprintf(fp,"\nRunning average: %lf\n\n",running_average);
    if(error < 0)
        return -1;

    printf("Process pid: %d - Running average: %lf\n",getpid(),running_average);

    fflush(fp);
    fclose(fp);

    return 0;
}

// Initialize all semaphores //
int initialize_sem(int empty_key,int* empty_id, int full_key, int* full_id, int mutex_key, int* mutex_id){

    if((empty_key < 0) || (full_key < 0) || (mutex_key < 0))
        return -1;

    if((empty_id == NULL) || (full_id == NULL) || (mutex_id == NULL))
        return -1;

    // Empty buffer. Feeder will add new data //
    *empty_id = semCreate(empty_key,1,0);
    if(*empty_id == -1)
        return -1;

    // Full buffer. Child can receive data //
    *full_id = semCreate(full_key,1,0);
    if(*full_id == -1)
        return -1;

    // For writing in file //
    *mutex_id = semCreate(mutex_key,1,1);
    if(*mutex_id == -1)
        return -1;

    return 0;
}

// Destroy all semaphores and check for errors //
int destroy_sem(int empty_id, int full_id, int mutex_id){
    int error;

    if((empty_id < 0) || (full_id < 0) || (mutex_id < 0))
        return -1;

    error = semDel(empty_id);
    if(error == -1)
        return -1;

    error = semDel(full_id);
    if(error == -1)
        return -1;

    error = semDel(mutex_id);
    if(error == -1)
        return -1;

    return 0;
}

// Initialize shared memory and check for errors //
int initialize_shared_mem(int buffer_key, int* buffer_id){

    if((buffer_key < 0) || (buffer_id == NULL))
        return -1;

    // Main buffer //
    *buffer_id = memCreate(buffer_key,2 * sizeof(int));
    if(*buffer_id == -1)
        return -1;

    return 0;
}

// Destroy shared memory and check for errors     //
// Don't forget to detach memory before delete it //
int destory_shared_mem(int buffer_id){
    int error;

    if(buffer_id < 0)
        return -1;

    error = memDel(buffer_id);
    if(error == -1)
        return -1;

    return 0;
}

// Editor:
// Panagiotis Petropoulakis
// sdi1500129
