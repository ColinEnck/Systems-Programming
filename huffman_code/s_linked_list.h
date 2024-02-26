struct Node 
{
    void *val;
    struct Node *next;
};

int addNodeEnd(struct Node *head, void *val)
{
    if (head == NULL)
        return -1;
    struct Node *current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = (struct Node*) malloc(sizeof(struct Node));
    if (current->next == NULL)
        return -1;
    current->next->val = val;
    current->next->next = NULL;
    return 0;
}

int changeNode(struct Node *head, int index, void *val)
{
    if (head == NULL)
        return -1;
    struct Node *current = head;
    // add 1 to index because head is NULL
    for (int i = 0; i < index+1; i++)
        current = current->next;
    current->val = val;
    return 0;
}

void* indexNode(struct Node *head, int index)
{
    if (head == NULL)
        return (int*) -1;
    struct Node* current = head;
    // add 1 to index because head is NULL
    for (int i = 0; i < index+1; i++)
        current = current->next;
    if (current == NULL)
        return NULL;
    return current->val;
}

int insertNode(struct Node *head, int index, void *val)
{
    if (head == NULL)
        return -1;
    void *temp1, *temp2;
    int i = index;
    temp1 = indexNode(head, i);
    changeNode(head, i, val);
    for (;;) {
        i += 1;
        if ((temp2 = indexNode(head, i)) == NULL)
            break;
        changeNode(head, i, temp1);
        i += 1;
        if ((temp1 = indexNode(head, i)) == NULL)
            break;
        changeNode(head, i, temp2);
    }
    return 0;
}

// sorts a new element into a sorted list greatest to least
// returns the new index of the given element
// given cmp function should return 1 if the val is less than the
// linked list element (i.e. 1 if it should continue traversing the list)
// the first arg is the linked list element, the second is the supplied new one
int sortNode(struct Node *head, void *val, int (*cmp)(void*, void*))
{
    if (head == NULL)
        return -1;
    void *temp;
    int i;
    for (i = 0; (temp = indexNode(head, i)) != NULL && (*cmp)(temp, val); i++);
    changeNode(head, i, val);
}
