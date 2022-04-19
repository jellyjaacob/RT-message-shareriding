/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#include "consumer.h"
// One million ns/ms
#define NSPERMS 1000000
// 1000 ms/s
#define MSPERSEC 1000

//consumes requests by using a fast saving or a cost saving algorithm
//takes requests off the broker and consumes them in the order they are published (FIFO)
//takes in a void pointer to access struct with semaphores
void* consumer(void* voidPtr) {

    struct rideShare *consAttr = (struct rideShare *)voidPtr; // semaphore to operate on
    static timespec timer; // struct to use nanosleep

    int consumerID = consAttr->consumer_id++;         // variable to hold consumer ID
    string consumerName = consumerID ? "CostAlgoDispatch" : "FastAlgoDispatch";    //set the type of driver based on the consumer id
    
    while(true){
        if(consAttr->curRequests < consAttr-> maxRequests) {
            
            sem_wait(&consAttr->unconsumedRequests);                    // lock what is on the broker

            sem_wait(&consAttr->mutex);                        // lock access to the critical region
            int cID = remove(consumerName, consAttr -> buffer); // consume the item by taking it off the broker
            if (cID == HUMAN) { sem_post(&consAttr -> maxHumanRequests); }  // if human request, increment 
            sem_post(&consAttr->mutex);                        // unlock and give access
            sem_post(&consAttr->maxRiderRequests);                        // unlock the space on the broker
        }
        else {   // when max requests are reached -> final request has been made -> break out of loop
            sem_post(&consAttr->mutex);
            sem_post(&consAttr->finalRequest);
            break;
        }

        // check the flags and set the appropriate delay
        if(consAttr->cFlag && consumerID == HUMAN) {
            timer.tv_sec = consAttr->cVal / MSPERSEC;
            timer.tv_nsec = (consAttr->cVal / MSPERSEC) * NSPERMS;
            nanosleep(&timer, NULL); // set the delay after what was passed after -h
        } else if (consAttr->fFlag && consumerID == AUTONOMOUS){
            timer.tv_sec = consAttr->fVal / MSPERSEC;
            timer.tv_nsec = (consAttr->fVal / MSPERSEC) * NSPERMS;            
            nanosleep(&timer, NULL); // set the delay after what was passed after -e
        }
    }
    /*
    if(consumerName.compare("CostAlgoDispatch")){
        sem_post(&consAttr->finalCostRequest);
    }
    else{
        sem_post(&consAttr->finalFastRequest);
    } */

    pthread_exit(NULL); 

    /*
    while(true){
        if(consAttr->curRequests >= consAttr-> maxRequests) {   // when max requests are reached -> final request has been made -> break out of loop
            sem_wait(&consAttr->currBrokerReq);                 // lock what is on the broker

            sem_wait(&consAttr->access);                        // lock access to the critical region
            int cID = remove(consumerName, consAttr -> buffer); // consume the item by taking it off the broker
            if (cID == 0) { sem_post(&consAttr -> maxHuman); }  
            sem_post(&consAttr->access);                        // unlock and give access
            sem_post(&consAttr->locked);                        // unlock the space on the broker
        }
        else{
            sem_post(&consAttr->access);
            break;
        }

        // check the flags and set the appropriate delay
        if (consAttr->cFlag && consumerID == 0) {
            timer.tv_sec = consAttr->cVal / MSPERSEC;
            timer.tv_nsec = (consAttr->cVal / MSPERSEC) * NSPERMS;
            nanosleep(&timer, NULL); // set the delay after what was passed after -h
        } else if (consAttr->fFlag && consumerID == 1){
            timer.tv_sec = consAttr->fVal / MSPERSEC;
            timer.tv_nsec = (consAttr->fVal / MSPERSEC) * NSPERMS;            
            nanosleep(&timer, NULL); // set the delay after what was passed after -e
        }
    }
    pthread_exit(NULL); */
}