////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c, sendsig.c, division.c
// This File:        division.c
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

int counter = 0;//counts the number of succesful divisions

/* 
 * SIGINT handler that prints information after ^C
 */
void handler_SIGINT() {

    printf("\nTotal number of operations completed successfully: %d\n", counter);
    printf("The program will be terminated.\n");
    exit(0);

}

/* 
 * SIGFPE handler that prints information after a division by 0
 */
void handler_SIGFPE() {

    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", counter);
    printf("The program will be terminated.\n");
    exit(0);

}

/* 
 * main function
 */
int main() {

    //initialize sigfpe
    struct sigaction sfpe;
    memset(&sfpe, 0, sizeof(sfpe));//set flags to 0
    sfpe.sa_handler = handler_SIGFPE;
    //check return type
    if (sigaction(SIGFPE, &sfpe, NULL) != 0) {
        printf("Error binding SIGFPE handler.\n");
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

    while(1) {

        //prompt the user
        //get the first integer
        printf("Enter first integer:");
        char buffer[100];
        if (fgets(buffer, 100, stdin) == NULL) {
            //check the fgets return type
            printf("Error getting the input.\n");
            exit(0);
        }
        int integer1 = atoi(buffer);

        //get the second integer
        printf("Enter second integer:");
        if (fgets(buffer, 100, stdin) == NULL) {
            //check the fgets return type
            printf("Error getting the input.\n");
            exit(0);
        }
        int integer2 = atoi(buffer);

        int quotient = integer1 / integer2;
        int remainder = integer1 % integer2;
        printf("%d / %d is %d with a remainder of %d\n", integer1, integer2, quotient, remainder);
        counter ++;

    }

    return 0;
}
