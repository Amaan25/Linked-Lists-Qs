// Write a recursive function to display a Singly Linked List in reverse order

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

void reverse (struct node* p)
{
    if (p->next != NULL)
    {
        reverse_print (p->next);
    }
    printf("%d ", p->data);
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

    reverse_print (lptr);
    
    nptr = lptr;
    for (i = 1; i <= n; i++)
    {
        lptr = lptr->next;
        free(nptr);
        nptr = lptr;
    }

    return 0;
}
