struct Node 
{
    void *val;
    struct Node *next;
};

int addNodeEnd(struct Node *head, void *val)
{
    if (head == NULL)
        return -1;
    struct Node* current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = (struct Node*) malloc(sizeof(struct Node));
    if (current->next == NULL)
        return -1;
    current->next->val = val;
    current->next->next = NULL;
    return 0;
}

int changeNode(struct Node *head, int index, void* val)
{
    if (head == NULL)
        return -1;
    struct Node* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    current->val = val;
    return 0;
}

void* indexNode(struct Node *head, int index)
{
    if (head == NULL)
        return (int*) -1;
    struct Node* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current->val;
}
