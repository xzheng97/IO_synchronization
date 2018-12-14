////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        Queue.h
// Other Files:      inputreader.c inputreader.h munch1.c munch1.h munch2.c
//                   munch2.h outputwriter.c outputwriter.h Queue.c
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

#ifndef __Queue_h__
#define __Queue_h__
#include <pthread.h>

typedef struct Queue{
    char **array;
    int qsize;
    int enqcount;
    int deqcount;
    int enqblcount;
    int deqblcount;
    int front; //not sure
    int end;
    pthread_cond_t full;
    pthread_cond_t empty;
    pthread_mutex_t mutex;
}Queue;

typedef struct queuelist {
    Queue *qreader;
    Queue *qmunch1;
    Queue *qmunch2;
}queuelist;

/*
 * Dynamically allocate a new Queue structure and initialize it with an array of
 * character points of length size.
 * The function returns a pointer to the new queue structure.
 *
 * @param size : size of the queue
 */
Queue *CreateStringQueue(int qsize);

/*
 * This function places the pointer to the string at the end of queue q.
 * If the queue is full, then this function blocks until there is space
 * available.
 * @param q : A queue that stores strings
 *        string : a ptr stores a string
 */
void EnqueueString(Queue *q, char *string);

/*
 * This function removes a pointer to a string from the beginning of queue q.
 * If the queue is empty, then this function blocks until there is a string
 * placed into the queue.
 * Returns the pointer that was removed from the queue.
 *
 * @param q
 * A queue that stores strings
 */
char * DequeueString(Queue *q);

/*
 * This function prints the statistics for this queue.
 *
 * @param q
 * A queue that stores strings
 */
void PrintQueueStats(Queue *q);

/*
 * This function frees all the memory that a que has allocated
 *
 * @param q
 * A queue that stores strings
 */
void DestoryQueue(Queue *q);


#endif


