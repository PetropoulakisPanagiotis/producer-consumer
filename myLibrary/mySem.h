#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

// Get and initialize semaphores set //
int semCreate(key_t,int,int);

// Operations //
int semDown(int,int);
int semUp(int,int);
int semWaitUntilZero(int,int);
int semOpN(int,int,int);

// Delete semaphores set //
int semDel(int);

// Editor:
// sdi1500129
// Panagiotis Petropoulakis
