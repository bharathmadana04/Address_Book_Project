/*
Name : Madana Bharath
Date : 18/08/2025
Title : Address Book
*/
#include <stdio.h>
#include "contact.h"
#include "file.h"
int main() {
    int choice,sortChoice;
    AddressBook addressBook;//memory is allocated
    //initialize(&addressBook); // Initialize the address book
    loadContactsFromFile(&addressBook);
    do {
        printf("\033[1;38m\n----------Address Book Menu----------\033[0m\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
