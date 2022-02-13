#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node node;

struct node
{
    struct node *next;
    int data;
};

void addNodeToList(node **list, node *_node)
{
    _node->next = *list;
    *list = _node;
}

void conCatList(node **left, node *right)
{
    while(*left)
        left = &((*left)->next);
    *left = right;
}

node *createNode(int d)
{
    node *new = (node*)malloc(sizeof(node));
    new->data = d;
    new->next = NULL;
    return new; 
}

void printList(node *h)
{
    while(h)
    {
        printf("%d\n", h->data);
        h = h->next;
    }
}

void quickSort(node **head)
{
    if(!(*head))
        return;
    
    node *pivot = *head, *pNext = pivot->next;
    int pValue = pivot->data;
    pivot->next = NULL;

    node *left = NULL, *right = NULL;
    while(pNext)
    {
        node *cur = pNext;
        pNext = pNext->next;
        addNodeToList( pValue > cur->data ? &left : &right, cur);
    }
    // printList(left);
    // printList(right);
    quickSort(&left);
    quickSort(&right);

    *head = NULL;
    conCatList(head, left);
    conCatList(head, pivot);
    conCatList(head, right);
}

int main()
{
    node *head = NULL;

    // srand(time(NULL));
    for(int i=0; i<20; i++)
        addNodeToList(&head, createNode(rand()%200));

    printf("Before sort:\n");
    printList(head);
    quickSort(&head);
    printf("After sort:\n");
    printList(head);

    return 0;
}