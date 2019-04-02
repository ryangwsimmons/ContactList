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

/*Structure for holding contact data, rather than positions; used for sorting contacts*/
struct contactData{
    unsigned long phone_number;
    char *first_name;
    char *last_name;
    char *company_name;
    char *email;
    int delete;
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

/************************************************************************************************
checkPhoneNumber: checks a phone number string to see if it's valid or not
IN: char *phoneNumber
OUT: An integer indicating whether or not the phone number is good (non-zero for good, 0 for bad)
POST: None
************************************************************************************************/
int checkPhoneNumber(char *phoneNumber);

/***********************************************************************************************
checkEmail: checks an email to see if it is valid or not
IN: char *email
OUT: An integer indicating whether or not the email is valid (non-zero for valid, 0 for invalid)
POST: None
***********************************************************************************************/
int checkEmail(char *email);

/***************************************************************************************
readDataToMemory: reads contact data from file into an array of contactData structures
IN: FILE *filePtr, int *numElements
OUT: An array containing contact data
POST: None
***************************************************************************************/
struct contactData *readDataToMemory(FILE *filePtr, int *numElements);

/***************************************
sortContacts: sorts an array of contacts
IN: struct contactData contacts[], int numElements
OUT: None
POST: None
***************************************/
void sortContacts(struct contactData contacts[], int numElements);

/*************************************************************************************
compareContacts: compares the names (either last name or company name) of two contacts
IN: const void *a, const void *b
OUT: less than 0 if a < b, 0 if a == b, greater than 0 if a > b
POST: None
*************************************************************************************/
int compareContacts(const void *a, const void *b);

/**************************************************************************************************************
getNameFirstLetter: Retrieves the first letter of either the last name or company name for the contact provided
IN: struct contactData contact
OUT: A char containing the first letter of the contact's name
POST: None
**************************************************************************************************************/
char getNameFirstLetter(struct contactData contact);

/*****************************************************************************************
editContact: edits an existing contact in the file
IN: struct contactData *contactArray, FILE **filePtrPtr, int contactNumber, int numElements
OUT: None
POST: Prompting users for new contact information
*****************************************************************************************/
void editContact(struct contactData *contactArray, FILE **filePtrPtr, int contactNumber, int numElements);

/**************************************************************************************
deleteContact: deletes a contact from the list
IN: struct contactData *contactArray, FILE **filePtrPtr, int contactNumber, int numElements
OUT: None
POST: None
**************************************************************************************/
void deleteContact(struct contactData *contactArray, FILE **filePtrPtr, int contactNumber, int numElements);