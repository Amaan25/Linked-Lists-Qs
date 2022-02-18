// For a given linked list, find the middle element of the node, and if there are an even number of elements, there exists a situation when there exist two middle elements, then out of the two nodes return the maximum of two nodes.
//  Sample Input: [1,2,3,4,5,6]
//  Sample Output: 4

#include <stdio.h>
#include <stdlib.h>

typedef enum {FAILURE, SUCCESS} status_code;

typedef struct Node_tag
{
    int data;
    struct Node_tag* next;
} Node;

Node* CreateList (int num);
void DeleteList (Node** lpptr);

int listlen(Node* lptr)
{
    int len = 0;
    Node* nptr = lptr;
    while (nptr != NULL)
    {
        nptr = nptr->next;
        len++;
    }
    return len;
}

int fetchdata (Node* lptr, int n)
{
    Node* nptr;
    nptr = lptr;
    n--;
    while (n != 0)
    {
        nptr = nptr->next;
        n--;
    }
    return nptr->data;
}

int midelmnt (Node* lptr)
{
    int val, len;
    len = listlen(lptr);
    if (len%2 == 0)
    {
        if (fetchdata(lptr, len/2) > fetchdata(lptr, len/2 +1))
        {
            val = fetchdata(lptr, len/2);
        }
        else
        {
            val = fetchdata(lptr, len/2 + 1);
        }
    }
    else
    {
        val = fetchdata(lptr, len/2 + 1);
    }
    return val;
}


int main()
{
    int n;
    scanf("%d", &n);
    Node* lptr;
    lptr = CreateList(n);

    printf("Required element is %d\n", midelmnt(lptr));

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
