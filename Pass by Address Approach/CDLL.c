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
                if (scanf("%d", &pos) != 1) {
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

    if (*q == NULL) 
    {
        // List is empty
        temp->next = temp;
        temp->prev = temp;
    } else {
        temp->next = *q;
        temp->prev = (*q)->prev;
        (*q)->prev->next = temp;
        (*q)->prev = temp;
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

    if (*q == NULL) 
    {
        // List is empty
        temp->next = temp;
        temp->prev = temp;
    } else {
        temp->next = *q;
        temp->prev = (*q)->prev;
        (*q)->prev->next = temp;
        (*q)->prev = temp;
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

    while (t1->next != *q && counter < pos - 1) 
    {
        t1 = t1->next;
        counter++;
    }

    if (counter == pos - 1) 
    {
        temp->next = t1->next;
        temp->prev = t1;
        t1->next->prev = temp;
        t1->next = temp;
    } else {
        printf("Position %d does not exist. Adding at the end instead.\n", pos);
        free(temp);
        addAtEnd(q);
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
    if (temp->next == *q) 
    {
        // Only one node in the list
        *q = NULL;
    } else {
        *q = temp->next;
        (*q)->prev = temp->prev;
        temp->prev->next = *q;
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
    
    struct patient *t1 = (*q)->prev;

    if (t1 == *q) 
    {
        // Only one node in the list
        free(*q);
        *q = NULL;
    } 
    else 
    {
        t1->prev->next = *q;
        (*q)->prev = t1->prev;
        free(t1);
    }
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

    while (t1->next != *q && counter < pos) 
    {
        t1 = t1->next;
        counter++;
    }

    if (counter == pos) 
    {
        t1->prev->next = t1->next;
        t1->next->prev = t1->prev;
        if (t1 == *q) 
        {
            *q = t1->next; // Adjust head if needed
        }
        free(t1);
    } 
    else 
    {
        printf("Position %d does not exist.\n", pos);
    }
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
    do {
        if (strcmp(t1->name, name) == 0) 
        {
            if (t1->prev != NULL) 
            {
                t1->prev->next = t1->next;
            }
            if (t1->next != NULL) 
            {
                t1->next->prev = t1->prev;
            }
            if (t1 == *q) 
            {
                *q = t1->next; // Adjust head if needed
            }
            free(t1);
            printf("Deleted patient: %s\n", name);
            return;
        }
        t1 = t1->next;
    } while (t1 != *q);
    printf("Patient with name %s not found.\n", name);
}

void countNodes(struct patient **q) 
{
    struct patient *t1 = *q;
    int count = 0;

    if (t1 == NULL) 
    {
        printf("Total patients: %d\n", count);
        return;
    }

    do {
        count++;
        t1 = t1->next;
    } while (t1 != *q);

    printf("Total patients: %d\n", count);
}

void freeNodes(struct patient **q) 
{
    struct patient *current = *q;
    if (current == NULL) return;

    struct patient *next;
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != *q);
    
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

    do {
        printf("---> Name: %s, Age: %d, Ward Number: %d\n", t1->name, t1->age, t1->ward_num);
        t1 = t1->next;
    } while (t1 != p);
    printf("\n");
}

