#include<stdio.h>
#include<stdlib.h>

struct _stablo;
typedef struct _stablo* Pozicija;
typedef struct _stablo{
    int broj;
    Pozicija desno;
    Pozicija lijevo
}stablo;

Pozicija Trazi(int broj, Pozicija list);
int UnosenjeElementa(int broj, Pozicija list);
Pozicija BrisiSve(Pozicija list);
int Ispis(Pozicija list);

int main()
{
    Pozicija root = NULL;
    int broj = 0;

    scanf(" %d", &broj);

    root = Trazi(broj, root);

    root = UnosenjeElementa(broj, root);

    Ispis(root);

    root = BrisiSve(root);

    return EXIT_SUCCESS;
}

Pozicija Trazi(int broj, Pozicija list)
{
    if(!list)
        return NULL;

    else if(broj < list->broj)
        return Trazi(broj, list->lijevo);

    else if(broj > list->broj)
        return Trazi(broj, list->desno);

    return list;
}

Pozicija UnosenjeElementa(int broj, Pozicija list)
{
    Pozicija noviEl = NULL;
    if(!list)
    {
        noviEl = (Pozicija)malloc(sizeof(stablo));
        if (!noviEl)
        {
            perror("Memorija nije alocirana!\n");
            return -1;
        }
        noviEl->broj = broj;
        noviEl->desno = NULL;
        noviEl->lijevo = NULL;
    }

    else if(broj < list->broj)
        list->lijevo = UnosenjeElementa(broj, list->lijevo);

    else if(broj > list->broj)
        list->desno = UnosenjeElementa(broj, list->desno);
    
    return noviEl;
}

Pozicija BrisiSve(Pozicija list)
{
    if(!list)
        return NULL;

    BrisiSve(list->lijevo);

    BrisiSve(list->desno);

    free(list);

    return NULL;
}
int Ispis(Pozicija list)
{
    if (!list)
		return EXIT_SUCCESS;

	Ispis(list->lijevo);
	printf("%d ", list->broj);
	Ispis(list->desno);

    return EXIT_SUCCESS;
}