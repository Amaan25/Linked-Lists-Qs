#include <stdio.h>
#include <stdlib.h>

typedef struct Node_tag
{
    int num;
    int size;
    int in_heap;
    int rc;
    int mark;
    int n;
    struct Node_tag* next[3];
}Node;

Node* create_new_node (int i, int s)
{
    Node* nn;
    nn = (Node*) malloc(sizeof(Node));
    nn->num = i;
    nn->size = s;
    nn->in_heap = 1;
    nn->rc = 0;
    nn->mark = 0;
    nn->n = 0;
    nn->next[0] = NULL;
    nn->next[1] = NULL;
    nn->next[2] = NULL;
    return nn;
}

int mat[10][10];
Node* arr[10];

void create_hm_scheme (void)
{
    for (int i = 0; i < 10; i++)
    {
        arr[i] = create_new_node(i+1, 100);
        if (i == 3 || i == 5)
        {
            arr[i]->in_heap = 0;
        }
    }
    
    //Linking
    arr[0]->n = 3;
    arr[0]->next[0] = arr[1];
    arr[0]->next[1] = arr[8];
    arr[0]->next[2] = arr[9];

    arr[2]->n = 2;
    arr[2]->next[0] = arr[7];
    arr[2]->next[1] = arr[9];

    arr[4]->n = 1;
    arr[4]->next[0] = arr[0];

    arr[6]->n = 2;
    arr[6]->next[0] = arr[0];
    arr[6]->next[1] = arr[7];

    arr[7]->n = 1;
    arr[7]->next[0] = arr[8];
}

void count_references (void)
{
    for (int i = 0; i < 10; i++)
    {
        if (arr[i]!=NULL && arr[i]->n > 0 && arr[i]->in_heap)
        {
            for (int j = 0; j < arr[i]->n; j++)
            {
                (arr[i]->next[j])->rc++;
            }
        }
    }
}

void rc_method (Node* root)
{
    int m = 0;
    for (int i = 0; i < 10; i++)
    {
        if (arr[i] == root)
        {
            arr[i]->rc++;
        }
        if (arr[i]!=NULL && arr[i]->rc == 0 && arr[i]->in_heap)
        {
            for (int j = 0; j < arr[i]->n; j++)
            {
                (arr[i]->next[j])->rc--;
            }
            printf("Node %d is no longer required\n", arr[i]->num);
            m += arr[i]->size;
            free(arr[i]);
            arr[i] = NULL;
        }
    }
    root->rc--;
    printf("Total memory freed: %d bytes\n", m);
}

void mark(Node* root)
{
    Node* head = root;
    Node* tail = NULL;
    Node* middle = NULL;
    while(head != NULL)
    {
        if(!head->mark)
        {
            head->mark= 1;
            printf("Node %d is marked\n", head->num);
        }
        if(head->next[0] != NULL && !head->next[0]->mark)
        {
            tail = middle;
            middle = head;
            head = head->next[0];
        }
        else if(head->next[1] != NULL && !head->next[1]->mark)
        {
            tail = middle;
            middle = head;
            head = head->next[1];
        }
        else if(head->next[2] != NULL && !head->next[2]->mark)
        {
            tail = middle;
            middle = head;
            head = head->next[2];
        }
        else
        {
            head = middle;
            middle = tail;
            tail = NULL;
        }
    }
}

void sweep(void)
{
    int m = 0;
    for(int i = 0; i < 10; i++)
    {
        if(arr[i]!=NULL && arr[i]->in_heap)
        {
            if(!arr[i]->mark)
            {
                printf("Node %d is no longer required\n", arr[i]->num);
                m += arr[i]->size;
                free(arr[i]);
                arr[i]=NULL;
            }
        }
    }
    printf("Total memory freed: %d bytes\n", m);
}

void unmark_all (void)
{
    for (int i = 0; i < 10; i++)
    {
        if (arr[i] != NULL)
        {
            arr[i]->mark = 0;
        }
    }
}

void initialise_matrix (void)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            mat[i][j] = 0;
        }
    }
}

void adj_matrix (Node* root)
{
    if (root->n > 0)
    {
        for (int i = 0; i < root->n; i++)
        {
            mat[root->num - 1][root->next[i]->num - 1] = 1;
            mat[root->next[i]->num - 1][root->num - 1] = 1;
            adj_matrix(root->next[i]);
        }
    }
}

void print_matrix (void)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void delete_hm_scheme (Node** arr)
{
    for (int i = 0; i < 10; i++)
    {
        if (arr[i] != NULL)
        {
            free(arr[i]);
        }
    }
}

int main()
{
    create_hm_scheme();
    
    Node* root1, *root2;
    root1 = arr[4];
    root2 = arr[0];
    
    int c;
    printf("Enter 1 for Reference count method, 2 for Mark and Sweep method: ");
    scanf("%d", &c);
    if (c == 1)
    {
        count_references();
        rc_method(root1);
        initialise_matrix();
        adj_matrix(root1);
        print_matrix();
        
        count_references();
        rc_method(root2);
        initialise_matrix();
        adj_matrix(root2);
        print_matrix();
    }
    else
    {
        mark(root1);
        sweep();
        initialise_matrix();
        adj_matrix(root1);
        print_matrix();

        unmark_all();
        
        mark(root2);
        sweep();
        initialise_matrix();
        adj_matrix(root2);
        print_matrix();
    }
    delete_hm_scheme(arr);
    return 0;
}
