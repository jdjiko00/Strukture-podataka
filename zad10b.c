#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)

struct _grad;
typedef struct _grad* Point;
typedef struct _grad {
    char imeG[MAX_SIZE];
    int broj;
    Point next;
}grad;

struct _drzava;
typedef struct _drzava* Stablo;
typedef struct _drzava {
    char imeD[MAX_SIZE];
    Stablo L;
    Stablo D;
    grad head;
}drzava;

Stablo DatotekaDrzave(Stablo root, char* fileName);
Stablo Tree(Stablo root, char* imeD, char* fileName);
Stablo MakeTree(char* imeD);
int DatotekaGradovi(Stablo el, char* fileName);
int SortUnos(Point head, char* imeG, int broj);
int MakeEl(Point el, char* imeG, int broj);
int Insert(Point el, Point new);
int IspisDrzava(Stablo root);
int IspisGrad(Point head);
int PretragaDrzava(Stablo root);
Stablo PretragaSabla(Stablo root, char* ime);
int PretragaGrada(Point head, int broj, int* i);
int FreeAll(Stablo root);
int FreeList(Point head);

int main()
{
    Stablo root = NULL;

    root = DatotekaDrzave(root, "drzave.txt");

    IspisDrzava(root);

    PretragaDrzava(root);

    FreeAll(root);

    return EXIT_SUCCESS;
}

Stablo DatotekaDrzave(Stablo root, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = {0};
    char imeD[MAX_SIZE] = {0};
    char datotekaGrad[MAX_SIZE] = {0};

    if(!fp)
    {
        printf("Datoteka drzave nije otvorena!\n");
        return NULL;
    }

    while(!feof(fp))
    {
        fgets(buffer, 1024, fp);
        
        if(sscanf(buffer, " %s %s", imeD, datotekaGrad)==2)
            root = Tree(root, imeD, datotekaGrad);
    }

    fclose(fp);

    return root;
}

Stablo Tree(Stablo root, char* imeD, char* fileName)
{
    if(!root)
    {
        root = MakeTree(imeD);
        DatotekaGradovi(root, fileName);
    }

    else if(strcmp(root->imeD, imeD) > 0)
        root->L = Tree(root->L, imeD, fileName);

    else
        root->D = Tree(root->D, imeD, fileName); 

    return root;
}

Stablo MakeTree(char* imeD)
{
    Stablo new = NULL;
    new = (Stablo)malloc(sizeof(drzava));
    if (!new)
    {
        perror("Memorija za stablo nije alocirana!\n");
        return NULL;
    }

    strcpy(new->imeD, imeD);
    strcpy(new->head.imeG, "");
    new->head.broj = 0;
    new->head.next = NULL;
    new->L = NULL;
    new->D = NULL;

    return new;
}

int DatotekaGradovi(Stablo el, char* fileName)
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
            SortUnos(&el->head, imeG, broj);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int SortUnos(Point head, char* imeG, int broj)
{
    Point tempPrev = head;
    Point tempNext = head->next;

    while (tempNext)
    {
        if(tempNext->broj > broj)
        {
            MakeEl(tempPrev, imeG, broj);
            return EXIT_SUCCESS;
        }

        else if(tempNext->broj == broj)
            if(strcmp(tempNext->imeG, imeG) > 0)
            {
                MakeEl(tempPrev, imeG, broj);
                return EXIT_SUCCESS;
            }

        tempPrev = tempPrev->next;
        tempNext = tempNext->next;
    }

    MakeEl(tempPrev, imeG, broj);

    return EXIT_SUCCESS;
}

int MakeEl(Point el, char* imeG, int broj)
{
    Point new = NULL;

    new = (Point)malloc(sizeof(grad));
    if (!new)
    {
        perror("Memorija za listu nije alocirana!\n");
        return -1;
    }

    strcpy(new->imeG, imeG);
    new->broj = broj;
    new->next = NULL;

    Insert(el, new);

    return EXIT_SUCCESS;
}

int Insert(Point el, Point new)
{
    new->next = el->next;
    el->next = new;

    return EXIT_SUCCESS;
}

int IspisDrzava(Stablo root)
{
    if(root->L)
        IspisDrzava(root->L);

    printf("%s\n", root->imeD);
    IspisGrad(&root->head);

    if(root->D)
        IspisDrzava(root->D);

    return EXIT_SUCCESS;
}

int IspisGrad(Point head)
{
    while(head->next)
    {
        printf("    %s\n", head->next->imeG);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int PretragaDrzava(Stablo root)
{
    char ime[MAX_SIZE] = {0};
    int broj = 0, i = 0;
    Stablo temp = NULL;

    printf("Koju drzavu zelite pretraziti?\n");
    scanf(" %s", ime);
    temp = PretragaSabla(root, ime);
    if(!temp)
    {
        printf("Nema te drzave!\n");
        return -1;
    }

    printf("Upisite broj stanovnika da vidite koji gradovi imaju vise stanovnika od tog broja.\n");
    scanf(" %d", &broj);
    PretragaGrada(&temp->head, broj, &i);

    return EXIT_SUCCESS;
}

Stablo PretragaSabla(Stablo root, char* ime)
{
    if(!strcmp(root->imeD, ime))
        return root;

    else if(strcmp(root->imeD, ime) > 0)
        PretragaSabla(root->D, ime);

    else
        PretragaSabla(root->L, ime);

    return NULL;
}

int PretragaGrada(Point head, int broj, int* i)
{
    while(head->next)
    {
        if(head->next->broj > broj)
        {
            (*i)++;
            printf("%s\n", head->next->imeG);
        }
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int FreeAll(Stablo root)
{
    if(!root)
        return EXIT_SUCCESS;

    FreeList(&root->head);

    FreeAll(root->L);

    FreeAll(root->D);

    free(root);

    return EXIT_SUCCESS;
}

int FreeList(Point head)
{
    Point temp = NULL;
    
    while(head->next)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}