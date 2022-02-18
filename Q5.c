// Write a program to find the maximum distance (maximum number of nodes between two consecutive peaks) between two consecutive peaks of a LL. The peak node contains a value greater than that of its neighbour nodes.

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

int maxpeakdist (Node* lptr)
{
    int max = 0, dist = 0, peaks = 0;
    if (listlen(lptr) < 5)
    {
        printf("Length of list must be greater than 4\n");
    }
    else
    {
        Node *nptr, *prev;
        prev = lptr;
        nptr = lptr->next;
        while (nptr->next != NULL)
        {
            if ((nptr->data > prev->data) && (nptr->data > (nptr->next)->data))
            {
                peaks++;
                if (dist > max)
                {
                    max = dist;
                }
                dist = 0;
            }
            else
            {
                if (peaks > 0)
                {
                    dist++;
                }
            }
            prev = prev->next;
            nptr = nptr->next;
        }
    }
    return max;
}

int main()
{
    int n;
    scanf("%d", &n);
    Node* lptr;
    lptr = CreateList(n);

    int max = maxpeakdist(lptr);
    if (max == 0)
    {
        printf("There are no consecutive peaks\n");
    }
    else
    {
        printf("Maximum number of nodes between two consecutive peaks in the list is %d\n", max);
    }

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
