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
#include "broker.h"
#include <pthread.h>
#include <semaphore.h>

#define DEFAULT_PRODUCTION_LIMIT 120;
#define MAX_RIDER_REQUEST 12;
#define MAX_HUMAN_RIDER_REQUEST 4;
#define PRODUCERS 2;
#define CONSUMERS 2;
#define REQUEST_TYPES 2;

using namespace std;

struct rideShare {

    sem_t maxHuman;         // semaphore for max amount of human request
    sem_t currBrokerReq;    // semaphore for what it is on current broken request
    sem_t access;           // semaphore to give a producer/consumer access to broker queue (mutex)
    sem_t locked;           // semaphore for locking broker queue until there is room/empty space on buffer
    sem_t finalReq;         // semaphore for the last request

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