#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
//for making the all contacts in sort order
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    int count = addressBook->contactCount;//storing no.of contacts in addressbook at count
    Contact tempContacts[100];//temparerly storing the addressbook contacts
    for (int i = 0; i < count; i++) {
        tempContacts[i] = addressBook->contacts[i];
    }
    for (int i = 0; i < count - 1; i++) { //comapring first and next name ingnoring the case and storing in temp contacts
        for (int j = i + 1; j < count; j++) {
            if (strcasecmp(tempContacts[i].name, tempContacts[j].name) > 0) {
                Contact temp = tempContacts[i];
                tempContacts[i] = tempContacts[j];
                tempContacts[j] = temp;
            }
        }
    }
    printf(" ...................................................................................\n");
    printf("| %-5s | %-15s | %-20s | %-33s |\n","Sl.No","Name","Mobile Number","Email");
    printf(" ...................................................................................\n");
    for (int i = 0; i < count; i++) {
        printf("| %-5d | %-15s | %-20s | %-33s |\n",
               i + 1,
               tempContacts[i].name,
               tempContacts[i].phone,
               tempContacts[i].email);
    }
    printf(" ...................................................................................\n");
}


void createContact(AddressBook *addressBook)
{
int i=0,count=0;
for(i=0;i<=100;i++)
{    
    char name[100], mobile[100], mail[100];
input_name:
    printf("Enter your name: ");
    scanf(" %[^\n]", name);
    if (!namevalidate(name)) {//validating the name if correct takes next input else again it will ask for name
        printf("........Enter a valid name.........\n");
        goto input_name;
    }
input_mobile:
    printf("Enter your number: ");
    scanf(" %s", mobile);
    if (!mobilevalidate(mobile,addressBook)) {//validating the number if correct takes next input else again it will ask for number
        printf("........Enter a valid 10-digit mobile number.........\nThe number doesn't contain alphabets and special charectres\n");
        goto input_mobile;
    }
input_email:
    printf("Enter your mailid: ");
    scanf(" %s",mail);
    if(!mailvalidate(mail,addressBook))//validating the mail if its not correct again it will ask for mail
    {
        printf("..........Enetr valid email..............\n");
        goto input_email;
    }
strcpy(addressBook->contacts[addressBook->contactCount].name,name);//copying the enterd information into the addressbook
strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile);
strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
addressBook->contactCount++;
count++;
name[0]='\0';
mobile[0]='\0';
mail[0]='\0';
    char ch;
    printf("Do you want to enter another contact? (y/n): ");//after first contact again it ask to enter the use to create one more contact
    scanf(" %c", &ch);
    if (ch == 'n' || ch == 'N')
            break;
}
for(int j=0;j<addressBook->contactCount;j++)
{
    printf("%d. | %s | %s | %s\n",
           j + 1,
           addressBook->contacts[j].name,
           addressBook->contacts[j].phone,
           addressBook->contacts[j].email);
}

}
int namevalidate(char *str)
{
    int i=0;
    while(str[i]!='\0')//validating the name if correct return 1 else else return 0
    {
        if((str[i]>='a' && str[i]<='z')||(str[i]>='A' && str[i]<='Z')||(str[i]==' '||str[i]=='.'))
        {
            i++;
        }
        else
        {
            return 0;
        }
}
 return 1;
}

int mobilevalidate(char *str,AddressBook *addressBook)
{
    int i=0;
    if(str[0]>='a'&&str[0]<='z'||str[0]>='a'&&str[0]<='z')//if my first char is alphabet then it returns 0
        return 0;
    while(str[i]!='\0')//validating the number if correct return 1 else else return 0
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
    }
if(i==10){
for(int j=0;j<addressBook->contactCount;j++)//if the number is correct then compare previous number whether it is already present are not
{
     if (strcmp(addressBook->contacts[j].phone, str) == 0) {
            printf("....This mobile number already exists....\n");
            return 0;
        }
}
    return 1;
}
else 
    return 0;
}

