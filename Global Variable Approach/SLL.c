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
 		printf("Quiting...\n");
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
    
    temp->next = head;
    head = temp;
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
    
    temp->next = NULL;

    if (head == NULL)
    {  
        head = temp;
    } 
    else
    {
        struct node *t1 = head;
        while (t1->next != NULL)
        {
            t1 = t1->next;
        }
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
    while (t1->next != NULL && counter < pos - 1)
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
	struct node *t1 = head;
	head = t1->next;
	free(t1);
	printf("Node Deleted from the List\n");
}

void deleteFromEnd()
{
	struct node *t1 = head;
	struct node *t2 = NULL;
	
	while(t1->next != NULL)
	{
		t2 = t1;
		t1 = t1->next;
	}
	
	free(t1);
	t2->next = NULL;
	printf("Node Deleted from the List\n");
} 

void deletePos(int pos)
{
    if (head == NULL)
    {
        printf("List is Empty, nothing to Delete\n");
        return;
    }

    struct node *t1 = head;
    struct node *t2 = NULL;

    if (pos == 1)
    {
        head = t1->next;
        free(t1);
        return;
    }

    int counter = 1;
    while (t1 != NULL && counter < pos)
    {
        t2 = t1;
        t1 = t1->next;
        counter++;
    }

    if (t1 == NULL)
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
        printf("List is Empty, nothing to Delete\n");
        return;
    }
    char name[20];
    getchar();
    printf("Enter Patient's Name to Delete Record: ");
    scanf("%19s", name);
    getchar();
    
    struct node *t1 = head;
    struct node *t2 = NULL;
    
    while (t1 != NULL)
    {
    	if (strcmp(t1->p.name, name) == 0)
	    {	
	    	if(t2 == NULL)
	    	{	
	    		head = t1->next;
	    		free(t1);
			printf("Node Deleted from the List\n");
	    	}
		else
		{    
			t2->next = t1->next;
			free(t1);
			printf("Node Deleted from the List\n");
	    	}
	    }
    	t2 = t1;
        t1 = t1->next;
    }
    if (t1 == NULL)
    {
        printf("Record does not Exist\n");
        return;
    }
}
void freeNodes()
{
    if (head == NULL)
    {
        printf("List is Empty, nothing to delete\n");
        return;
    }
    struct node *t1 = head;
    
    int counter = 1;
    while (t1 != NULL)
    {
    	struct node *t2 = head;
    	head = t1->next;
        t1 = t1->next;
        free(t2);
        counter++;
    }
    printf("All Nodes Deleted from the List\n");
    
}
void countNodes()
{
    if (head == NULL)
    {
        printf("List is Empty, nothing to Delete\n");
        return;
    }
    struct node *t1 = head;

    int counter = 1;
    while (t1 != NULL)
    {
        t1 = t1->next;
        counter++;
    }
    
    printf("Number of Nodes are: %d\n", counter-1);
}
void display()
{
    struct node *t1 = head;
    if (t1 == NULL)
    {
        printf("The List is Empty\n");
        return;
    }
    while (t1 != NULL)
    {
        printf("---> Name: %s, Age: %d, Ward Number: %d ", t1->p.name, t1->p.age, t1->p.ward_num);
        t1 = t1->next;
    }
    printf("\n");
}
