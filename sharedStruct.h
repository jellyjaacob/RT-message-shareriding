/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#ifndef SHARED_STRUCT
#define SHARED_STRUCT

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include "broker.h"

#define DEFAULT_PRODUCTION_LIMIT 120
#define MAX_RIDER_REQUEST 12
#define MAX_HUMAN_RIDER_REQUEST 4
#define HUMAN 0
#define AUTONOMOUS 1

using namespace std;

struct rideShare {

    sem_t maxHumanRequests;         // semaphore for max amount of human requests
    sem_t maxRiderRequests;         // semaphore for max amount of rider requests
    sem_t unconsumedRequests;       // semaphore for what is currently on broker (unconsumed)
    sem_t mutex;                    // semaphore to give a producer/consumer access to broker queue (mutex)
    sem_t finalRequest;                 // semaphore for the barrier
    //sem_t finalCostRequest;           // semaphore for the cost barrier
    //sem_t finalFastRequest;           // semaphore for the fast barrier

    queue<REQUEST*> *buffer; // buffer to hold the requests
    
    // flags for optional arguments, set to 0 for false 1 for true
    int nFlag;
    int cFlag;
    int fFlag;
    int hFlag;
    int aFlag;

    // values to store optional arguments
    int nVal;
    int cVal;
    int fVal;
    int hVal;
    int aVal;

    int consumer_id;        // id for consumer
    int producer_id;        // id for producer
    int curRequests;        // current amount of requests
    int maxRequests;        // max amount of requests

};

#endif