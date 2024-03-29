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
#include "producer.h"
#include "consumer.h"
#include "broker.h"
#include "sharedStruct.h"
#include "io.h"

using namespace std;

int main (int argc, char* argv[]) {

    struct rideShare* sharedAttribute = new rideShare(); // initialize the struct
    
    //initialize our struct's semaphores and variables
    sem_init(&sharedAttribute->maxHumanRequests, 0, MAX_HUMAN_RIDER_REQUEST);
    sem_init(&sharedAttribute->maxRiderRequests, 0, MAX_RIDER_REQUEST);
    sem_init(&sharedAttribute->unconsumedRequests, 0, 0);    
    sem_init(&sharedAttribute->mutex, 0, 1);
    sem_init(&sharedAttribute->finalRequest, 0, 0);
    //sem_init(&sharedAttribute->finalCostRequest, 0, 0);
    //sem_init(&sharedAttribute->finalFastRequest, 0, 0);

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

    sharedAttribute->curRequests = 0;
    sharedAttribute->maxRequests = DEFAULT_PRODUCTION_LIMIT;
    
    int idx, option;

    // get optional command line arguments
    while ((option = getopt(argc, argv, "n:c:f:h:a:")) != -1) {
        
        switch(option) {
            case 'n':
                sharedAttribute->nFlag = 1;
                sharedAttribute->maxRequests = atoi(optarg);
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

    //wait for the barrier to consume the final request
    //sem_wait(&sharedAttribute->finalCostRequest);
    //sem_wait(&sharedAttribute->finalFastRequest);
    sem_wait(&sharedAttribute->finalRequest);       // enter critical region

    int *cost = getCostDispatch();
    int *fast = getFastDispatch();
    int *produced = getProduced();
    int *producers[REQUEST_TYPES] = {cost, fast};
    io_production_report(produced, producers);
    return 0;                                       // exit 
}