int mailvalidate(char *str,AddressBook *addressBook)
{
    int i=0,found=0,len=strlen(str),pos_com;
    char start=str[i];
    if(start=='@'|| (start>='0' && start<='9'))//first char doesn't start with these chars
        return 0;
    while(str[i]!='\0')
    {
        if((str[i] >='0' && str[i] <='9')||(str[i] >='a' && str[i] <= 'z')||str[i]=='@'||str[i]=='.')
        {
            if(str[i]=='@')   //checking for @
            {
                found=1;
                break;
            }
        }
       i++;
    }
if(found==0)//if @not found
    return 0;
pos_com=len-4;
if(pos_com<i+1)//checking after @ is there four positions are not 
    return 0;
if (strcmp(&str[pos_com], ".com") != 0)//from @ comparing the string with .com directly
        return 0;
 for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (strcmp(addressBook->contacts[j].email, str) == 0)
        {
            printf("....This email already exists....\n");
            return 0;
        }           
}
  return 1; 
}
void searchContact(AddressBook *addressBook) 
{
    char op;
    int index = -1; // to store search result

    printf("Enter your choice to search the contact:\n");
    printf("1. Name\n2. Mobile\n3. Email\n");
    scanf(" %c", &op); // space before %c to skip newline

    switch(op)
    {
        case '1':
        {
            char str[50];
            do {
                printf("Enter name to search: ");
                scanf(" %[^\n]", str);
                if (!namevalidate(str)) {
                    printf("Invalid name format. Try again.\n");
                } else {
                    break;
                }
            } while (1);

            search_by_name(str, addressBook);
            break;
        }

        case '2':
        {
            char str1[20];
            do {
                printf("Enter Mobile number to search: ");
                scanf(" %[^\n]", str1);
                if (!mobilevalidate_search(str1)) { // use search-specific validation
                    printf("Invalid phone number format. Try again.\n");
                } else {
                    break;
                }
            } while (1);

            search_by_phone(str1, addressBook);
            break;   
        }

        case '3':
        {
            char str2[50];
            do {
                printf("Enter email to search: ");
                scanf(" %[^\n]", str2);
                if (!mailvalidate_search(str2))  {
                    printf("Invalid email format. Try again.\n");
                } else {
                    break;
                }
            } while (1);

            search_by_mail(str2, addressBook);
            break;     
        }

        default:
            printf("Invalid option. Returning to main menu.\n");
            return;
    }
}


void search_by_name(char *str, AddressBook *addressBook) {
    int matches[100];//creating a temp array to store the match contact
    int matchCount = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {//comapring with the previous names with given name if present store in matchs array
        if (strcasecmp(addressBook->contacts[i].name, str) == 0) {
            matches[matchCount++] = i;
        }
    }

    if (matchCount == 0) {//if match count is 0 no contact found
        printf("No contact found with that name.\n");
        return;
    }
    else if (matchCount == 1) {//if match count is 1 there is one match contact
        int idx = matches[0];
        printf("Found: %s | %s | %s\n",
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone,
               addressBook->contacts[idx].email);
    }
    else {
        printf("\nMultiple contacts found:\n");//more than one contact is matched
        for (int i = 0; i < matchCount; i++) {
            int idx = matches[i];
            printf("%d. %s | %s | %s\n", i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        int choice;//again asking the user to enter the index value to search the contact
        printf("Enter index number to search: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > matchCount) {
        printf("Invalid choice.\n");
        return;
        }
        int idx = matches[choice - 1];//for diaplaying the match contact
        printf("%s | %s | %s\n",
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone,
               addressBook->contacts[idx].email);
    }
}

void search_by_phone(char *str, AddressBook *addressBook) {
    for (int i = 0; i < addressBook->contactCount; i++) {//comapring the present string with previous strings that are present are not
        if (strcmp(addressBook->contacts[i].phone, str) == 0) {
            printf("%s | %s | %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return;
        }
    }
    printf("No contact found with that phone number.\n");
}

void search_by_mail(char *str, AddressBook *addressBook) {
    int found = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasecmp(addressBook->contacts[i].email, str) == 0) {
            printf("Found: %s | %s | %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No contact found with that email.\n");
}
// Only validate format for search (does NOT check duplicates)
int mobilevalidate_search(char *str)
{
    int i = 0;
    if (str[0] < '0' || str[0] > '9') // first character must be digit
        return 0;

    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }

    return (i == 10); // must be exactly 10 digits
}
// Validate email format for search (does NOT check duplicates)
int mailvalidate_search(char *str)
{
    int i = 0, found_at = 0;
    int len = strlen(str);

    if (len < 5) // minimum length for a@b.com
        return 0;

    if (str[0] == '@' || (str[0] >= '0' && str[0] <= '9'))
        return 0;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!((c >= '0' && c <= '9') || 
              (c >= 'a' && c <= 'z') || 
              (c >= 'A' && c <= 'Z') || 
              c == '@' || c == '.' || c == '_' || c == '-'))
            return 0;

        if (c == '@')
            found_at = 1;
    }

    if (!found_at)
        return 0;

    // Ensure email ends with ".com" (case-insensitive)
    if (strcasecmp(&str[len - 4], ".com") != 0)
        return 0;

    return 1; // valid format
}

