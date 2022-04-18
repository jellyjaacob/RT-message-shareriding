/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#ifndef PRODUCER_H
#define PRODUCER_H

#include <semaphore.h>
#include <unistd.h>
#include "sharedStruct.h"
#include "broker.h"
#include <time.h>

//producer function to accept requests for human and autonomous drivers
//publishes these requests to the broker
//takes in a void pointer to access struct with semaphores
void* producer(void* voidPtr);

#endif
