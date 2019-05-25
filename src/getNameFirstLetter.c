/*****getNameFirstLetter.c*****
Author: Ryan Simmons
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/contactList.h"

char getNameFirstLetter(struct contactData contact)
{
    /*string for storing name*/
    char str[1000];

    /*character for storing the first letter of the string*/
    char firstLetter;

    /*Check to see if contact has a last name, and assign a value to str accordingly*/
    if (strcmp(contact.last_name, "") == 0)
    {
        strcpy(str, contact.company_name);
    }
    else
    {
        strcpy(str, contact.last_name);
    }

    /*Get the first letter from the string*/
    firstLetter = toupper(str[0]);

    /*Return first letter*/
    return firstLetter;
}
