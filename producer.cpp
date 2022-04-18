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
#define NS_PER_MS 1000000
// 1000 ms/s
#define MS_PER_SEC 1000

void* producer(void* voidPtr){

    struct rideShare *prodAttr = new rideShare(); // semaphore to operate on
    static timespec timer; // struct to use nanosleep

    sem_wait(&prodAttr->start); // lock the semaphore 
    int request_id = prodAttr->producer_id++; // once done, increment prod_id to human/robot driver
    sem_post(&prodAttr->start); // unlock the semaphore so we can move into critical region

    //while (!sem_trywait(&prodAttr->maxQuantity)) // produce until 120 requests have been made | THIS IS WHAT IT SHOULD HAVE BEEN
    if(prodAttr->maxQuantity > 0) // as long as semaphore is positive
        while(!sem_wait(&prodAttr->maxQuantity)) { // produce until maxQuantity

            sem_wait(&prodAttr->locked); // lock the semaphore until space is available
            if (request_id == 0) { // check if it is a human request
                if(prodAttr->maxHuman > 0) { // as long as semaphore is positive
                    if (sem_wait(&prodAttr->maxHuman)) { // if request hasn't hit max human request, then decrement
                        sem_post(&prodAttr->maxQuantity); // increment the max qunatity 
                        continue;
                    }
                }

            }
            sem_wait(&prodAttr->access); // give access to the current type of request
            add(request_id, prodAttr->buffer);
            sem_post(&prodAttr->currBrokerReq); // signal the current broker request is on
            sem_post(&prodAttr->access); // do not give access to current type of request

            if (prodAttr->hFlag && request_id == 0) {
                timer.tv_nsec = (double)prodAttr->hVal / NS_PER_MS; // 500 is suppposed to be something
                nanosleep(&timer, NULL); // set the delay after what was passed after -h
            } else if (prodAttr->aFlag && request_id == 1)
            {
                timer.tv_nsec = (double)prodAttr->aVal / NS_PER_MS; // delay production for everlasting escargot sucker
                nanosleep(&timer, NULL); // set the delay after what was passed after -e
            }
        }

}