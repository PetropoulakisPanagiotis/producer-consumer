#pragma once
#include <sys/time.h>
#include "mySem.h"
#include "myMem.h"

// Algorithm for child processes //
int child_work(int*,int,int,int,int,int);

// Make oparations with final results //
int handle_results(int*,int,double);

// Initialize all semaphores //
int initialize_sem(int,int*,int,int*,int,int*);

// Destroy all semaphores //
int destroy_sem(int,int,int);

// Initialize shared memory //
int initialize_shared_mem(int,int*);

// Destroy shared memory //
int destory_shared_mem(int);

// Editor:
// Panagiotis Petropoulakis
// sdi1500129
