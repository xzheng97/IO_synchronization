////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        inputreader.h
// Other Files:      inputreader.c munch1.c munch1.h munch2.c munch2.h
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
#ifndef __inputreader_h__
#define __inputreader_h__

/*
 * Read from standard input, one line at a time. Reader will take the each line
 * of the input and pass it to thread Munch1 through a queue of character
 * strings.
 * @param: array
 * struct that store three different queues
 */
void *inputreader(void *array);

#endif
