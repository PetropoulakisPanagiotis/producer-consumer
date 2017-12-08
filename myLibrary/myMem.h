#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Create shared memory segment //
int memCreate(key_t,int);

// Get a pointer in shared memory segment //
void *memGet(int);

// Detached shared memory segment //
int memDetach(void *);

// Delete shared memory segment //
int memDel(int);

// Editor:
// Sdi1500129
// Panagiotis Petropoulakis
