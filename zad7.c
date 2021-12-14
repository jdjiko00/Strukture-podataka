#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (128)

struct _el;
typedef struct _el* Position;
typedef struct _el{
    char name[MAX_SIZE];
    Position sibling;
    Position child;
}el;

struct _stog;
typedef struct _stog* StogP;
typedef struct _stog{
    Position point;
    StogP next;
}stog;

Position Insert(Position current, Position newElement);
Position MakeElement(Position parent, char* name);
Position md(StogP head, Position Dir, char* name);
int Push(StogP head, Position element);
Position cd2(StogP head, Position Dir);
int Pop(StogP head);
Position cd(StogP head, Position Dir, char* name);
int dir(Position Dir);
int FreeElements(Position current, Position following);
int FreeStog(StogP head);
int Ispis(Position Dir, Position first);

int main()
{
    stog headS = {.point = NULL, .next = NULL};
    el headE = {.name = {0}, .sibling = NULL, .child = NULL};
    Position Dir = &headE;
    char command[MAX_SIZE] = {0};
    char name[MAX_SIZE] = {0};

    while(strcmp(command, "izlaz"))
    {
        Ispis(Dir, headE.child);
        scanf(" %s %s", command, name);
        if(!strcmp(command, "md") || !strcmp(command, "cd") || !strcmp(command, "dir") || !strcmp(command, "izlaz"))
            printf("Ta naredba nepostoji!\n");

        if(!strcmp(command, "md"))
        {
            Dir = md(&headS, Dir, name);
        }

        else if(!strcmp(command, "cd"))
        {
            if(!strcmp(name, ".."))
                Dir = cd2(&headS, Dir);

            else Dir = cd(&headS, Dir, name);
        }

        else if(!strcmp(command, "dir"))
        {
            dir(Dir);
        }
    }

    FreeStog(&headS);
    FreeElements(&headE, headE.child);

    return EXIT_SUCCESS;
}

Position Insert(Position current, Position newElement)
{
    if(!current)
    {
        return newElement;
    }

    if(strcmp(current->name, newElement->name) < 0)
    {
        current->sibling = Insert(current->sibling, newElement);
    }

    else if(strcmp(current->name, newElement->name) > 0)
    {
        newElement->sibling = current;
        return newElement;
    }

    return current;
}

Position MakeElement(Position parent, char* name)
{
    Position newElement = NULL;

    newElement = (Position)malloc(sizeof(el));

    if (!newElement)
    {
        perror("Memorija nije alocirana!\n");
        return NULL;
    }

    strcpy(newElement->name, name);
    newElement->sibling = NULL;
    newElement->child = NULL;

    parent->child = Insert(parent->child, newElement);

    return parent->child;
}

Position md(StogP head, Position Dir, char* name)
{
    Position temp = NULL;

    if(!head->next)
    {
        temp = MakeElement(Dir, name);
        Push(head, temp);
        return temp;
    }

    temp = MakeElement(Dir, name);

    return Dir;
}

int Push(StogP head, Position element)
{
    StogP newStog = NULL;

    newStog = (StogP)malloc(sizeof(stog));

    if (!newStog)
    {
        perror("Memorija nije alocirana!\n");
        return -1;
    }

    newStog->point = element;
    newStog->next = head->next;
    head->next = newStog;

    return EXIT_SUCCESS;
}

Position cd2(StogP head, Position Dir)
{
    if(!head->next->next)
    {
        printf("Nema gornjih direktorija!\n");
        return Dir;
    }

    Pop(head);

    return head->next->point;
}

int Pop(StogP head)
{
    StogP temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}

Position cd(StogP head, Position Dir, char* name)
{
    Position temp = Dir->child;

    while(temp)
    {
        if(!strcmp(temp->name, name))
        {
            Push(head, temp);
            return temp;
        }
        temp = temp->sibling;
    }

    if(!temp)
    {
        printf("Nepostoji taj direktorij!\n");
        return Dir;
    }
}

int dir(Position Dir)
{
    Position temp = Dir->child;

    if(!temp)
    {
        printf("Direktorij je prazan!\n");
        return EXIT_SUCCESS;
    }

    while (temp)
    {
        printf("    %s\n", temp->name);
        temp = temp->sibling;
    }

    return EXIT_SUCCESS;
}

int FreeElements(Position current, Position following)
{
    Position temp = NULL;

    if(following->child)
        FreeElements(following, following->child);

    temp = following;
    following = following->sibling;
    current->child = following;
    free(temp);
    if(current->child)
        FreeElements(current, following);
    
    return EXIT_SUCCESS;
}

int FreeStog(StogP head)
{
    StogP temp = NULL;

    while(head->next)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}

int Ispis(Position Dir, Position first)
{
    if(!first)
        printf("Napravite glavni direktorij!\n");

    else printf(":\\%s> ", Dir->name);

    return EXIT_SUCCESS;
}