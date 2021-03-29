////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c, sendsig.c, division.c
// This File:        sendsig.c
// Other Files:      None.
// Semester:         CS 354 Fall 2020
//
// Author:           Weihang Guo
// Email:            wguo63@wisc.edu
// CS Login:         weihang 
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None.
//
// Online sources:   None.
//
////////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

/* 
 * main function that contains a infinite loop
 */
int main(int argc, char** argv) {

    //check argc for correct number
    if (argc !=3) {
        printf("Usage: <signal type> <pid>\n");
        exit(0);
    }
    //case1: -i -> SIGINT
    if (strcmp(argv[1], "-i") == 0) {
        //check kill return type
        if (kill(atoi(argv[2]), SIGINT) == -1) {
            printf("Error sending the signal.\n");
            exit(0);
        } 

    //case2: -u -> SIGUSR1
    } else if (strcmp(argv[1], "-u") == 0) {
        //check kill return type
        if (kill(atoi(argv[2]), SIGUSR1) == -1) {
            printf("Error sending the signal.\n");
            exit(0);
        }

    } else {
    //case3: invalid input -> exit
        printf("Invalid input.\n");
        exit(0);
    }
   
    return 0;

}