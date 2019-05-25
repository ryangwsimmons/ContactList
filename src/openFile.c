/*********openFile.c***********
Author: Ryan Simmons
Last Modified: March 13th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include "../includes/contactList.h"

FILE *openFile()
{
    FILE *filePtr;

    filePtr = fopen("myContactList.db", "ab+");
    if (filePtr == NULL)
    {
        printf("Error: file could not be opened or created\n");
        exit(-1);
    }

    return filePtr;
}
