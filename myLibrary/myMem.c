#include "myMem.h"

// Failure: return -1 //

int memCreate(key_t key,int nbytes){

    if((nbytes <= 0) || (key < 0))
        return -1;

    // Create shared memory segment and return id //
    return shmget(key,nbytes,0644|IPC_CREAT);
}

// Get a pointer in shared memory segment //
void* memGet(int shmid){

    if(shmid < 0)
        return NULL;

    return shmat(shmid,0,0);
}

// Detach pointer from shared memory segment //
int memDetach(void *ptr){
    return shmdt(ptr);
}

// Delete shared memory segment //
int memDel(int shmid){

    if(shmid < 0)
        return -1;

    return shmctl(shmid,0,IPC_RMID);
}

// Editor:
// Sdi1500129
// Panagiotis Petropoulakis
