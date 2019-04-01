CC=gcc
CFLAGS=-Wall -ansi -g

contactList: main.o checkEmail.o checkPhoneNumber.o createContact.o openFile.o retrieveContact.o readDataToMemory.o sortContacts.o getNameFirstLetter.o
	$(CC) $(CFLAGS) -o bin/contactList bin/main.o bin/checkEmail.o bin/checkPhoneNumber.o bin/createContact.o bin/openFile.o bin/retrieveContact.o bin/readDataToMemory.o bin/sortContacts.o bin/getNameFirstLetter.o

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

retrieveContact.o: src/retrieveContact.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/retrieveContact.c -o bin/retrieveContact.o

readDataToMemory.o: src/readDataToMemory.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/readDataToMemory.c -o bin/readDataToMemory.o

sortContacts.o: src/sortContacts.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/sortContacts.c -o bin/sortContacts.o

getNameFirstLetter.o: src/getNameFirstLetter.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/getNameFirstLetter.c -o bin/getNameFirstLetter.o

test: testMain.o checkEmail.o checkPhoneNumber.o createContact.o openFile.o retrieveContact.o readDataToMemory.o sortContacts.o getNameFirstLetter.o
	$(CC) $(CFLAGS) -o bin/test bin/testMain.o bin/checkEmail.o bin/checkPhoneNumber.o bin/createContact.o bin/openFile.o bin/retrieveContact.o

testMain.o: src/testMain.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/testMain.c -o bin/testMain.o

clean:
	rm bin/main.o bin/checkEmail.o bin/checkPhoneNumber.o bin/createContact.o bin/openFile.o bin/retrieveContact.o bin/contactList bin/testMain.o bin/test
