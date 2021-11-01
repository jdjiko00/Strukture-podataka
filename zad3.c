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

int ReadFromFile(Position head, char* fileName);
Position CreatePerson(char* name, char* surname, int birthYear);
int SortList(Position head, Position newPerson);
int InsertAfter(Position position, Position newPerson);
int PrintList(Position first);
int AddElement(Position head, int position);
Position FindBefore(Position first, int position);
int WriteInFile(Position head, char* fileName);
int FreeAll(Position head);

int main()
{
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
    char fileName[MAX_SIZE] = {0};
    int a = 0;

    printf("From what file do you want to read elements?\n");
    scanf(" %s", fileName);
    ReadFromFile(&head, fileName);

    printf("Print after reading and sorting elements:\n");
    PrintList(head.next);

    printf("After what element do you want to add an element?\n");
    scanf(" %d", &a);
    AddElement(&head, a);

    printf("Before what element do you want to add an element?\n");
    scanf(" %d", &a);
    AddElement(&head, a-1);

    printf("In what file do you want to write elements?\n");
    scanf(" %s", fileName);
    WriteInFile(&head, fileName);

    FreeAll(&head);

    return EXIT_SUCCESS;
}

int ReadFromFile(Position head, char* fileName)
{
    Position newPerson = NULL;
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = {0};
    char name[MAX_SIZE] = {0};
    char surname[MAX_SIZE] = {0};
    int birthYear = 0;

    if(!fp)
    {
        printf("Can't open file to read!\n");
        return -1;
    }

    while(!feof(fp))
    {
        fgets(buffer, 1024, fp);
        if(sscanf(buffer, " %s %s %d", name, surname, &birthYear)==3)
        {
            newPerson = CreatePerson(name, surname, birthYear);
            SortList(head, newPerson);
        }
    }

    fclose(fp);

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

int SortList(Position head, Position newPerson)
{
    Position temp = head->next;

    if(!temp)
    {
        InsertAfter(head, newPerson);
    }
    else if(temp->next)
    {
        if(strcmp(newPerson->surname, temp->surname) >= 0)
        {
            while(temp->next)
            {
                if(strcmp(newPerson->surname, temp->surname) >= 0 && strcmp(newPerson->surname, temp->next->surname) < 0)
                {
                    InsertAfter(temp, newPerson);
                    return EXIT_SUCCESS;
                }
                temp=temp->next;
            }
            if(!temp->next)
            {
                InsertAfter(temp, newPerson);
            }
        }
        else    
        {
            InsertAfter(head, newPerson);
        }
    }

    else
    {
        if(strcmp(newPerson->surname, temp->surname) >= 0)
        {
            InsertAfter(temp, newPerson);
        }
        else
        {
            InsertAfter(head, newPerson);
        }
    }

    return EXIT_SUCCESS;
}

int InsertAfter(Position position, Position newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

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

int AddElement(Position head, int position)
{
    Position personBefore = NULL;
    Position newPerson = NULL;
    char name[MAX_SIZE] = {0};
    char surname[MAX_SIZE] = {0};
    int birthYear = 0;

    if(position < 0)
    {
        printf("Error, illegal value");
        return EXIT_SUCCESS;
    }

    personBefore = FindBefore(head, position);

    if(!personBefore)
    {
        printf("Error, element does not exist!\n");
        return EXIT_SUCCESS;
    }

    scanf(" %s %s %d", name, surname, &birthYear);
    newPerson = CreatePerson(name, surname, birthYear);

    InsertAfter(personBefore, newPerson);

    return EXIT_SUCCESS;
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

int WriteInFile(Position head, char* fileName)
{
    Position temp = head;
    FILE* fp = fopen(fileName, "w");
    if(!fp)
    {
        printf("Can't open file to write!\n");
        return -1;
    }
    while(temp->next)
    {
        temp = temp->next;
        fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
    }

    fclose(fp);

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