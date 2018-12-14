////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        outputwriter.c
// Other Files:      inputreader.c inputreader.h munch1.c munch1.h munch2.c
//                   munch2.h outputwriter.h Queue.c Queue.h
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "Queue.h"
#include "outputwriter.h"
#define buffersize 1024
#define qsize 10

/*
 * Write the line to standard output.
 *
 * @param: array
 * struct that store three different queues
 */
void *outputwriter(void *array) {
    // get munch2 queue from queuelist
    Queue *qmunch2 = ((queuelist *)array)->qmunch2;
    char *str;
    // count how many strings are processed
    int counter = 0;
    // traverse all strings in the munch1 queue
    while( (str = DequeueString(qmunch2)) != NULL) {
        fprintf(stdout, "%s\n", str);
        counter++;
        free(str); 
    }
    free(str);
    str = NULL;
    fprintf(stdout, "Number of strings processed: %d\n", counter);
    pthread_exit(NULL);
}
