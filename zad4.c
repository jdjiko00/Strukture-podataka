#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct _polinom;
typedef struct _polinom* pozicija;
typedef struct _polinom{
    int koeficijent;
    int potencija;
    pozicija next;
}polinom;

int CitanjeDatoteke(pozicija head1, pozicija head2, char* naziv);
int StvaranjeListe(pozicija head, char* buffer);
pozicija StvaranjeClana(int koeficijent, int potencija);
int SortiraniUnos(pozicija head, pozicija novi);
int Spoji(pozicija mjesto, pozicija novi);
int Dodaj(pozicija mjesto, pozicija novi);
int Izbrisi(pozicija mjesto);
int IspisListe(pozicija prvi);
int Zbrajanje(pozicija head, pozicija head1, pozicija head2);
int Unos(int koeficijent, int potencija, pozicija head);
int Mnozenje(pozicija head, pozicija head1, pozicija head2);
int FreeAll(pozicija head);

int main()
{
    polinom head1 = {.koeficijent = 0, .potencija = 0, .next = NULL};
    polinom head2 = {.koeficijent = 0, .potencija = 0, .next = NULL};
    polinom head = {.koeficijent = 0, .potencija = 0, .next = NULL};
    char naziv[50] = {0};

    scanf(" %s", naziv);

    if (CitanjeDatoteke(&head1, &head2, naziv) == EXIT_SUCCESS)
	{
		IspisListe(head1.next);
		IspisListe(head2.next);

		Zbrajanje(&head, &head1, &head2);
        IspisListe(head.next);
        FreeAll(&head);

		Mnozenje(&head, &head1, &head2);
        IspisListe(head.next);
        FreeAll(&head);

        FreeAll(&head1);
        FreeAll(&head2);
	}

    return EXIT_SUCCESS;
}

