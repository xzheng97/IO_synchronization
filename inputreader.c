////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        inputreader.c
// Other Files:      inputreader.h munch1.c munch1.h munch2.c munch2.h
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

#include "Queue.h"
#include "inputreader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define buffersize 1024
#define qsize 10

/*
 * Read from standard input, one line at a time. Reader will take the each line
 * of the input and pass it to thread Munch1 through a queue of character
 * strings.
 * @param: array
 * struct that store three different queues
 */
void *inputreader(void *array) {
    // get the reader queue from queuelist
    Queue *qreader = ((queuelist *)array)->qreader;
    int c = 0;
    int index = 0;
    // allocate memory to each string
    char *str = calloc(buffersize,sizeof(char));
    if(!str) {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    // traverse all characters from stdin until reach EOF
    while((c = fgetc(stdin)) != EOF){
        // case when string length is greater than buffersize
        if(index >= buffersize) {
            // read the string and flush it
            if(c != '\n') {
                continue;
            }
            // reset index
            index = 0;
            fprintf(stderr, "This string line is too long\n");
        }
        // normal case
        else {
            // when a string reaches end
            if(c == '\n') {
                // attach end of string character
                str[index] = '\0';
                // add the string to queue
                EnqueueString(qreader, str);
                // reset index
                index = 0;
                // allocate str with new memory
                str = calloc(buffersize, sizeof(char));
                if(!str) {
                    fprintf(stderr, "Error allocating memory\n");
                    exit(1);
                }
            }
            else{
                // fill sring with characters
                str[index] = c;
                index++;
            }
        }
    }
    // case when there are characters before EOF
    if( index !=0 ) {
        // attach end of string character
        str[index] = '\0';
        // add the string to queue
        EnqueueString(qreader, str);
    }
    // add NULL to queue as a sign of there will be no more input
    EnqueueString(qreader, NULL);
    pthread_exit(NULL);
}
