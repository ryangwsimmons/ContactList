CC=gcc
CFLAGS=-Wall -ansi

contactList: main.o checkEmail.o checkPhoneNumber.o createContact.o openFile.o readDataToMemory.o sortContacts.o getNameFirstLetter.o editContact.o deleteContact.o
	$(CC) $(CFLAGS) -o bin/contactList bin/main.o bin/checkEmail.o bin/checkPhoneNumber.o bin/createContact.o bin/openFile.o bin/readDataToMemory.o bin/sortContacts.o bin/getNameFirstLetter.o bin/editContact.o bin/deleteContact.o

main.o: src/main.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

checkEmail.o: src/checkEmail.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/checkEmail.c -o bin/checkEmail.o

checkPhoneNumber.o: src/checkPhoneNumber.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/checkPhoneNumber.c -o bin/checkPhoneNumber.o

createContact.o: src/createContact.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/createContact.c -o bin/createContact.o

openFile.o: src/openFile.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/openFile.c -o bin/openFile.o

readDataToMemory.o: src/readDataToMemory.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/readDataToMemory.c -o bin/readDataToMemory.o

sortContacts.o: src/sortContacts.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/sortContacts.c -o bin/sortContacts.o

getNameFirstLetter.o: src/getNameFirstLetter.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/getNameFirstLetter.c -o bin/getNameFirstLetter.o

editContact.o: src/editContact.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/editContact.c -o bin/editContact.o

deleteContact.o: src/deleteContact.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/deleteContact.c -o bin/deleteContact.o

clean:
	rm bin/main.o bin/checkEmail.o bin/checkPhoneNumber.o bin/createContact.o bin/openFile.o bin/readDataToMemory.o bin/sortContacts.o bin/getNameFirstLetter.o bin/editContact.o bin/deleteContact.o bin/contactList
