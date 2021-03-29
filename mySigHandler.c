////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c, sendsig.c, division.c
// This File:        mySigHandler.c
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

int counter = 0;//counts the number of SIGUSR1 caught

/* 
 * SIGALRM handler that prints pid and time information every 3 seconds.
 */
void handler_SIGALRM() {

    //obtain the current time
    time_t current;
    time(&current);
    //check time and ctime return value
    if (current == -1 || ctime(&current) == NULL) {
        printf("error getting the current time.\n");
        exit(0);
    }
    printf("PID: %d CURRENT TIME: %s", getpid(), ctime(&current));
    alarm(3);

}

/* 
 * SIGINT handler that prints information after ^C.
 */
void handler_SIGINT() {

    printf("SIGINT handled.\n");
    printf("SIGUSR1 was handled %d times. Exiting now.\n", counter);
    exit(0);

}

/* 
 * SIGUSR1 handler that prints information when catching SIGUSR1.
 */
void handler_SIGUSR1() {

    counter ++;
    printf("SIGUSR1 handled and counted!\n");

}


/* 
 * main function that contains a infinite loop
 */
int main() {

    //prompt the user
    printf("Pid and time print every 3 seconds.\n");
    printf("Enter Ctrl-C to end the program.\n");
    
    //set alarm
    alarm(3);

    //initialize sigalrm
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));//set flags to 0
    sa.sa_handler = handler_SIGALRM;
    //check return type
    if (sigaction(SIGALRM, &sa, NULL) != 0) {
        printf("Error binding SIGALRM handler.\n");
        exit(1);
    }

    //initialize sigusr1
    struct sigaction su;
    memset(&su, 0, sizeof(su));//set flags to 0
    su.sa_handler = &handler_SIGUSR1;
    //check return type
    if (sigaction(SIGUSR1, &su, NULL) != 0) {
        printf("Error binding SIGUSR1 handler.\n");
        exit(1);
    }

    //initialize sigint
    struct sigaction si;
    memset(&si, 0, sizeof(si));//set flags to 0
    si.sa_handler = &handler_SIGINT;
    //check return type
    if (sigaction(SIGINT, &si, NULL) != 0) {
        printf("Error binding SIGINT handler.\n");
        exit(1);
    }

    //infinite loop
    while(1) {}
    return 0;

}

