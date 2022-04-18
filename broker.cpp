/*
Drake Nguyen + Jacob Le
Drake: 83197720 cssc1437
Jacob: 822652578 cssc1431
CS480-03
9 April 2022
Assignment 4
*/

#include "broker.h"
#include "io.h"
#include "ridesharing.h"
#include <stdio.h>

using namespace std;

// parameters
int currHumans, currRobots;                     // holds current human and robot drivers
int totalHumans, totalRobots;                   // holds total amount of humans and robots drivers
int totalDrivers;                               // holds total drivers
int humanCost, humanFast;                       // holds how much the cost/fast algorithm has consumed of human drivers
int robotCost, robotFast;                       // holds how much the cost/fast algorithm has consumed of robot drivers
int currBrokerAmount[REQUEST_TYPES];                        // holds what request type is currently on broker
int produced[PRODUCERS], consumed[CONSUMERS];   // arrays that will hold how many requests are produced and consumed 
int cost_consumed[REQUEST_TYPES], fast_consumed[REQUEST_TYPES];         // arrays that will hold how many costAlgo and fastAlgo consumed
RequestType req_type;
ConsumerType consume_type;

// constructor for Requests
REQUEST::REQUEST(int id)
{
    request_id = id;
    name = request_id ? "Human" : "Robot";
    // if item_id is 0, then return Human, else return Robot
}


void add(int request_id, queue<REQUEST*> *broker) {

    REQUEST *newRequest = new REQUEST(request_id);          // create a new request to be added into the broker queue
    broker -> push(newRequest);                             // push that new request into the queue
    req_type = request_id ? HumanDriver : RoboDriver;       // assign req_type to be either human or robot
    currBrokerAmount[req_type] += 1;                        // increment the type of driver by 1
    produced[req_type] += 1;                                // increment the total request by 1
    io_add_type(req_type, currBrokerAmount, produced);      // print it out!

}

int remove(string consumer, queue<REQUEST*> *broker) {

    REQUEST *newRequest = broker -> front();                // new request will get the first request from the broker queue
    int request_id = newRequest -> request_id;              // store the request id into an int variable
    broker -> pop();                                        // remove the request from the queue
    consume_type = consumer.compare("CostAlgoDispatch")     // cost algo is 0, fast algo is 1
        == 0 ? CostAlgoDispatch : FastAlgoDispatch;
    req_type = request_id ? HumanDriver : RoboDriver;       // human is 0, robot is 1
    currBrokerAmount[req_type] -= 1;                        // remove by 1 what is currently on the broker array

    if (consume_type == CostAlgoDispatch) {
        cost_consumed[req_type] += 1;                       // cost algorithm consumes a request
        io_remove_type(CostAlgoDispatch, req_type, currBrokerAmount, cost_consumed);  // print it out!
    } else if (consume_type == FastAlgoDispatch) {
        fast_consumed[req_type] += 1;                       // fast algorithm consumes a request
        io_remove_type(FastAlgoDispatch, req_type, currBrokerAmount, fast_consumed);  // print it out!
    }

    return request_id;                                      // now return the request we removed

}
int *getCostDispatch() { return cost_consumed; }
int *getFastDispatch() { return fast_consumed; }
int *getProduced() { return produced; }