/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#include <pthread.h>
#include <time.h>
#include "semaphore.h"
#include "ridesharing.h"
#include "producer.h"
#include "consumer.h"
#include "broker.h"
#include "sharedStruct.h"

using namespace std;

int main (int argc, char* argv[]) {

    struct rideShare* sharedAttribute = new rideShare(); // initialize the struct
    
    //initialize our struct's semaphores and variables
    int maxProduction = DEFAULT_PRODUCTION_LIMIT;
    int maxHR = MAX_HUMAN_RIDER_REQUEST;
    int maxRR = MAX_RIDER_REQUEST;

    sem_init(&sharedAttribute->start, 0, 1);
    sem_init(&sharedAttribute->maxQuantity, 0, maxProduction);
    sem_init(&sharedAttribute->maxHuman, 0, maxHR);
    sem_init(&sharedAttribute->currBrokerReq, 0, 0);
    sem_init(&sharedAttribute->access, 0, 1);
    sem_init(&sharedAttribute->locked, 0, maxRR);

    sharedAttribute->buffer = new queue<REQUEST*>;
    sharedAttribute->nFlag = 0;
    sharedAttribute->cFlag = 0;
    sharedAttribute->fFlag = 0;
    sharedAttribute->hFlag = 0;
    sharedAttribute->aFlag = 0;

    sharedAttribute->nVal = 0;
    sharedAttribute->cVal = 0;
    sharedAttribute->fVal = 0;
    sharedAttribute->hVal = 0;
    sharedAttribute->aVal = 0;

    sharedAttribute->consumer_id = 0;
    sharedAttribute->producer_id = 0;
    sharedAttribute->maxRequests = DEFAULT_PRODUCTION_LIMIT;
    

    int idx, option;

    // get optional command line arguments
    while ((option = getopt(argc, argv, "n:c:f:h:a:")) != -1) {
        
        switch(option) {
            case 'n':
                sharedAttribute->nFlag = 1;
                sharedAttribute->maxQuantity = atoi(optarg);
                break;
            case 'c':
                sharedAttribute->cFlag = 1;
                sharedAttribute->cVal = atoi(optarg);
                break;
            case 'f':
                sharedAttribute->fFlag = 1;
                sharedAttribute->fVal = atoi(optarg);
                break;
            case 'h':
                sharedAttribute->hFlag = 1;
                sharedAttribute->hVal = atoi(optarg);
                break;
            case 'a':
                sharedAttribute->aFlag = 1;
                sharedAttribute->aVal = atoi(optarg);
                break;
            default:
                exit(1);
        }
    }
        
    pthread_t humanDriverThread;
    pthread_t roboDriverThread;
    pthread_t costDispatchThread;
    pthread_t fastDispatchThread;

    pthread_attr_t pthread_attributes;
    pthread_attr_init(&pthread_attributes);

    pthread_create(&humanDriverThread, &pthread_attributes, producer, sharedAttribute);
    pthread_create(&roboDriverThread, &pthread_attributes, producer, sharedAttribute);
    pthread_create(&costDispatchThread, &pthread_attributes, consumer, sharedAttribute);
    pthread_create(&fastDispatchThread, &pthread_attributes, consumer, sharedAttribute);

    //do something with semaphores
}