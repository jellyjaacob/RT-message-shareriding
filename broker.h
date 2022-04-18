/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#ifndef BROKER_H
#define BROKER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>

#define PRODUCERS 2
#define CONSUMERS 2
#define REQUEST_TYPES 2

/*
Each time the broker request queue is mutated (addition or removal), a message should be
printed indicating which thread performed the action and the current state, i.e., descriptive
output should be produced each time right after a request is added to or removed from the
broker request queue. 
    a. Functions in io.c will let you produce output in a standard manner. Use
    io_add_type and io_remove_type to print messages. When the request production
    is complete, you should print out how many of each type of request was produced
    and how many of each type were processed by each of the consumer threads, use
    io_production_report. 
*/

using namespace std;

//requests hold our consumer and producer requests and the type of consumer or producer request they are
class REQUEST {
    public:
        REQUEST(int id);
        int request_id;
        string name;
};

void add(int request_id, queue<REQUEST*> *broker);      // adds requests into the broker queue
int remove(string consumer, queue<REQUEST*> *broker);   // removes requests from the broker queue
int *getCostDispatch();                                 // returns how many cost algorithms were dispatched
int *getFastDispatch();                                 // returns how many fast algorithms were dispatched
int *getProduced();                                     // returns how many requests were produced
#endif
