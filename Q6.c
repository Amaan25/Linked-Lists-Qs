// Write a program to Sort a Linked List Of Os, Is and 2s.
// Input: 1->1->2->0->2->0->1-> NULL
// Output: 0 -> 0 -> 1 -> 1 -> 1 -> 2 -> 2 -> NULL

#include <stdio.h>
#include <stdlib.h>

typedef enum {FAILURE, SUCCESS} status_code;

typedef struct Node_tag
{
    int data;
    struct Node_tag* next;
} Node;

Node* CreateList (int num);
void TraverseList (Node* lptr);
void DeleteList (Node** lpptr);

Node* sort (Node* lptr)
{
    Node *nptr, *p0, *prev;
    nptr = lptr;
    p0 = NULL;
    prev = NULL;
    while (nptr->data == 0)
    {
        prev = nptr;
        p0 = nptr;
        nptr = nptr->next;
    }
    prev = nptr;
    nptr = nptr->next;
    while (nptr != NULL)
    {
        if (nptr->data == 0)
        {
            prev->next = nptr->next;
            nptr->next = lptr;
            lptr = nptr;
            nptr = prev;
            if (p0 == NULL)
            {
                p0 = lptr;
            }
        }
        else if (nptr->data == 1)
        {
            prev->next = nptr->next;
            if (p0 == NULL)
            {
                nptr->next = lptr;
                lptr = nptr;
            }
            else
            {
                nptr->next = p0->next;
                p0->next = nptr;
            }
            nptr = prev;
        }
        prev = nptr;
        nptr = nptr->next;
    }
    return lptr;
}

void check (Node* lptr)
{
    int flag = 0;
    Node* nptr = lptr;
    while ((nptr != NULL) && (flag == 0))
    {
        if ((nptr->data != 0) && (nptr->data != 1) && (nptr->data != 2))
        {
            flag++;
        }
        nptr = nptr->next;
    }
    if (flag > 0)
    {
        printf("Please enter only 0s, 1s and 2s\n");
    }
    else
    {
        printf("Before sorting: \n");
        TraverseList(lptr);
        lptr = sort (lptr);
        printf("After sorting: \n");
        TraverseList(lptr);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    Node* lptr;
    lptr = CreateList(n);

    check(lptr);
    
    DeleteList(&lptr);
    return 0;
}

status_code InsertAtStart (int d, Node** lpptr)
{
    Node* lptr;
    Node* nptr;
    status_code sc = SUCCESS;
    lptr = *lpptr;
    nptr = (Node*)malloc(sizeof(Node));
    if (nptr == NULL)
    {
        sc = FAILURE;
    }
    else
    {
        nptr->data = d;
        nptr->next = lptr;
        lptr = nptr;
        *lpptr = lptr;
    }
    return sc;
}

Node* CreateList (int num)
{
    int i, x;
    Node* lptr = NULL;
    for (i = 1; i <= num; i++)          //creating a linked list from the end to the start
    {
        scanf("%d", &x);
        InsertAtStart(x, &lptr);
    }
    return lptr;
}

void visit (Node* nptr)
{
    printf("%d->", nptr->data);
}

void TraverseList (Node* lptr)
{
    Node* nptr;
    nptr = lptr;
    while (nptr != NULL)
    {
        visit(nptr);
        nptr = nptr->next;
    }
    printf("NULL\n");
}

status_code DeleteAtStart (int *dptr, Node** lpptr)
{
    Node* lptr = *lpptr;
    status_code sc = SUCCESS;
    Node* nptr = lptr;
    *dptr = lptr->data;
    if (lptr != NULL)
    {
        lptr = lptr->next;
        free(nptr);
        *lpptr = lptr;
    }
    else
    {
        sc = FAILURE;
    }
    return sc;
}

void DeleteList (Node** lpptr)
{
    Node* lptr;
    Node* nptr;
    status_code sc;
    int info;
    lptr = *lpptr;
    nptr = lptr;
    while (lptr != NULL)
    {
        sc = DeleteAtStart(&info, &lptr);
    }
    *lpptr = NULL;
}
