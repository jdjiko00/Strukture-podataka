#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}student;

int BrojRedaka(char* naziv);
student* AlociranjeMemorije(int brojStudenata, char* naziv);
double NajveciBodovi(int brojStudenata, student* studenti);
void IspisStudenata(int brojStudenata, double maxBodovi, student* studenti);

int main()
{
    char naziv[MAX_SIZE] = {0};
    int i = 0;
    double maxBodovi = 0;
    student* studenti = NULL;

    scanf(" %s", naziv);
    i = BrojRedaka(naziv);
    studenti = AlociranjeMemorije(i, naziv);
    maxBodovi = NajveciBodovi(i, studenti);
    IspisStudenata(i, maxBodovi, studenti);

    free(studenti);

    return 0;
}

int BrojRedaka(char* naziv)
{
    int i = 0;
    FILE* fp = NULL;
    char buffer[MAX_LINE] = {0};

    fp = fopen(naziv, "r");
    if(!fp)
    {
        printf("Greška!");
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp);
        i++;
    }

    fclose(fp);

    return i;
}

student* AlociranjeMemorije(int brojStudenata, char* naziv)
{
    int i = 0;
    FILE* fp = NULL;
    student* studenti = NULL;

    studenti = (student* )malloc(brojStudenata * sizeof(student));
    fp = fopen(naziv, "r");
    if(!fp)
    {
        printf("Greska alociranja!");
        free(studenti);
        return NULL;
    }
    while(!feof(fp))
    {
        fscanf(fp, " %s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i]. bodovi);
        i++;
    }

    fclose(fp);

    return studenti;
}

double NajveciBodovi(int brojStudenata, student* studenti)
{
    int i = 0;
    double maxBodovi = 0;

    maxBodovi = studenti[0].bodovi;
    i = 1;

    while(i < brojStudenata)
    {
        if(maxBodovi < studenti[i].bodovi)
        {
            maxBodovi = studenti[i].bodovi;
        }
        i++;
    }

    return maxBodovi;
}

void IspisStudenata(int brojStudenata, double maxBodovi, student* studenti)
{
    int i = 0;
    double relativniBodovi = 0;

    while(i < brojStudenata)
    {
        relativniBodovi = (studenti[i].bodovi/maxBodovi)*100;
        printf("\nIme: %s \nPrezime: %s \nApsolutni broj bodova: %lf \nRelativni broj bodova: %lf \n\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativniBodovi);
        i++;
    }
}