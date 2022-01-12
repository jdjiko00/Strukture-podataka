#include<stdio.h>
#include<stdlib.h>

struct _stablo;
typedef struct _stablo* Pozicija;
typedef struct _stablo{
    int broj;
    Pozicija desno;
    Pozicija lijevo;
}stablo;

struct _red;
typedef struct _red* Point;
typedef struct _red{
    Pozicija el;
    Point next;
}red;

int Search(int broj, Pozicija root);
Pozicija UnosenjeElementa(int broj, Pozicija root);
int FreeAll(Pozicija root);
int InorderPrint(Pozicija root);
int PreorderPrint(Pozicija root);
int PostorderPrint(Pozicija root);
int LevelorderPrint(Pozicija root);
int MakeRed(Point head, Pozicija el);
int Pop(Point head);

int main()
{
    Pozicija root = NULL;
    int broj = 0;

    while(1)
    {
        scanf(" %d", &broj);
        if(!broj)
            break;
        root = UnosenjeElementa(broj, root);
    }

    printf("Inoreder ispisivanje: ");
    InorderPrint(root);
    printf("\n");
    printf("Preoreder ispisivanje: ");
    PreorderPrint(root);
    printf("\n");
    printf("Postoreder ispisivanje: ");
    PostorderPrint(root);
    printf("\n");
    printf("Leveloreder ispisivanje: ");
    LevelorderPrint(root);
    printf("\n");

    scanf(" %d", &broj);
    Search(broj, root);

    FreeAll(root);

    return EXIT_SUCCESS;
}

int Search(int broj, Pozicija root)
{
    if(!root)
        return -1;

    if(broj == root->broj)
    {
        printf("%d\n", root->broj);
        return EXIT_SUCCESS;
    }

    else if(broj < root->broj)
        Search(broj, root->lijevo);

    else if(broj > root->broj)
        Search(broj, root->desno);

    return EXIT_SUCCESS;
}

Pozicija UnosenjeElementa(int broj, Pozicija root)
{
    Pozicija noviEl = NULL;
    if(!root)
    {
        noviEl = (Pozicija)malloc(sizeof(stablo));
        if (!noviEl)
        {
            perror("Memorija stabla nije alocirana!\n");
            return NULL;
        }
        noviEl->broj = broj;
        noviEl->desno = NULL;
        noviEl->lijevo = NULL;

        root = noviEl;
    }

    else if(broj < root->broj)
        root->lijevo = UnosenjeElementa(broj, root->lijevo);

    else if(broj > root->broj)
        root->desno = UnosenjeElementa(broj, root->desno);
    
    return root;
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

int InorderPrint(Pozicija root)
{
    if(root->lijevo)
        InorderPrint(root->lijevo);

    printf("%d    ", root->broj);

    if(root->desno)
        InorderPrint(root->desno);
    
    return EXIT_SUCCESS;
}

int PreorderPrint(Pozicija root)
{
    printf("%d    ", root->broj);

    if(root->lijevo)
        PreorderPrint(root->lijevo);

    if(root->desno)
        PreorderPrint(root->desno);
    
    return EXIT_SUCCESS;
}

int PostorderPrint(Pozicija root)
{
    if(root->lijevo)
        PostorderPrint(root->lijevo);

    if(root->desno)
        PostorderPrint(root->desno);

    printf("%d    ", root->broj);
    
    return EXIT_SUCCESS;
}

int LevelorderPrint(Pozicija root)
{
    red p = {.el = NULL, .next = NULL};
    Point head = &p;

    if(!root)
        return EXIT_SUCCESS;

    else
    {
        MakeRed(head, root);

        while(head->next)
        {
            printf("%d    ", head->next->el->broj);

            if(head->next->el->lijevo)
                MakeRed(head, head->next->el->lijevo);

            if(head->next->el->desno)
                MakeRed(head, head->next->el->desno);

            Pop(head);
        }
    }

    while(head->next)
    {
        printf("%d    ", head->next->el->broj);

        if(head->next->el->lijevo)
            MakeRed(head, head->next->el->lijevo);

        if(head->next->el->desno)
            MakeRed(head, head->next->el->desno);

        Pop(head);
    }

    return EXIT_SUCCESS;
}

int MakeRed(Point head, Pozicija el)
{
    Point new = NULL;
    Point temp = NULL;

    new = (Point)malloc(sizeof(red));
    if(!new)
    {
        perror("Memorija reda nije alocirana!\n");
        return -1;
    }

    new->el = el;
    new->next = NULL;

    while(head->next)
    {
        head = head->next;
    }

    head->next = new;

    return EXIT_SUCCESS;
}

int Pop(Point head)
{
    Point temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}