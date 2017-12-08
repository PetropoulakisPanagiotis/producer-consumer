#include "mySem.h"

union semun{
    int val;
    struct semid_ds *buf;
    ushort *array;
};

// Failure: return -1 //

// Create and initialize semaphores set. Returns semaphore id //
int semCreate(key_t key, int nsems,int val){
    int semid,i;
    union semun arg;
    int error; // Keep errors


    if ((key < 0) || (nsems <= 0))
        return -1;

    semid = semget(key,nsems,0666|IPC_CREAT);
    if (semid < 0)
        return -1;

    // Initialize semaphores set //
    arg.val = val;

    for(i = 0; i < nsems; i++){

        error = semctl(semid,i,SETVAL,arg);
        if (error < 0)
            return -1;
    } // End for

    return semid;
}

// Operations //

// Down given semaphore //
int semDown(int semid, int sem_num){
    struct sembuf sb;

    if((semid < 0) || (sem_num < 0))
        return -1;

    sb.sem_num = sem_num;
    sb.sem_op = -1;
    sb.sem_flg = 0;

    return semop(semid,&sb,1);
}

// Up given semaphore //
int semUp(int semid, int sem_num){
    struct sembuf sb;

    if((semid < 0) || (sem_num) < 0)
        return -1;

    sb.sem_num = sem_num;
    sb.sem_op = 1;
    sb.sem_flg = 0;

    return semop(semid,&sb,1);
}

// Wait until current semaphore reach zero //
int semWaitUntilZero(int semid, int sem_num){
    struct sembuf sb;

    if((semid < 0) || (sem_num < 0))
        return -1;

    sb.sem_num = sem_num;
    sb.sem_op = 0;
    sb.sem_flg = 0;

    return semop(semid,&sb,1);
}

// Up semaphore with given value //
// Ex: semaphore A with value 0  //
// Call semUpN with N = 3        //
// sempahore A will have value 3 //
int semOpN(int semid,int sem_num, int value){
    struct sembuf sb;

    if((semid < 0) || (sem_num < 0))
        return -1;

    sb.sem_num = sem_num;
    sb.sem_op = value;
    sb.sem_flg = 0;

    return semop(semid,&sb,1);
}
// Delete given semaphores set //
int semDel(int semid){

    if(semid < 0)
        return -1;

    return semctl(semid,0,IPC_RMID);
}

// Editor:
// sdi1500129
// Panagiotis Petropoulakis
