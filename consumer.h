/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#ifndef CONSUMER_H
#define CONSUMER_H

#include <semaphore.h>
#include <unistd.h>
#include "sharedStruct.h"
#include "broker.h"
#include <time.h>

//consumes requests by using a fast saving or a cost saving algorithm
//takes requests off the broker and consumes them in the order they are published (FIFO)
//takes in a void pointer to access struct with semaphores
void* consumer(void* voidPtr);

#endif