int CitanjeDatoteke(pozicija head1, pozicija head2, char* naziv)
{
    FILE* fp = fopen(naziv, "r");
    char buffer[1024] = {0};
    int status = EXIT_SUCCESS;

    if(!fp)
    {
        perror("Nemogucnost otvaranja datoteke!\n");
        return -1;
    }
    fgets(buffer, 1024, fp);
    status =StvaranjeListe(head1, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, 1024, fp);
	status = StvaranjeListe(head2, buffer);
	if (status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(fp);

    return EXIT_SUCCESS;
}

int StvaranjeListe(pozicija head, char* buffer)
{
    pozicija novi = NULL;
    char trenutni[1024] = {0};
	int koef = 0;
	int pot = 0;
	int brB = 0;
	int status = 0;

    strcpy(trenutni, buffer);
	while (strlen(trenutni) > 0)
	{
		status = sscanf(trenutni, " %d %d %n", &koef, &pot, &brB);
		if (status != 2)
		{
			printf("Error, datoteka nevalja!\n");
			return EXIT_FAILURE;
		}

		novi = StvaranjeClana(koef, pot);
		if (!novi)
		{
			return EXIT_FAILURE;
		}

		SortiraniUnos(head, novi);

		trenutni += brB;
	}

    return EXIT_SUCCESS;
}

pozicija StvaranjeClana(int koeficijent, int potencija)
{
    pozicija novi = NULL;

	novi = (pozicija)malloc(sizeof(polinom));
	if (!novi)
	{
		perror("Nemogucnost alociranja memorije!\n");
		return NULL; 
	}

	novi->koeficijent = koeficijent;
	novi->potencija = potencija;
	novi->next = NULL;

	return novi;
}

int SortiraniUnos(pozicija head, pozicija novi)
{
    pozicija temp = head;

	while (temp->next != NULL && temp->next->potencija < novi->potencija) 
	{
		temp = temp->next;
	}

	Spoji(temp, novi);

    return EXIT_SUCCESS;
}

int Spoji(pozicija mjesto, pozicija novi)
{
    int koef = 0;

    if (mjesto->next == NULL || mjesto->next->potencija != novi->potencija)
	{
		Dodaj(mjesto, novi);
	}
	else {
		koef = mjesto->next->koeficijent + novi->koeficijent;
		if (koef == 0) 
		{
			Izbrisi(mjesto);
		}
		else {
			mjesto->next->koeficijent = koef;
		}
		free(novi);
	}

	return EXIT_SUCCESS;
}

int Dodaj(pozicija mjesto, pozicija novi)
{
    novi->next = mjesto->next;
	mjesto->next = novi;

	return EXIT_SUCCESS;
}

int Izbrisi(pozicija mjesto)
{
    pozicija temp = NULL;

	temp = mjesto->next;
	mjesto->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int IspisListe(pozicija prvi)
{
    if (prvi) 
    {
		if (prvi->potencija < 0) 
        {
			if (prvi->koeficijent == 1)
			{
				printf("x^(%d)", prvi->potencija);
			}
			else {
				printf("%dx^(%d)", prvi->koeficijent, prvi->potencija);
			}
		}
		else {
			if (prvi->koeficijent == 1)
			{
				printf("x^%d", prvi->potencija);
			}
			else {
				printf("%dx^%d", prvi->koeficijent, prvi->potencija);
			}
		}

		prvi = prvi->next;
	}

    while(prvi)
    {
        if (prvi->koeficijent < 0) 
        {
			if (prvi->potencija < 0) 
            {
				printf(" - %dx^(%d)", abs(prvi->koeficijent), prvi->potencija);
			}
			else {
				printf(" - %dx^%d", abs(prvi->koeficijent), prvi->potencija);
			}
		}
		else {
			if (prvi->potencija < 0) 
            {
				if (prvi->koeficijent == 1)
				{
					printf(" + x^(%d)", prvi->potencija);
				}
				else {
					printf(" + %dx^(%d)", prvi->koeficijent, prvi->potencija);
				}
			}
			else {
				if (prvi->koeficijent == 1)
				{
					printf(" + x^%d", prvi->potencija);
				}
				else
				{
					printf(" + %dx^%d", prvi->koeficijent, prvi->potencija);
				}
			}
		}
        prvi = prvi->next;
    }

	printf("\n");

	return EXIT_SUCCESS;
}

int Zbrajanje(pozicija head, pozicija head1, pozicija head2)
{
    pozicija temp1 = head1->next;
	pozicija temp2 = head2->next;

	while (temp1 != NULL && temp2 != NULL) 
	{
		if (temp1->potencija == temp2->potencija)
		{
			Unos(temp1->koeficijent + temp2->koeficijent, temp1->potencija, head);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->potencija > temp2->potencija)
		{
			Unos(temp1->koeficijent, temp1->potencija, head);
			temp1 = temp1->next;
		}
		else {
			Unos(temp2->koeficijent, temp2->potencija, head);
			temp2 = temp2->next;
		}

	}
    while(temp1)
    {
        Unos(temp1->koeficijent, temp1->potencija, head);
		temp1 = temp1->next;
    }
    while(temp2)
    {
        Unos(temp2->koeficijent, temp2->potencija, head);
		temp2 = temp2->next;
    }

	return EXIT_SUCCESS;
}

int Unos(int koeficijent, int potencija, pozicija mjesto)
{
    pozicija novi = StvaranjeClana(koeficijent, potencija);
	if (!novi)
	{
		return EXIT_FAILURE;
	}

	Dodaj(mjesto, novi);
	mjesto = mjesto->next;

	return EXIT_SUCCESS;
}

int Mnozenje(pozicija head, pozicija head1, pozicija head2)
{
    pozicija novi = NULL;
    pozicija temp1 = head1->next;
	pozicija temp2 = NULL;

    while(temp1)
    {
        temp2 = head2->next;
        while(temp2)
        {
            novi = StvaranjeClana(temp1->koeficijent * temp2->koeficijent, temp1->potencija + temp2->potencija);
            if(!novi)
            {
                return EXIT_FAILURE;
            }
            SortiraniUnos(head, novi);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

	return EXIT_SUCCESS;
}

int FreeAll(pozicija head)
{
    pozicija temp1 = head;
    pozicija temp2 = NULL;

    while(temp1->next)
    {
        temp2 = temp1->next;
        temp1->next = temp1->next->next;
        free(temp2);
    }
	
	return EXIT_SUCCESS;
}