void editContact(AddressBook *addressBook)
{
	char op;
    int index=-1;//buz in array 0 is a valid index
    printf("1.Name\n2.Number\n3.Email\n");
    scanf(" %c",&op);
    switch (op)
    {
        case '1':
        {
            char str[50];
            do {
                printf("Enter name to edit: \n");
                scanf(" %[^\n]", str); 
                if (!namevalidate(str)) {
                    printf("Invalid name format. Try again.\n");
                } else {
                    break;
                }
            } while (1); // repeat until valid

            index = edit_by_name(str, addressBook);//checking given string is present are not if present it return index vlaue
            break;
        }

        case '2': {
    char str2[20];
    do {
        printf("Enter number to edit: ");
        scanf(" %s", str2);
        if (!mobilevalidate_search(str2)) { // ONLY format check
            printf("Invalid phone number format. Try again.\n");
        } else {
            break;
        }
    } while (1);

    index = edit_by_phone(str2, addressBook); // now we locate the contact
    break;
}


        case '3':
        {
            char str3[50];
            do {
                printf("Enter Email to edit: \n");
                scanf(" %s", str3);
               if (mailvalidate_edit(str3, addressBook, index)) {
                    printf("Invalid email format. Try again.\n");
                } else {
                    break;
                }
            } while (1);

            index = edit_by_mail(str3, addressBook);//checking given string is present are not if present it return index vlaue
            break;
        }

        default:
            printf("Invalid option.\n");
            return;
    }

    if (index != -1)//if index not equal to -1 means there a presence of contact
    {
        edit(index, addressBook);
    }
    else //if index is -1 then there is no contact
    {
        printf("Contact not found.\n");
    }
}

