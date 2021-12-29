#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)

struct _grad;
typedef struct _grad* Stablo;
typedef struct _grad {
    char imeG[MAX_SIZE];
    int broj;
    Stablo L;
    Stablo D;
}grad;

struct _drzava;
typedef struct _drzava* Point;
typedef struct _drzava {
    char imeD[MAX_SIZE];
    Stablo root;
    Point next;
}drzava;

int DatotekaDrzave(Point head, char* fileName);
int SortUnos(Point head, char* imeD, char* fileName);
Point MakeEl(Point head, char* imeD);
int Insert(Point el, Point new);
int DatotekaGradovi(Point el, char* fileName);
Stablo Tree(Stablo root, char* imeG, int broj);
Stablo MakeTree(char* imeG, int broj);
int IspisDrzava(Point head);
int IspisGrad(Stablo root);
int PretragaDrzava(Point head);
int PretragaGradova(Stablo root, int broj, int* i);
int FreeAll(Point head);
int FreeTree(Stablo root);
int Pop(Point head);

int main()
{
    drzava head = { .imeD = {0}, .root = NULL, .next = NULL };

    DatotekaDrzave(&head, "drzave.txt");

    IspisDrzava(&head);

    PretragaDrzava(&head);

    FreeAll(&head);

    return EXIT_SUCCESS;
}

int DatotekaDrzave(Point head, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = {0};
    char imeD[MAX_SIZE] = {0};
    char datotekaGrad[MAX_SIZE] = {0};

    if(!fp)
    {
        printf("Datoteka drzave nije otvorena!\n");
        return -1;
    }

    while(!feof(fp))
    {
        fgets(buffer, 1024, fp);
        
        if(sscanf(buffer, " %s %s", imeD, datotekaGrad)==2)
            SortUnos(head, imeD, datotekaGrad);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int SortUnos(Point head, char* imeD, char* fileName)
{
    Point tempPrev = head;
    Point tempNext = head->next;
    Point el = NULL;

    while (tempNext)
    {
        if (strcmp(tempNext->imeD, imeD) > 0)
        {
            el = MakeEl(tempPrev, imeD);
            DatotekaGradovi(el, fileName);
            return EXIT_SUCCESS;
        }

        tempPrev = tempPrev->next;
        tempNext = tempNext->next;
    }

    el = MakeEl(tempPrev, imeD);
    DatotekaGradovi(el, fileName);

    return EXIT_SUCCESS;
}

Point MakeEl(Point el, char* imeD)
{
    Point new = NULL;

    new = (Point)malloc(sizeof(drzava));
    if (!new)
    {
        perror("Memorija za listu nije alocirana!\n");
        return NULL;
    }

    strcpy(new->imeD, imeD);
    new->root = NULL;
    new->next = NULL;

    Insert(el, new);

    return new;
}

int Insert(Point el, Point new)
{
    new->next = el->next;
    el->next = new;

    return EXIT_SUCCESS;
}

int DatotekaGradovi(Point el, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = {0};
    char imeG[MAX_SIZE] = {0};
    int broj = 0;

    if(!fp)
    {
        printf("Datoteka grad nije otvorena!\n");
        return -1;
    }

    while(!feof(fp))
    {
        fgets(buffer, 1024, fp);

        if(sscanf(buffer, " %s %d", imeG, &broj)==2)
            el->root = Tree(el->root, imeG, broj);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

Stablo Tree(Stablo root, char* imeG, int broj)
{
    Stablo temp = NULL;

    if (!root)
        root = MakeTree(imeG, broj);

    else if (broj < root->broj)
        root->L = Tree(root->L, imeG, broj);

    else if (broj > root->broj)
        root->D = Tree(root->D, imeG, broj);

    else
    {
        if(strcmp(root->imeG, imeG) < 0)
        {
            if(root->D->broj == broj)
                root->D = Tree(root->D, imeG, broj);

            else
            {
                temp = root->D;
                root->D = MakeTree(imeG, broj);
                root->D->D = temp;
            }
        }

        else
        {
            if(root->L->broj == broj)
                root->L = Tree(root->L, imeG, broj);

            else
            {
                temp = root->L;
                root->L = MakeTree(imeG, broj);
                root->L->L = temp;
            }
        }
    }

    return root;
}

Stablo MakeTree(char* imeG, int broj)
{
    Stablo new = NULL;
    new = (Stablo)malloc(sizeof(grad));
    if (!new)
    {
        perror("Memorija za stablo nije alocirana!\n");
        return NULL;
    }

    strcpy(new->imeG, imeG);
    new->broj = broj;
    new->L = NULL;
    new->D = NULL;

    return new;
}

int IspisDrzava(Point head)
{
    while(head->next)
    {
        printf("%s\n", head->next->imeD);
        IspisGrad(head->next->root);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int IspisGrad(Stablo root)
{
    if(root->L)
        IspisGrad(root->L);

    printf("    %s\n", root->imeG);

    if(root->D)
        IspisGrad(root->D);

    return EXIT_SUCCESS;
}

int PretragaDrzava(Point head)
{
    char ime[MAX_SIZE] = {0};
    int broj = 0, i = 0;
    Point temp = NULL;

    printf("Koju drzavu zelite pretraziti?\n");
    scanf(" %s", ime);
    while(head->next)
    {
        if(!strcmp(head->next->imeD, ime))
        {
            temp = head->next;
            break;
        }
        head = head->next;
    }
    if(!head->next)
    {
        printf("Nema te drzave!\n");
        return -1;
    }

    printf("Upisite broj stanovnika da vidite koji gradovi imaju vise stanovnika od tog broja.\n");
    scanf(" %d", &broj);
    PretragaGradova(temp->root, broj, &i);

    if(!i)
        printf("Nepostoje ti gradovi!\n");

    return EXIT_SUCCESS;
}

int PretragaGradova(Stablo root, int broj, int* i)
{
    if(root->broj > broj)
    {
        printf("%s\n", root->imeG);
        (*i)++;
        if(root->L)
            if(root->L->broj > broj)
                PretragaGradova(root->L, broj, i);
    }

    if(!root->D)
        return EXIT_SUCCESS;

    if(root->D->broj > broj)
        PretragaGradova(root->D, broj, i);

    return EXIT_SUCCESS;
}

int FreeAll(Point head)
{
    while(head->next)
    {
        FreeTree(head->next->root);
        Pop(head);
    }

    return EXIT_SUCCESS;
}

int FreeTree(Stablo root)
{
    if(!root)
        return EXIT_SUCCESS;

    FreeTree(root->L);

    FreeTree(root->D);

    free(root);

    return EXIT_SUCCESS;
}

int Pop(Point head)
{
    Point temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}