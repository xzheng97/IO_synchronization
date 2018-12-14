////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        munch2.h
// Other Files:      inputreader.c inputreader.h munch1.c munch1.h munch2.c
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
#ifndef __munch2_h__
#define __munch2_h__

/*
 * Scan the line and convert all lower case letters to upper case (e.g.,convert
 * "a" to "A"). It will then pass the line to thread Writer though yet another
 * queue of character strings.
 *
 * @param: array
 * struct that store three different queues
 */
void *munch2(void *array) ;

#endif
