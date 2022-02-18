// Write a program to move the last element of a singly linked list to the front of the list. Display the modified list.

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

void display (struct node* p)
{
    printf("%d ", p->data);
    if (p->next != NULL)
    {
        display (p->next);
    }
}

struct node* last_to_first (struct node* p)
{
    struct node* first, *prev;
    first = p;
    prev = NULL;
    
    while (p->next != NULL)
    {
        prev = p;
        p = p->next;
    }
    
    if (prev != NULL)
    {
        prev->next = NULL;
    }
    p->next = first;
    
    display(p);
    return p;
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
    
    lptr = last_to_first(lptr);
    
    nptr = lptr;
    for (i = 1; i <= n; i++)
    {
        lptr = lptr->next;
        free(nptr);
        nptr = lptr;
    }

    return 0;
}
