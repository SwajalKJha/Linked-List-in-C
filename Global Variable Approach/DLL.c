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

struct patient *head = NULL;

void addAtBeg();
void addAtEnd();
void addAtPos(int);
void deleteFromBeg();
void deleteFromEnd();
void deletePos(int);
void deleteElement();
void freeNodes();
void countNodes();
void display();

int main() 
{
    int choice, pos;
    
    while (1) 
    {
        printf("*************************\n");
        printf(" 1. Add at Beginning\n 2. Add at End\n 3. Add at Position\n 4. Delete from Beginning\n 5. Delete from End\n 6. Delete a Position\n 7. Delete by Element\n 8. Free all Nodes\n 9. Count Nodes\n 10. Display\n 11. Quit\n"); 
        printf("Enter a choice: ");
        scanf("%d", &choice);
        
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) 
        {
            case 1: 
                addAtBeg(); 
                break;
            case 2: 
                addAtEnd(); 
                break;
            case 3: 
                printf("Enter Position to Add: ");
                if (scanf("%d", &pos) != 1) 
                {
                    printf("Invalid input! Please enter a valid position.\n");
                    continue;
                }
                addAtPos(pos);
                break;
            case 4: 
                deleteFromBeg(); 
                break;
            case 5: 
                deleteFromEnd(); 
                break;
            case 6: 
                printf("Enter Position to Delete: ");
                if (scanf("%d", &pos) != 1) 
                {
                    printf("Invalid input! Please enter a valid position.\n");
                    continue;
                }
                deletePos(pos); 
                break;
            case 7: 
                deleteElement(); 
                break;
            case 8:
                freeNodes();
                break;
            case 9: 
                countNodes(); 
                break;
            case 10: 
                display(); 
                break;
            case 11:
                printf("Quitting...\n");
                return 0;
            default: 
                printf("Enter a Valid Choice\n");
                break;
        }
    }
    return 0;
}

void addAtBeg() 
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
    
    temp->next = head;
    temp->prev = NULL;
    
    if (head != NULL) 
    {
        head->prev = temp;
    }
    
    head = temp; 
}

void addAtEnd() 
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

    if (head == NULL)
    {  
        temp->prev = NULL;
        head = temp; 
    } 
    else 
    {
        struct patient *t1 = head;
        while (t1->next != NULL) 
        {
            t1 = t1->next;
        }
        t1->next = temp;
        temp->prev = t1; 
    }
}

void addAtPos(int pos) 
{
    if (pos <= 0) 
    {
        printf("Position must be greater than 0.\n");
        return;
    }

    if (pos == 1) 
    {
        addAtBeg();
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
    
    struct patient *t1 = head;
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
        addAtEnd();
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

void deleteFromBeg() 
{
    if (head == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }
    
    struct patient *temp = head;
    head = head->next;
    
    if (head != NULL) 
    {
        head->prev = NULL;
    }
    free(temp);
}

void deleteFromEnd() 
{
    if (head == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }
    
    struct patient *t1 = head;
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
        head = NULL; 
    }
    free(t1);
}

void deletePos(int pos) 
{
    if (head == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }

    struct patient *t1 = head;
    int counter = 1;

    if (pos == 1) 
    {
        deleteFromBeg();
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

void deleteElement() 
{
    if (head == NULL) 
    {
        printf("The list is empty, nothing to delete.\n");
        return;
    }

    char name[20];
    printf("Enter Patient's Name to Delete: ");
    scanf("%19s", name);

    struct patient *t1 = head;
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
                head = t1->next;
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

void countNodes() 
{
    struct patient *t1 = head;
    int count = 0;
    
    while (t1 != NULL) 
    {
        count++;
        t1 = t1->next;
    }
    
    printf("Total patients: %d\n", count);
}

void freeNodes() 
{
    struct patient *current = head;
    struct patient *next;
    
    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

void display() 
{
    struct patient *t1 = head;
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