void edit(int index, AddressBook *addressBook) {
    char choice;
    char input[100];//for copying the string that is present in the addresbook of the provided index into the input array

    printf("What do you want to edit?\n1.Name\n2.Mobile\n3.Email\n");
    scanf(" %c", &choice);  // Space before %c is important to consume newline

    switch(choice) {
        case '1':
            while (1) {
                printf("Enter new name: ");
                scanf(" %[^\n]", input);
                if (namevalidate(input)) {
                    strcpy(addressBook->contacts[index].name, input);//copying the strings that are presnt at that index
                    break;
                } else {
                    printf("Invalid name format. Please try again.\n");
                }
            }
            break;

       case '2':
    while (1) {
        printf("Enter new mobile number: ");
        scanf(" %s", input);
        if (mobilevalidate_edit(input, addressBook, index)) { // format + duplicates
            strcpy(addressBook->contacts[index].phone, input);
            break;
        } else {
            printf("Invalid or duplicate mobile number. Please try again.\n");
        }
    }
    break;
        case '3':
            while (1) {
                printf("Enter new email: ");
                scanf(" %s", input);
                if (mailvalidate_edit(input, addressBook, index)){
                    strcpy(addressBook->contacts[index].email, input);//copying the strings that are presnt at that index
                    break;
                } else {
                    printf("Invalid email format. Please try again.\n");
                }
            }
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("Contact updated successfully.\n");
}

int edit_by_name(char *str, AddressBook *addressBook) {
    int matches[100];
    int matchCount = 0;

    // Collect all matching contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasecmp(addressBook->contacts[i].name, str) == 0) {
            matches[matchCount++] = i;
        }
    }

    if (matchCount == 0) {
        return -1; // no match found
    }
    else if (matchCount == 1) {
        return matches[0]; // only one match, return its index
    }
    else {
        // Multiple matches found, show them to the user
        printf("Multiple contacts found with this name:\n");
        for (int i = 0; i < matchCount; i++) {
            int idx = matches[i];
            printf("%d. %s | %s | %s\n", i + 1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        int choice;
        do {
            printf("Enter the index number of the contact you want to edit: ");
            scanf("%d", &choice);
            if (choice >= 1 && choice <= matchCount)
                break;
            printf("Invalid choice. Try again.\n");
        } while (1);

        return matches[choice - 1]; // return selected index
    }
}


int edit_by_phone(char *str, AddressBook *addressBook) {
    for (int i = 0; i < addressBook->contactCount; i++) {//finding the index value with phone
        if (strcmp(addressBook->contacts[i].phone, str) == 0) {
            return i;
        }
    }
    return -1;
}

int edit_by_mail(char *str, AddressBook *addressBook) {
    for (int i = 0; i < addressBook->contactCount; i++) {//finding the index value with mail
        if (strcmp(addressBook->contacts[i].email, str) == 0) {
            return i;
        }
    }
    return -1;
}
int mobilevalidate_edit(char *str, AddressBook *addressBook, int index) {
    int i = 0;

    // Check all characters are digits
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') return 0;
        i++;
    }

    if (i != 10) return 0; // must be exactly 10 digits

    // Check duplicates, skip the contact being edited
    for (int j = 0; j < addressBook->contactCount; j++) {
        if (j == index) continue;  // skip self
        if (strcmp(addressBook->contacts[j].phone, str) == 0) {
            printf("....This mobile number already exists....\n");
            return 0;
        }
    }

    return 1; // valid
}
int mailvalidate_edit(char *str, AddressBook *addressBook, int index) {
    int len = strlen(str);
    int found_at = 0;

    // Basic format checks
    if (len < 5) return 0;  // minimum length for a@b.com
    if (str[0] == '@' || (str[0] >= '0' && str[0] <= '9')) return 0;

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (!((c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              c == '@' || c == '.' || c == '_' || c == '-')) {
            return 0;
        }
        if (c == '@') found_at = 1;
    }

    if (!found_at) return 0;

    // Must end with ".com" (case-insensitive)
    if (len < 4 || strcasecmp(&str[len - 4], ".com") != 0) return 0;

    // Check duplicates, skip the contact being edited
    for (int j = 0; j < addressBook->contactCount; j++) {
        if (j == index) continue;  // skip self
        if (strcasecmp(addressBook->contacts[j].email, str) == 0) {
            printf("....This email already exists....\n");
            return 0;
        }
    }

    return 1; // valid email
}

void deleteContact(AddressBook *addressBook)
{
    char op;
    int index = -1; // index of contact to delete

    printf("Delete by:\n1. Name\n2. Number\n3. Email\n");
    scanf(" %c", &op);

    switch(op)
    {
        case '1': // Name
        {
            char str[50];
            do {
                printf("Enter name to delete: ");
                scanf(" %[^\n]", str);
                if (!namevalidate(str)) {
                    printf("Invalid name format. Try again.\n");
                } else {
                    break;
                }
            } while(1);

            index = edit_by_name(str, addressBook); // reuse search function
            break;
        }

        case '2': // Number
        {
            char str[20];
            do {
                printf("Enter number to delete: ");
                scanf(" %s", str);
                if (!mobilevalidate_search(str)) { // format validation only
                    printf("Invalid phone number format. Try again.\n");
                } else {
                    break;
                }
            } while(1);

            index = edit_by_phone(str, addressBook);
            break;
        }

        case '3': // Email
        {
            char str[50];
            do {
                printf("Enter email to delete: ");
                scanf(" %s", str);
                if (!mailvalidate_search(str)) { // format validation only
                    printf("Invalid email format. Try again.\n");
                } else {
                    break;
                }
            } while(1);

            index = edit_by_mail(str, addressBook);
            break;
        }

        default:
            printf("Invalid option.\n");
            return;
    }

    if (index != -1)
        deleteContactByIndex(addressBook, index);
    else
        printf("Contact not found.\n");
}

void deleteContactByIndex(AddressBook *addressBook, int index) {
    if (index < 0 || index >= addressBook->contactCount) {
        printf("Invalid contact index.\n");
        return;
    }
    for (int i = index; i < addressBook->contactCount - 1; i++) { //-1 buz array index starts from 0
        addressBook->contacts[i] = addressBook->contacts[i + 1];//shifting all contacts 
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully.\n");
}