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

void* consumer(void* voidPtr);

#endif
