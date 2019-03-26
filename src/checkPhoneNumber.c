/*******createContact.c********
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 26th, 2019
******************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/contactList.h"

int checkPhoneNumber(char *phoneNumber)
{
    /*Variable is set to a 0 if phone number is determined to be bad*/
    int pNBad = 1;

    /*Counting variable*/
    int i;

    /*Check to see if all of the characters in the phone number string are numbers*/
    for (i = 0; i < strlen(phoneNumber); ++i)
    {
        if (isdigit(phoneNumber[i]) == 0)
            pNBad = 0;
    }

    /*Checks to see if the phone number is the right number of characters, 7 or 10 digits*/
    if (strlen(phoneNumber) != 7 && strlen(phoneNumber) != 10)
        pNBad = 0;

    return pNBad;
}