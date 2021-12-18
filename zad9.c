#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define UpGranica (90)
#define DownGranica (10)
#define MAX_SIZE (100)

struct _stablo;
typedef struct _stablo* Pozicija;
typedef struct _stablo{
    int broj;
    Pozicija desno;
    Pozicija lijevo;
}stablo;

struct _list;
typedef struct _list* Point;
typedef struct _list{
    int broj;
    Point next;
}list;

Pozicija Insert(Pozicija root, int broj);
Pozicija Add(int broj);
int InorderPrint(Pozicija root);
int FreeAll(Pozicija root);
int Replace(Pozicija root);
int MakeList(Pozicija root, Point head);
int InsertList(Point head, int broj);
Point AddList(int broj);
int Datoteka(Point head, char* ime);
int Pop(Point head);

int main()
{
    Pozicija root = NULL;
    list head = {.broj = 0, .next = NULL};
    int i = 0;
    int niz[11] = {2,5,7,8,11,1,4,2,3,7,0};
    char ime[MAX_SIZE] = {0};
    srand((unsigned)time(NULL));
// a i b dio zadatka pocetak
    while(niz[i])
    {
        root = Insert(root, niz[i]);
        i++;
    }

    InorderPrint(root);
    printf("\n");

    Replace(root);

    InorderPrint(root);
    printf("\n");

    FreeAll(root);
// a i b dio zadatka kraj
// c dio zadatka pocetak
    root = NULL;
    printf("Koliko ce cvorova imati stablo?\n");
    scanf(" %d", &i);
    while(i)
    {
        root = Insert(root, rand()%(UpGranica - DownGranica - 1) + DownGranica + 1);
        i--;
    }

    MakeList(root, &head);

    printf("Kako ce se zvati datoteka?\n");
    scanf(" %s", ime);
    Datoteka(&head, ime);

    Replace(root);
    MakeList(root, &head);
    Datoteka(&head, ime);

    FreeAll(root);
// c dio zadatka kraj

    return EXIT_SUCCESS;
}

Pozicija Insert(Pozicija root, int broj)
{
    if(!root)
        root = Add(broj);

    else if(broj >= root->broj)
        root->lijevo = Insert(root->lijevo, broj);

    else
        root->desno = Insert(root->desno, broj); 

    return root;
}

Pozicija Add(int broj)
{
    Pozicija new = NULL;
    new = (Pozicija)malloc(sizeof(stablo));
    if(!new)
    {
        perror("Memorija stabla nije alocirana!\n");
        return NULL;
    }

    new->broj = broj;
    new->lijevo = NULL;
    new->desno = NULL;

    return new;
}

int InorderPrint(Pozicija root)
{
    if(root->desno)
        InorderPrint(root->desno);

    printf("%d    ", root->broj);

    if(root->lijevo)
        InorderPrint(root->lijevo);
    
    return EXIT_SUCCESS;
}

int FreeAll(Pozicija root)
{
    if(!root)
        return EXIT_SUCCESS;

    FreeAll(root->lijevo);

    FreeAll(root->desno);

    free(root);

    return EXIT_SUCCESS;
}

int Replace(Pozicija root)
{
    int desno = 0, lijevo = 0;

    if(root->desno)
        desno = root->desno->broj + Replace(root->desno);

    if(root->lijevo)
        lijevo = root->lijevo->broj + Replace(root->lijevo);

    root->broj = desno + lijevo;

    return root->broj;
}

int MakeList(Pozicija root, Point head)
{
    if(root->desno)
        MakeList(root->desno, head);

    InsertList(head, root->broj);

    if(root->lijevo)
        MakeList(root->lijevo, head);
    
    return EXIT_SUCCESS;
}

int InsertList(Point head, int broj)
{
    Point new = NULL;

    new = AddList(broj);

    while(head->next)
        head = head->next;

    head->next = new;

    return EXIT_SUCCESS;
}

Point AddList(int broj)
{
    Point new = NULL;
    new = (Point)malloc(sizeof(list));
    if(!new)
    {
        perror("Memorija liste nije alocirana!\n");
        return NULL;
    }

    new->broj = broj;
    new->next = NULL;

    return new;
}

int Datoteka(Point head, char* ime)
{
    FILE* fp = fopen(ime, "a");
    if(!fp)
    {
        printf("Nemoguce otvoriti datoteku!\n");
        return -1;
    }

    while(head->next)
    {
        fprintf(fp, "%d    ", head->next->broj);
        Pop(head);
    }

    fprintf(fp, "\n");

    fclose(fp);

    return EXIT_SUCCESS;
}

int Pop(Point head)
{
    Point temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}