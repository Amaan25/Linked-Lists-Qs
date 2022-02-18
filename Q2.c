// Write a program to print the nth node from the end of a Singly Linked List

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

int list_length (struct node* p)
{
    int length = 0;
    
    while (p->next != NULL)
    {
        length++;
        p = p->next;
    }
    length++;
    
    return length;
}

void nth_node_from_end(struct node* q)
{
    int n;
    scanf("%d", &n);
    n = list_length(q) - n;

    while (n != 0)
    {
        n--;
        q = q->next;
    }
    printf("%d\n", q->data);
}


int main()
{
    int n, i, x;
    scanf("%d", &n);
    struct node* nptr, *lptr;
    lptr = NULL;
    for (i = 1; i <= n; i++)        //creating a linked list from the end to the start
    {
        nptr = (struct node*)malloc(sizeof(struct node));
        scanf("%d", &x);
        nptr->data = x;
        nptr->next = lptr;
        lptr = nptr;
    }
    
    nth_node_from_end(lptr);
    
    nptr = lptr;

    for (i = 1; i <= n; i++)
    {
        lptr = lptr->next;
        free(nptr);
        nptr = lptr;
    }

    return 0;
}
