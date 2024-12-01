#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient {
    char name[20];
    int age;
    int ward_num;
};

struct node {
    struct patient p;
    struct node *next;
};

void addAtBeg(struct node **);
void addAtEnd(struct node **);
void addAtPos(struct node **,int);
void deleteFromBeg(struct node **);
void deleteFromEnd(struct node **);
void deletePos(struct node **,int);
void deleteElement(struct node **);
void freeNodes(struct node **);
void countNodes(struct node **);
void display(struct node *);

int main()
{
    struct node *head = NULL;
    int choice, pos;
    
    while (1) {
		printf("*************************\n");
		printf(" 1. Add at Beginning\n 2. Add at End\n 3. Add at Position\n 4. Delete from Beginning\n 5. Delete from End\n 6. Delete a Position\n 7. Delete by Element\n 8. Free all Nodes\n 9. Count Nodes\n 10. Display\n 11. Quit\n");
		printf("Enter a choice: ");
		scanf("%d", &choice);
        
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
		        	scanf("%d", &pos);
		        	addAtPos(&head,pos); 
		        	break;
		    case 4: 
		        	deleteFromBeg(&head); 
		        	break;
		    case 5: 
		        	deleteFromEnd(&head); 
		        	break;
		    case 6: 
		       		printf("Enter Position to Delete: ");
		        	scanf("%d", &pos);
		        	deletePos(&head,pos); 
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
		        	return 0;
		    default: 
		        	printf("Enter a Valid Choice\n");
		        	break;
        }
    }
    return 0;
}

void addAtBeg(struct node **q) 
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) 
    {
        printf("Memory Allocation Failed!\n");
        return;
    }
    printf("Enter Patient's Name: ");
    scanf("%19s", temp->p.name);
    printf("Enter Patient's Age: ");
    scanf("%d", &temp->p.age);
    printf("Enter Patient's Ward Number: ");
    scanf("%d", &temp->p.ward_num);
    
    if (*q == NULL) 
    {
        *q = temp;
        temp->next = *q;
    } else {
        struct node *t1 = *q;
        while (t1->next != *q) 
        {
            t1 = t1->next;
        }
        temp->next = *q;
        t1->next = temp;
        *q = temp;
    }
}

void addAtEnd(struct node **q)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) 
    {
        printf("Memory Allocation Failed!\n");
        return;
    }
    printf("Enter Patient's Name: ");
    scanf("%19s", temp->p.name);
    printf("Enter Patient's Age: ");
    scanf("%d", &temp->p.age);
    printf("Enter Patient's Ward Number: ");
    scanf("%d", &temp->p.ward_num);
    
    if (*q == NULL) 
    {
        *q = temp;
        temp->next = *q;
    } 
    else 
    {
        struct node *t1 = *q;
        while (t1->next != *q) 
        {
            t1 = t1->next;
        }
        temp->next = *q;
        t1->next = temp;
    }
}

void addAtPos(struct node **q, int pos) 
{
    if (pos < 1) 
    {
        printf("Invalid Position!\n");
        return;
    }
    if (*q == NULL || pos == 1) 
    {
        addAtBeg(q);
        return;
    }
    
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) 
    {
        printf("Memory Allocation Failed!\n");
        return;
    }
    printf("Enter Patient's Name: ");
    scanf("%19s", temp->p.name);
    printf("Enter Patient's Age: ");
    scanf("%d", &temp->p.age);
    printf("Enter Patient's Ward Number: ");
    scanf("%d", &temp->p.ward_num);

    struct node *t1 = *q;
    int counter = 1;
    
    while (t1->next != *q && counter < pos - 1) 
    {
        t1 = t1->next;
        counter++;
    }
    if (counter < pos - 1)
    {
        printf("Position exceeded the current list size, Inserting at the end.\n");
    }
    temp->next = t1->next;
    t1->next = temp;
}

void deleteFromBeg(struct node **q) 
{
    if (*q == NULL) 
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    struct node *t1 = *q;
    if (t1->next == *q) 
    {
        *q = NULL;
    } 
    else 
    {
        struct node *t2 = *q;
        while (t2->next != *q) 
        {
            t2 = t2->next;
        }
        *q = t1->next;
        t2->next = *q; 
    }
    free(t1);
    printf("Node Deleted from the List\n");
}

void deleteFromEnd(struct node **q) 
{
    if (*q == NULL) 
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    struct node *t1 = *q;
    struct node *t2 = NULL;
    
    if (t1->next == *q) 
    {
        free(*q);
        *q = NULL;
    } 
    else 
    {
        while (t1->next != *q) 
        {
            t2 = t1;
            t1 = t1->next;
        }
        t2->next = *q;
        free(t1);
    }
    printf("Node Deleted from the List\n");
}

void deletePos(struct node **q, int pos)
{
    if (*q == NULL)
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }

    if (pos == 1)
    {
        deleteFromBeg(q);
        return;
    }
    
    struct node *t1 = *q;
    struct node *t2 = NULL;
    int counter = 1;

    while (t1->next != *q && counter < pos)
    {
        t2 = t1;
        t1 = t1->next;
        counter++;
    }

    if (counter < pos) 
    {
        printf("Position %d does not Exist\n", pos);
        return;
    }

    t2->next = t1->next;
    free(t1);
    printf("Node Deleted from the List\n");
}

void deleteElement(struct node **q)
{
    if (*q == NULL)
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    char name[20];
    printf("Enter Patient's Name to Delete Record: ");
    scanf("%19s", name);
    
    struct node *t1 = *q;
    struct node *t2 = NULL;
    int found = 0;

    do {
        if (strcmp(t1->p.name, name) == 0) 
        {
            found = 1;
            if (t2 == NULL) 
            {
                deleteFromBeg(q);
            } 
            else 
            {
                t2->next = t1->next; 
                free(t1);
                printf("Node Deleted from the List\n");
            }
            return;
        }
        t2 = t1;
        t1 = t1->next;
    } while (t1 != *q);

    if (!found) 
    {
        printf("Record does not Exist\n");
    }
}

void freeNodes(struct node **q) 
{
    if (*q == NULL) 
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    struct node *current = *q;
    struct node *nextNode;
    
    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != *q);
    
    *q = NULL;
    printf("All Nodes Deleted from the List\n");
}

void countNodes(struct node **q) 
{
    if (*q == NULL) 
    {
        printf("List is Empty, nothing to Count\n");
        return;
    }

    struct node *t1 = *q;
    int count = 0;
    
    do {
        count++;
        t1 = t1->next;
    } while (t1 != *q);
    
    printf("Number of Nodes are: %d\n", count);
}

void display(struct node *p) 
{
    if (p == NULL)
    {
        printf("The List is Empty\n");
        return;
    }

    struct node *t1 = p;
    do {
        printf("---> Name: %s, Age: %d, Ward Number: %d ", t1->p.name, t1->p.age, t1->p.ward_num);
        t1 = t1->next;
    } while (t1 != p);
    printf("\n");
}

