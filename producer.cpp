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

    int request_id = prodAttr->producer_id++; // set request_id to human/robot + increment to human/robot
    
    while(true) {

        // sleep depending on the -h and -a flags
        if (prodAttr->hFlag && request_id == HUMAN) {
            usleep(MSPERSEC * prodAttr->hVal);
        } else if (prodAttr->aFlag && request_id == AUTONOMOUS){
            usleep(MSPERSEC * prodAttr->aVal);
        }

        if (prodAttr->curRequests >= prodAttr->maxRequests) {
            sem_post(&prodAttr->unconsumedRequests);        // lock what is on the broker
            sem_post(&prodAttr->mutex);                     // exit critical region
            break;
        } else {                                            // until current is greater than max, produce
            if(request_id == HUMAN)                         // check for human request, 0 for human and 1 for autonomous
                sem_wait(&prodAttr->maxHumanRequests);

            sem_wait(&prodAttr->maxRiderRequests);          // lock until space is available
            sem_wait(&prodAttr->mutex);                     // enter critical region

            if (prodAttr->curRequests == prodAttr->maxRequests)
                break;                                      // in the case that an extra requests goes through, we just break
            
            add(request_id, prodAttr->buffer);              // add the request into buffer
            prodAttr->curRequests++;                        // increment up to max
        
            sem_post(&prodAttr->unconsumedRequests);        // lock what is on the broker
            sem_post(&prodAttr->mutex);                     // exit critical region
        }
    } 
    pthread_exit(NULL);
}