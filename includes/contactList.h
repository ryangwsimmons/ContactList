/*********contactList.h*******
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 9th, 2019
*****************************/
/*Includes necessary for function prototypes*/
#include <stdio.h>

/*Header file for assignment 3 structure and function prototypes*/

struct contact {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};

/************************************************
openFile: opens a file
IN: None
OUT: The file pointer pointing to the file opened
POST: If file cannot be opened, prints an error
************************************************/
FILE *openFile();

/************************************************************
createContact: creates a contact
IN: FILE *filePtr
OUT: None
POST: Prompting the user for the various values of the struct
************************************************************/
void createContact(FILE *filePtr);

/******************************************************************************
retrieveContact: retrieves a contact from the database
IN: unsigned long phoneNumber, struct contact *database
OUT: None
POST: Prompting the user to enter a phone number, the contact requested
******************************************************************************/
void retrieveContact(FILE *filePtr);