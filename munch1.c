////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        munch1.c
// Other Files:      inputreader.c inputreader.h munch1.h munch2.c munch2.h
//                   outputwriter.c outputwriter.h Queue.c Queue.h
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
#include <strings.h>
#include <stdlib.h>
#include <pthread.h>
#include "Queue.h"
#include "munch1.h"
#define buffersize 1024
#define qsize 10

/*
 * Scan the line and replace each space character (not tabs or newlines) with
 * an asterisk ("*") character. It will then pass the line to thread Munch2
 * through another queue of character strings.
 * @param: array
 * struct that store three different queues
 */
void *munch1(void *array) {
    // get queues from queuelist
    Queue *qreader = ((queuelist*)array)->qreader;
    Queue *qmunch1 = ((queuelist*)array)->qmunch1;
    
    char *str;
    // traverse all strings in the reader queue
    while((str = DequeueString(qreader)) != NULL) {
        // change every space character to star
        while(index(str, ' ') != NULL) {
            *index(str, ' ') = '*';
        }
        // add changed strings to next queue
        EnqueueString(qmunch1, str);
    }
    // add NULL to queue as a sign of there will be no more input
    EnqueueString(qmunch1, NULL);
    pthread_exit(NULL);
    
}
