/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#define DEFAULT_PRODUCTION_LIMIT 120;
#define MAX_RIDER_REQUEST 12;
#define MAX_HUMAN_RIDER_REQUEST 4;
#define PRODUCERS 2;
#define CONSUMERS 2;

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "semaphore.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <vector>
#include "ridesharing.h"

using namespace std;

int main (int argc, char* argv[]) {
    
    int idx, option;

    // parameters
    int numRequest;

    // get optional command line arguments
    while ((option = getopt(argc, argv, "n:c:f:h:a:"))) {
        
        switch(option) {
            case 'n':
                numRequest = atoi(optarg);
            case 'c':
                //TODO
            case 'f':
                // Similar argument for the fast-matching dispatcher
            case 'h':
                // number of milliseconds required to produce a ride request for  a human driver
            case 'a':
                // number of milliseconds required to produce a ride request for an autonomous driver
        }
    }

    // semaphores + pthreads
    
    sem_t sharedSemaphore;
    int sharedValue = 0;

    if (sem_init(&sharedSemaphore, 0, sharedValue) == -1)
	    // unable to initialize semaphore, report failure;
        perror("Thread was unable to be created!");

    //for (int i = 0; i < PRODUCERS; i++) {}
        // pthread_create();
        

}