#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient {
    struct patient *prev;
    char name[20];
    int age;
    int ward_num;
    struct patient *next;
};

void addAtBeg(struct patient **);
void addAtEnd(struct patient **);
void addAtPos(struct patient **, int);
void deleteFromBeg(struct patient **);
void deleteFromEnd(struct patient **);
void deletePos(struct patient **, int);
void deleteElement(struct patient **);
void freeNodes(struct patient **);
void countNodes(struct patient **);
void display(struct patient *);

int main() 
{
    struct patient *head = NULL;
    int choice, pos;

    while (1) 
    {
        printf("*************************\n");
        printf(" 1. Add at Beginning\n 2. Add at End\n 3. Add at Position\n 4. Delete from Beginning\n 5. Delete from End\n 6. Delete a Position\n 7. Delete by Element\n 8. Free all Nodes\n 9. Count Nodes\n 10. Display\n 11. Quit\n"); 
        printf("Enter a choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) 
        {
            case 1: 
                addAtBeg(&head); 
                break;
            case 2: 
                addAtEnd(&head); 
                break;
            case 3:
                printf("Enter Position to Add: ");
                if (scanf("%d", &pos) != 1) 
                {
                    printf("Invalid input! Please enter a valid position.\n");
                    continue;
                }
                addAtPos(&head, pos);
                break;
            case 4: 
                deleteFromBeg(&head); 
                break;
            case 5: 
                deleteFromEnd(&head); 
                break;
            case 6: 
                printf("Enter Position to Delete: ");
                if (scanf("%d", &pos) != 1) 
                {
                    printf("Invalid input! Please enter a valid position.\n");
                    continue;
                }
                deletePos(&head, pos); 
                break;
            case 7: 
                deleteElement(&head); 
                break;
            case 8:
                freeNodes(&head);
                break;
            case 9: 
                countNodes(&head); 
                break;
            case 10: 
                display(head); 
                break;
            case 11:
                printf("Quitting...\n");
                freeNodes(&head); // Free memory before quitting
                return 0;
            default: 
                printf("Enter a Valid Choice\n");
                break;
        }
    }
    return 0;
}

void addAtBeg(struct patient **q) 
{
    struct patient *temp = (struct patient *)malloc(sizeof(struct patient));
    if (temp == NULL) 
    {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter Patient's Name: ");
    scanf("%19s", temp->name);
    printf("Enter Patient's Age: ");
    scanf("%d", &temp->age);
    printf("Enter Patient's Ward Number: ");
    scanf("%d", &temp->ward_num);
    
    temp->next = *q;
    temp->prev = NULL;

    if (*q != NULL) 
    {
        (*q)->prev = temp; // Correct pointer dereference
    }

    *q = temp; 
}

void addAtEnd(struct patient **q) 
{
    struct patient *temp = (struct patient *)malloc(sizeof(struct patient));
    if (temp == NULL) 
    {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter Patient's Name: ");
    scanf("%19s", temp->name);
    printf("Enter Patient's Age: ");
    scanf("%d", &temp->age);
    printf("Enter Patient's Ward Number: ");
    scanf("%d", &temp->ward_num);
    
    temp->next = NULL;

    if (*q == NULL)
    {  
        temp->prev = NULL;
        *q = temp; 
    } 
    else 
    {
        struct patient *t1 = *q;
        while (t1->next != NULL) 
        {
            t1 = t1->next;
        }
        t1->next = temp;
        temp->prev = t1; 
    }
}

void addAtPos(struct patient **q, int pos) 
{
    if (pos <= 0) 
    {
        printf("Position must be greater than 0.\n");
        return;
    }

    if (pos == 1) 
    {
        addAtBeg(q);
        return;
    }

    struct patient *temp = (struct patient *)malloc(sizeof(struct patient));
    if (temp == NULL) 
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Patient's Name: ");
    scanf("%19s", temp->name);
    printf("Enter Patient's Age: ");
    scanf("%d", &temp->age);
    printf("Enter Patient's Ward Number: ");
    scanf("%d", &temp->ward_num);
    
    struct patient *t1 = *q;
    int counter = 1;

    while (t1 != NULL && counter < pos - 1) 
    {
        t1 = t1->next;
        counter++;
    }

    if (t1 == NULL) 
    {
        printf("Position %d does not exist. Adding at the end instead.\n", pos);
        free(temp);
        addAtEnd(q);
        return;
    }

    temp->next = t1->next;
    temp->prev = t1;
    t1->next = temp;
    if (temp->next != NULL) 
    {
        temp->next->prev = temp;
    }
}

void deleteFromBeg(struct patient **q) 
{
    if (*q == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }
    
    struct patient *temp = *q;
    *q = (*q)->next; // Correct pointer dereference

    if (*q != NULL) 
    {
        (*q)->prev = NULL; // Correct pointer dereference
    }
    free(temp);
}

void deleteFromEnd(struct patient **q) 
{
    if (*q == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }
    
    struct patient *t1 = *q;
    while (t1->next != NULL) 
    {
        t1 = t1->next;
    }

    if (t1->prev != NULL) 
    {
        t1->prev->next = NULL;
    } 
    else 
    {
        *q = NULL; 
    }
    free(t1);
}

void deletePos(struct patient **q, int pos) 
{
    if (*q == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }

    struct patient *t1 = *q;
    int counter = 1;

    if (pos == 1) 
    {
        deleteFromBeg(q);
        return;
    }

    while (t1 != NULL && counter < pos) 
    {
        t1 = t1->next;
        counter++;
    }

    if (t1 == NULL) 
    {
        printf("Position %d does not exist.\n", pos);
        return;
    }

    if (t1->prev != NULL) 
    {
        t1->prev->next = t1->next;
    }
    if (t1->next != NULL) 
    {
        t1->next->prev = t1->prev;
    }
    free(t1);
}

void deleteElement(struct patient **q) 
{
    if (*q == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }

    char name[20];
    printf("Enter Patient's Name to Delete: ");
    scanf("%19s", name);

    struct patient *t1 = *q;
    while (t1 != NULL) 
    {
        if (strcmp(t1->name, name) == 0) 
        {
            if (t1->prev != NULL) 
            {
                t1->prev->next = t1->next;
            } 
            else 
            {
                *q = t1->next;
            }
            if (t1->next != NULL) 
            {
                t1->next->prev = t1->prev;
            }
            free(t1);
            printf("Deleted patient: %s\n", name);
            return;
        }
        t1 = t1->next;
    }
    printf("Patient with name %s not found.\n", name);
}

void countNodes(struct patient **q) 
{
    struct patient *t1 = *q;
    int count = 0;
    
    while (t1 != NULL) 
    {
        count++;
        t1 = t1->next;
    }
    
    printf("Total patients: %d\n", count);
}

void freeNodes(struct patient **q) 
{
    struct patient *current = *q;
    struct patient *next;

    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    *q = NULL;
}

void display(struct patient *p) 
{
    struct patient *t1 = p;
    if (t1 == NULL) 
    {
        printf("The list is empty.\n");
        return;
    }

    while (t1 != NULL) 
    {
        printf("---> Name: %s, Age: %d, Ward Number: %d\n", t1->name, t1->age, t1->ward_num);
        t1 = t1->next;
    }
    printf("\n");
}

