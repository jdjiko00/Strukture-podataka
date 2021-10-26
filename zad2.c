#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position first, int position);
int DeleteAfter(Position head, int position);
int FreeAll(Position head);

int main(int argc, char** argv)
{
    Person zeroth = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
    Position head = &zeroth;
    Position prezime = NULL;
    int a = 0, birthYear = 0;
    char name[MAX_SIZE] = {0}, surname[MAX_SIZE] = {0};

    printf("Koliko zelite osoba dodati na pocetku?\n");
    scanf(" %d", &a);
    printf("Upisite osobe:\n");
    while(a)
    {
        scanf(" %s %s %d", name, surname, &birthYear);
        PrependList(head, name, surname, birthYear);
        a--;
    }

    printf("Ispis osoba nakon dodavanja na pocetku:\n");
    PrintList(head->next);

    printf("Koliko zelite osoba dodati na kraju?\n");
    scanf(" %d", &a);
    printf("Upisite osobe:\n");
    while(a)
    {
        scanf(" %s %s %d", name, surname, &birthYear);
        AppendList(head, name, surname, birthYear);
        a--;
    }

    printf("Ispis osoba nakon dodavanja na kraju:\n");
    PrintList(head->next);

    printf("Upisite prezime osobe koje zelite naci:\n");
    scanf(" %s", surname);
    prezime = FindBySurname(head->next, surname);
    if(!prezime)
    {
        printf("Nepostoji ta osoba!\n");
    }
    else
    {
        printf("Name: %s, surname: %s, birthYear: %d\n", prezime->name, prezime->surname, prezime->birthYear);
    }

    printf("Koji element zelite izbrisati iz vezane liste?\n");
    scanf(" %d", &a);
    DeleteAfter(head, a);

    printf("Ispis osoba nakon brisanja odredenog elementa:\n");
    PrintList(head->next);

    FreeAll(head);

    return EXIT_SUCCESS;
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = CreatePerson(name, surname, birthYear);

    if (!newPerson)
    {
        return -1;
    }

    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

int PrintList(Position first)
{
    Position temp = first;
    while (temp)
    {
        printf("Name: %s, surname: %s, birthYear: %d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (!newPerson)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
    Position temp = head;

    while (temp->next)
    {
        temp = temp->next;
    }

    return temp;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;

    newPerson = CreatePerson(name, surname, birthYear);

    if (!newPerson)
    {
        return -1;
    }

    last = FindLast(head);
    InsertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

Position FindBySurname(Position first, char* surname)
{
    Position temp = first;

    while (temp)
    {
        if (strcmp(temp->surname, surname) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }

    return temp;
}

Position FindBefore(Position head, int position)
{
    Position temp = head;

    while (position)
    {
        temp = temp->next;
        if(!temp->next)
        {
            return NULL;
        }
        position--;
    }

    return temp;
}

int DeleteAfter(Position head, int position)
{
    Position temp1 = FindBefore(head, position-1);
    Position temp2 = NULL;
    if(!temp1)
    {
        printf("Taj element nepostoji!\n");
    }
    else
    {
        temp2 = temp1->next;
        temp1->next = temp1->next->next;
        free(temp2);
    }

    return EXIT_SUCCESS;
}

int FreeAll(Position head)
{
    Position temp1 = head;
    Position temp2 = NULL;

    while(temp1->next)
    {
        temp2 = temp1->next;
        temp1->next = temp1->next->next;
        free(temp2);
    }

    return EXIT_SUCCESS;
}