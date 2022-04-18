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
        if (prodAttr->hFlag && request_id == 0) {
            timer.tv_sec = prodAttr->hVal / MSPERSEC;
            timer.tv_nsec = (prodAttr->hVal / MSPERSEC) * NSPERMS;
            nanosleep(&timer, NULL); // set the delay after what was passed after -h
        } else if (prodAttr->aFlag && request_id == 1){
            timer.tv_sec = prodAttr->aVal / MSPERSEC;
            timer.tv_nsec = (prodAttr->aVal / MSPERSEC) * NSPERMS;            
            nanosleep(&timer, NULL); // set the delay after what was passed after -e
        }
        //until current is greater than max, produce
        if(prodAttr->curRequests < prodAttr->maxRequests){
            if(request_id == 0){ // check if it is a human request
                sem_wait(&prodAttr->maxHuman);
            }
            sem_wait(&prodAttr->locked); // lock the semaphore until space is available

            sem_wait(&prodAttr->access); // give access to the current type of request
            add(request_id, prodAttr->buffer);
            prodAttr->curRequests++;
            sem_post(&prodAttr->currBrokerReq); // signal the current broker request is on
            sem_post(&prodAttr->access); // do not give access to current type of request
        }
        else{
            sem_post(&prodAttr->currBrokerReq);
            sem_post(&prodAttr->access);
            break;
        }
    }
    pthread_exit(NULL);
}