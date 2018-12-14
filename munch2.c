////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        munch2.c
// Other Files:      inputreader.c inputreader.h munch1.c munch1.h munch2.h
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
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include "Queue.h"
#include "munch2.h"
#define buffersize 1024
#define qsize 10

/*
 * Scan the line and convert all lower case letters to upper case (e.g.,convert
 * "a" to "A"). It will then pass the line to thread Writer though yet another
 * queue of character strings.
 *
 * @param: array
 * struct that store three different queues
 */
void *munch2(void *array) {
    // get queues from queuelist
    Queue *qmunch1 = ((queuelist *)array)->qmunch1;
    Queue *qmunch2 = ((queuelist *)array)->qmunch2;
    
    char *str;
    // traverse all strings in the munch1 queue
    while((str = DequeueString(qmunch1)) != NULL) {
        // change every lower-case to upper-case
        for(int i = 0; i < (int)strlen(str); i++) {
            if(islower(str[i])) {
                str[i] = toupper(str[i]);
            }
        }
        // add changed strings to next queue
        EnqueueString(qmunch2, str);
    }
    // add NULL to queue as a sign of there will be no more input
    EnqueueString(qmunch2, NULL);
    
    pthread_exit(NULL);
    
    
}
