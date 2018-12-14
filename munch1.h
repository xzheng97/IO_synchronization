////////////////////////////////////////////////////////////////////////////////
// Main File:        main.c
// This File:        munch1.h
// Other Files:      inputreader.c inputreader.h munch1.c munch2.c munch2.h
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
#ifndef __munch1_h__
#define __munch1_h__


/*
 * Scan the line and replace each space character (not tabs or newlines) with
 * an asterisk ("*") character. It will then pass the line to thread Munch2
 * through another queue of character strings.
 *
 * @param: array
 * struct that store three different queues
 */
void *munch1(void *array);

#endif
