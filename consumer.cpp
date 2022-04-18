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
    static timespec timer; // struct to use nanosleep

    int consumerID = consAttr->consumer_id++;         // variable to hold consumer ID
    string consumerName = consumerID ? "RoboDriver" : "HumanDriver";    //set the type of driver based on the consumer id

    while(true){
        sem_wait(&consAttr->currBrokerReq);                 // lock what is on the broker

        sem_wait(&consAttr->access);                        // lock access to the critical region
        int cID = remove(consumerName, consAttr -> buffer); // consume the item by taking it off the broker
        if (cID == 0) { sem_post(&consAttr -> maxHuman); }  
        sem_post(&consAttr->access);                        // unlock and give access
        sem_post(&consAttr->locked);                        // unlock the space on the broker
        
        if(consAttr->curRequests == consAttr-> maxRequests) {   // when max requests are reached -> final request has been made -> break out of loop
            sem_post(&consAttr->finalReq);
            break;
        }

        // check the flags and set the appropriate delay
        if (consAttr->cFlag && consumerID) {                    
            timer.tv_nsec = (double)consAttr->cVal / NS_PER_MS; // set the delay after what was passed after -c
            nanosleep(&timer, NULL);
        }
        else if (consAttr->fFlag && consumerID == 0) {                                                       
            timer.tv_nsec = (double)consAttr->fVal / NS_PER_MS; // set the delay after what was passed after -f
            nanosleep(&timer, NULL);
        }
    }
    pthread_exit(NULL);
}