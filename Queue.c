////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        Queue.c
// Other Files:      inputreader.c inputreader.h munch1.c munch1.h munch2.c
//                   munch2.h outputwriter.c outputwriter.h Queue.h
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
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

int ModIncr(int v) {
    return (v+1) % 10; //TODO
}

/*
 * Dynamically allocate a new Queue structure and initialize it with an array of
 * character points of length size.
 * The function returns a pointer to the new queue structure.
 *
 * @param size : size of the queue
 */
Queue *CreateStringQueue(int size){
    // edge case when size is negative
    if (size <= 0) {
        fprintf(stderr, "Wrong size!" );
        exit(-1);
    }
    // create a queue struct
    struct Queue *q = (Queue *)calloc(1, sizeof(Queue));
    if(!q) {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    // allocate memory to the queue
    q->array = malloc(size*sizeof(char*));
    if(!q->array) {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    q->qsize = size;
    q->enqcount = 0;
    q->deqcount = 0;
    q->enqblcount = 0;
    q->deqblcount = 0;
    q->front = 0;
    q->end = 0;
    pthread_cond_init(&(q->full),NULL);
    pthread_cond_init(&(q->empty),NULL);
    pthread_mutex_init(&(q->mutex), NULL);
    return q;
}

/*
 * This function places the pointer to the string at the end of queue q.
 * If the queue is full, then this function blocks until there is space
 * available.
 * @param q : A queue that stores strings
 * string : a ptr stores a string
 */
void EnqueueString(Queue *q, char *string) {
    // use mutex to realize mutual exclusion
    if(pthread_mutex_lock(&(q->mutex)))
        fprintf(stderr, "error locking mutex");
    // when the queue is full, block
    while (ModIncr(q->end) == q->front){
        q->enqblcount++;
        if(pthread_cond_wait(&(q->full), &(q->mutex)))
            fprintf(stderr, "error waiting condition variable");
    }
    // add string
    *(q->array + q->end) = string;
    if (string != NULL) {
        q->enqcount++;
    }
    
    q->end = ModIncr(q->end);
    // signal that there's at least one string in queue
    if(pthread_cond_signal(&(q->empty)))
        fprintf(stderr, "error signaling condition variable");
    if(pthread_mutex_unlock(&(q->mutex)))
        fprintf(stderr, "error locking mutex");
}

/*
 * This function removes a pointer to a string from the beginning of queue q.
 * If the queue is empty, then this function blocks until there is a string
 * placed into the queue.
 * Returns the pointer that was removed from the queue.
 *
 * @param q
 * A queue that stores strings
 */
char * DequeueString(Queue *q) {
    // use mutex to realize mutual exclusion
    if(pthread_mutex_lock(&(q->mutex)))
        fprintf(stderr, "error locking mutex");
    // when the queue is empty, block
    while(q->front == q->end) {
        q->deqblcount++;
        if(pthread_cond_wait(&(q->empty), &(q->mutex)))
            fprintf(stderr, "error waiting condition variable");
    }
    // remove string
    char *result = *(q->array + q->front);
    q->front = ModIncr(q->front);
    
    if(result != NULL) {
        q->deqcount++;
    }
    // signal that string can be added to the queue
    if(pthread_cond_signal(&(q->full)))
        fprintf(stderr, "error signaling condition variable");
    if(pthread_mutex_unlock(&(q->mutex)))
        fprintf(stderr, "error unlocking mutex");
    return result;
}

/*
 * This function prints the statistics for this queue.
 *
 * @param q
 * A queue that stores strings
 */
void PrintQueueStats(Queue *q) {
    fprintf(stderr, "Number of strings enqueued: %d\n", q->enqcount);
    fprintf(stderr, "Number of strings dequeued: %d\n", q->deqcount);
    fprintf(stderr, "Number of times that an enqueue was blocked: %d\n", q->enqblcount);
    fprintf(stderr, "Number of times that a dequeue was blocked: %d\n", q->deqblcount);
}

/*
 * This function frees all the memory that a que has allocated
 *
 * @param q
 * A queue that stores strings
 */
void DestoryQueue(Queue *q) {
    free(q->array);
    q->array = NULL;
    free(q);
    q = NULL;
}


