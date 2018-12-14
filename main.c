////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        main.c
// Other Files:      inputreader.c inputreader.h munch1.c munch1.h munch2.c
//                   munch2.h outputwriter.c outputwriter.h Queue.c Queue.h
// Semester:         CS 537 Fall 2018
//
// Author:           Youmin Han
// Email:            youmin.han@wisc.edu
// CS Login:         youmin
//
// Author:           Xianjie Zheng
// Email:            xzheng97@wisc.edu
// CS Login:         xianjie
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NULL
//
// Online sources:   NULL
//
//////////////////////////// 80 columns wide ///////////////////////////////////


#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Queue.h"
#include "munch1.h"
#include "munch2.h"
#include "outputwriter.h"
#include "inputreader.h"

const int qsize = 10;
/*
 * This program will read strings from input and call different threads, each does
 * distinct jobs to the strings, and then output those strings and print out any
 * errors occured.
 *
 */
int main() {
    // create three queue structs
    Queue *qreader = CreateStringQueue(qsize);
    Queue *qmunch1 = CreateStringQueue(qsize);
    Queue *qmunch2 = CreateStringQueue(qsize);
    // create a structure that stores three queues
    queuelist array;
    array.qreader = qreader;
    array.qmunch1 = qmunch1;
    array.qmunch2 = qmunch2;
    // create four threads
    pthread_t rthread;
    pthread_t m1thread;
    pthread_t m2thread;
    pthread_t wthread;
    
    // initialize four threads
    if(pthread_create(&rthread, NULL, inputreader, &array)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    if(pthread_create(&m1thread, NULL, munch1, &array)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    if(pthread_create(&m2thread, NULL, munch2, &array)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    if(pthread_create(&wthread, NULL, outputwriter, &array)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    // wait for all threads to complete
    if(pthread_join(rthread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    
    if(pthread_join(m1thread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    
    if(pthread_join(m2thread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    
    if(pthread_join(wthread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    
    // print out statistics from three queues
    fprintf(stderr, "Statistics of reader queue\n");
    PrintQueueStats(array.qreader);
    fprintf(stderr, "Statistics of munch1 queue\n");
    PrintQueueStats(array.qmunch1);
    fprintf(stderr, "Statistics of munch2 queue\n");
    PrintQueueStats(array.qmunch2);
    // free queues' memory
    DestoryQueue(array.qreader);
    DestoryQueue(array.qmunch1);
    DestoryQueue(array.qmunch2);
    
    
    
    return(0);
}
