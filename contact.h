#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
//void saveAndExit(AddressBook *addressBook) ;
//void initialize(AddressBook *addressBook);
//void saveContactsToFile(AddressBook *AddressBook);
int namevalidate(char *str);
int mobilevalidate(char *str,AddressBook *addressBook);
int mailvalidate(char *str,AddressBook *addressBook);
void search_by_mail(char *str, AddressBook *addressBook);
void search_by_phone(char *str, AddressBook *addressBook) ;
void search_by_name(char *str, AddressBook *addressBook) ;
void edit(int index, AddressBook *addressBook) ;
int edit_by_mail(char *str, AddressBook *addressBook);
int edit_by_phone(char *str, AddressBook *addressBook) ;
int edit_by_name(char *str, AddressBook *addressBook) ;
void deleteContactByIndex(AddressBook *addressBook, int index) ;
int mobilevalidate_search(char *str);
int mailvalidate_search(char *str);
int mobilevalidate_edit(char *str, AddressBook *addressBook, int index);
int mailvalidate_edit(char *str, AddressBook *addressBook, int index);
//void loadContactsFromFile(AddressBook *addressBook);
#endif