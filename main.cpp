/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#define DEFAULT_PRODUCTION_LIMIT 120;

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
using namespace std;
#define CFB 1;
#define EES 2;
sem_t semEmpty;
sem_t semFull;

int main (int argc, char* argv[]) {

    sem_t MutualExclusion;

    if (sem_init(&MutualExclusion, 0, 1) == -1)
	    // unable to initialize semaphore, report failure;
        perror("Thread was unable to be created!");
    
    int idx, Option;

    // parameters
    int numRequest;

    // get optional command line arguments
    while ((Option = getopt(argc, argv, "n:c:f:h:a:"))) {
        
        switch(Option) {
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

}