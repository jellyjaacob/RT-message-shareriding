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
#define NS_PER_MS 1000000
// 1000 ms/s
#define MS_PER_SEC 1000

void* consumer(void* voidPtr) {

    struct rideShare *consAttr = (struct rideShare *)voidPtr; // semaphore to operate on
    struct timespec timer; // struct to use nanosleep

    sem_wait(&consAttr -> start);                   // lock the start semaphore
    int consumerID = consAttr->consumer_id++;         // variable to hold consumer ID
    string consumerName = consumerID ? "RoboDriver" : "HumanDriver";
    sem_post(&consAttr -> start);                   // unlock the start semaphore

    /*
    while (consAttr -> maxQuantity >= 0) {  //loop until the consumers reach max quantity
        while (sem_wait(&consAttr->currBrokerReq) && )  //lock while there are still consumer requests

    }

    if(consAttr->maxQuantity > 0) // as long as semaphore is positive
        while(!sem_wait(&consAttr->maxQuantity)) { // produce until maxQuantity
        
            sem_wait(&consAttr -> access);                          // lock the semaphore and give current consumer access to broker queue
            int cID = remove(consumerName, consAttr -> buffer);
            if (cID == 0) { sem_post(&consAttr -> maxHuman); }      // if human driver is consumed, signal to attain more requests
            sem_post(&consAttr -> locked);                          // unlock semaphore if there is room on the queue
            consAttr -> maxRequests--;                             // decrement the amount of request to consume

            if (consAttr -> maxRequests == 0) { //sem_post(&consAttr -> ) } // suppose to kill all threads b/c all requests have been consumed

            sem_post(&consAttr -> access);                          // unlock the semaphore and remove access to broker queue
        
            if (consAttr->cFlag && consumerID) {                             // delay consumption for ethel
                timer.tv_nsec = (double)consAttr->cVal / NS_PER_MS; // set the delay after what was passed after -E
                nanosleep(&timer, NULL);
            }
            else if (consAttr->fFlag && consumerID == 0)
            {                                                 // delay consumption for lucy
                timer.tv_nsec = (double)consAttr->fVal / NS_PER_MS; // set the delay after what was passed after -L
                nanosleep(&timer, NULL);
            }
        } */
    while (consAttr -> maxQuantity >= 0) {  //loop until the consumers reach max quantity
        if(consAttr -> currBrokerReq > 0){
            while (!sem_wait(&consAttr->currBrokerReq)){
                sem_wait(&consAttr -> access);                          // lock the semaphore and give current consumer access to broker queue
                int cID = remove(consumerName, consAttr -> buffer);
                if (cID == 0) { sem_post(&consAttr -> maxHuman); }      // if human driver is consumed, signal to attain more requests
                sem_post(&consAttr -> locked);                          // unlock semaphore if there is room on the queue
                consAttr -> maxRequests--;                             // decrement the amount of request to consume

                if (consAttr -> maxRequests == 0) { //sem_post(&consAttr -> ) } // suppose to kill all threads b/c all requests have been consumed

                sem_post(&consAttr -> access);                          // unlock the semaphore and remove access to broker queue
            
                if (consAttr->cFlag && consumerID) {                             // delay consumption for ethel
                    timer.tv_nsec = (double)consAttr->cVal / NS_PER_MS; // set the delay after what was passed after -E
                    nanosleep(&timer, NULL);
                }
                else if (consAttr->fFlag && consumerID == 0)
                {                                                 // delay consumption for lucy
                    timer.tv_nsec = (double)consAttr->fVal / NS_PER_MS; // set the delay after what was passed after -L
                    nanosleep(&timer, NULL);
                }
            }
        }
    }
}