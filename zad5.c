#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _StackElement;
typedef struct _StackElement* Position;
struct _StackElement{
    double number;
    Position next;
}StackElement;

Position CreateStackElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* destination, Position head);
int PerformOperation(Position head, char operation);
int CalculatePostfixFile(double* result, char* fileName);

int main()
{
    double result = 0;
    char fileName[MAX_SIZE] = {0};

    scanf(" %s", fileName);

    if(CalculatePostfixFile(&result, fileName) == EXIT_SUCCESS)
    {
        printf("Result is: %lf\n", result);
    }

    return EXIT_SUCCESS;
}

Position CreateStackElement(double number)
{
    Position newElement = NULL;

    newElement = (Position)malloc(sizeof(StackElement));
    if (!newElement)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int InsertAfter(Position position, Position newElement)
{
    newElement->next = position->next;
    position->next = newElement;

    return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
    Position newElement = NULL;

    newElement = CreateStackElement(number);
    if (!newElement)
    {
        return -1;
    }

    InsertAfter(head, newElement);

    return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
    Position temp = position->next;
    if (!temp)
    {
        return EXIT_SUCCESS;
    }

    position->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}

int Pop(double* destination, Position head)
{
    Position first = head->next;

    if (!first)
    {
        perror("Postfix not valid! Please check your file!\n");
        return -1;
    }

    *destination = first->number;

    DeleteAfter(head);

    return EXIT_SUCCESS;
}

int PerformOperation(Position head, char operation, double* result)
{
    double operand2 = 0;
    double operand1 = 0;
    int status1 = EXIT_SUCCESS;
    int status2 = EXIT_SUCCESS;
    double result = 0;

    status2 = pop(&operand2, head);
    if (status2 != EXIT_SUCCESS)
    {
        return -1;
    }

    status1 = pop(&operand1, head);
    if (status1 != EXIT_SUCCESS)
    {
        return -2;
    }

    switch (operation)
    {
        case '+':
        {
            *result = operand1 + operand2;
            break;
        }
        case '-':
        {
            *result = operand1 - operand2;
            break;
        }
        case '*':
        {
            *result = operand1 * operand2;
            break;
        }
        case '/':
        {
            if (operand2 == 0)
            {
                printf("Cannot divide with zero!\n");
                return -3;
            }
            *result = operand1 / operand2;
            break;
        }
        default:
            printf("This operation is not supported yet!\n");
        return -4;
    }

    Push(head, *result);

    return EXIT_SUCCESS;
}

int CalculatePostfixFile(double* result, char* fileName)
{
    FILE* file = NULL;
    char* buffer = NULL;
    int fileLength = 0;
    char* currentBuffer = NULL;
    int numBytes = 0;
    int status = 0;
    char operation = 0;
    double number = 0;
    StackElement p = { .number = 0, .next = NULL };
    Position head = &p;

    file = fopen(fileName, "rb");
    if (!file)
    {
        perror("Can't open file\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);

    buffer = (char*)calloc(fileLength + 1, sizeof(char));
    if (!buffer)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    rewind(file);
    fread(buffer, sizeof(char), fileLength, file);
    printf("|%s|\n", buffer);
    fclose(file);

    currentBuffer = buffer;

    while (strlen(curentBuffer > 0))
    {
        status = sscanf(currentBuffer, "%lf %n", &number, &numBytes);
        if (status == 1)
        {
            Push(head, number);
            currentBuffer += numBytes;
        }
        else{
            sscanf(currentBuffer, " %c %n", &operation, &numBytes);
            status = PerformOperation(head, operation);
            if (status != EXIT_SUCCESS)
            {
                free(buffer);
                while (head.next != NULL)
                {
                    DeleteAfter(head);
                }
                return -1;
            }
            currentBuffer += numBytes;
        }
    }

    if(head->next)
    {
        DeleteAfter(head);
    }

    free(buffer);

    return EXIT_SUCCESS;
}