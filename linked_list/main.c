#include <stdio.h>
#include <stdlib.h>
#include "s_linked_list.h"

int main()
{
    struct Node *head = (struct Node*) malloc(sizeof(struct Node)); 
    head->val = (int*) 47;
    addNodeEnd(head, (int*) 521);
    addNodeEnd(head, (int*) 32);
    changeNode(head, 2, (int*) 47);
    printf("%d\n", (int) indexNode(head, 2));
    return 0;
}
