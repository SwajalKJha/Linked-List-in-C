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

struct node *head = NULL;

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
    
    while (1) {
		printf("*************************\n");
		printf(" 1. Add at Beginning\n 2. Add at End\n 3. Add at Position\n 4. Delete from Beginning\n 5. Delete from End\n 6. Delete a Position\n 7. Delete by Element\n 8. Free all Nodes\n 9. Count Nodes\n 10. Display\n 11. Quit\n");
		printf("Enter a choice: ");
		scanf("%d", &choice);
        
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
		        	scanf("%d", &pos);
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
		        	scanf("%d", &pos);
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
    
    if (head == NULL) 
    {
        head = temp;
        temp->next = head;
    } else {
        struct node *t1 = head;
        while (t1->next != head) 
        {
            t1 = t1->next;
        }
        temp->next = head;
        t1->next = temp;
        head = temp;
    }
}

void addAtEnd()
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
    
    if (head == NULL) 
    {
        head = temp;
        temp->next = head;
    } 
    else 
    {
        struct node *t1 = head;
        while (t1->next != head) 
        {
            t1 = t1->next;
        }
        temp->next = head;
        t1->next = temp;
    }
}

void addAtPos(int pos) 
{
    if (pos < 1) 
    {
        printf("Invalid Position!\n");
        return;
    }
    if (head == NULL || pos == 1) 
    {
        addAtBeg();
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

    struct node *t1 = head;
    int counter = 1;
    
    while (t1->next != head && counter < pos - 1) 
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

void deleteFromBeg() 
{
    if (head == NULL) 
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    struct node *t1 = head;
    if (t1->next == head) 
    {
        head = NULL;
    } 
    else 
    {
        struct node *t2 = head;
        while (t2->next != head) 
        {
            t2 = t2->next;
        }
        head = t1->next;
        t2->next = head; 
    }
    free(t1);
    printf("Node Deleted from the List\n");
}

void deleteFromEnd() 
{
    if (head == NULL) 
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    struct node *t1 = head;
    struct node *t2 = NULL;
    
    if (t1->next == head) 
    {
        free(head);
        head = NULL;
    } 
    else 
    {
        while (t1->next != head) 
        {
            t2 = t1;
            t1 = t1->next;
        }
        t2->next = head;
        free(t1);
    }
    printf("Node Deleted from the List\n");
}

void deletePos(int pos)
{
    if (head == NULL)
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }

    if (pos == 1)
    {
        deleteFromBeg();
        return;
    }
    
    struct node *t1 = head;
    struct node *t2 = NULL;
    int counter = 1;

    while (t1->next != head && counter < pos)
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

void deleteElement()
{
    if (head == NULL)
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    char name[20];
    printf("Enter Patient's Name to Delete Record: ");
    scanf("%19s", name);
    
    struct node *t1 = head;
    struct node *t2 = NULL;
    int found = 0;

    do {
        if (strcmp(t1->p.name, name) == 0) 
        {
            found = 1;
            if (t2 == NULL) 
            {
                deleteFromBeg();
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
    } while (t1 != head);

    if (!found) 
    {
        printf("Record does not Exist\n");
    }
}

void freeNodes() 
{
    if (head == NULL) 
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    
    struct node *current = head;
    struct node *nextNode;
    
    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != head);
    
    head = NULL;
    printf("All Nodes Deleted from the List\n");
}

void countNodes() 
{
    if (head == NULL) 
    {
        printf("List is Empty, nothing to Count\n");
        return;
    }

    struct node *t1 = head;
    int count = 0;
    
    do {
        count++;
        t1 = t1->next;
    } while (t1 != head);
    
    printf("Number of Nodes are: %d\n", count);
}

void display() 
{
    if (head == NULL)
    {
        printf("The List is Empty\n");
        return;
    }

    struct node *t1 = head;
    do {
        printf("---> Name: %s, Age: %d, Ward Number: %d ", t1->p.name, t1->p.age, t1->p.ward_num);
        t1 = t1->next;
    } while (t1 != head);
    printf("\n");
}

