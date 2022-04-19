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
            
            sem_wait(&consAttr->unconsumedRequests);            // lock what is on the broker

            sem_wait(&consAttr->mutex);                         // lock access to the critical region
            int cID = remove(consumerName, consAttr -> buffer); // consume the item by taking it off the broker
            if (cID == HUMAN) { sem_post(&consAttr -> maxHumanRequests); }  // if human request, increment 
            sem_post(&consAttr->mutex);                         // unlock and give access
            sem_post(&consAttr->maxRiderRequests);              // unlock the space on the broker
        }
        else { // when max requests are reached -> final request has been made -> break out of loop
            sem_post(&consAttr->mutex);
            break;
        }

        // sleep depending on the -c and -f flags
        if(consAttr->cFlag && consumerID == HUMAN) {
            usleep(MSPERSEC * consAttr->cVal);
        } else if (consAttr->fFlag && consumerID == AUTONOMOUS){
            usleep(MSPERSEC * consAttr->fVal);
        }
    }

    if (consAttr->curRequests >= consAttr->maxRequests && (consumerName.compare("CostAlgoDispatch") || consumerName.compare("FastAlgoDispatch")))
        sem_post(&consAttr->finalRequest);
    pthread_exit(NULL); 

}