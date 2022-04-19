/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#include "producer.h"
// One million ns/ms
#define NSPERMS 1000000
// 1000 ms/s
#define MSPERSEC 1000

//producer function to accept requests for human and autonomous drivers
//publishes these requests to the broker
//takes in a void pointer to access struct with semaphores
void* producer(void* voidPtr){

    struct rideShare *prodAttr;
    prodAttr = (rideShare*) voidPtr; // semaphore to operate on
    static timespec timer; // struct to use nanosleep

    int request_id = prodAttr->producer_id++; // once done, increment prod_id to human/robot driver

    
    while(true){

        // sleep depending on the -h and -a flags
        if (prodAttr->hFlag && request_id == HUMAN) {
            usleep(MSPERSEC * prodAttr->hVal);
        } else if (prodAttr->aFlag && request_id == AUTONOMOUS){
            usleep(MSPERSEC * prodAttr->aVal);
        }

        // until current is greater than max, produce
        if(prodAttr->curRequests < prodAttr->maxRequests) {
            // check for human request
            if(request_id == HUMAN) // 0 for human and 1 for autonomous
                sem_wait(&prodAttr->maxHumanRequests);

            sem_wait(&prodAttr->maxRiderRequests);          // lock the semaphore until space is available
            sem_wait(&prodAttr->mutex);                     // give access to the critical region

            add(request_id, prodAttr->buffer);
            prodAttr->curRequests++;                        // increment up to max
            sem_post(&prodAttr->unconsumedRequests);    
            sem_post(&prodAttr->mutex);                     // remove access to critical region
        }
        else{
            sem_post(&prodAttr->unconsumedRequests);    
            sem_post(&prodAttr->mutex);                     // remove access to critical region
            break;
        }
    }
    pthread_exit(NULL);
}