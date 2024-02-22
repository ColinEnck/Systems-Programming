struct table
{
    void* key;
    void* val;
    struct table* next;
};

// adds a key-value pair to the table
int tableAdd(struct table* head, void* key, void* val)
{
    if (head == NULL)
        return -1;
    struct table* current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = (struct table*) malloc(sizeof(struct table));
    if (current->next == NULL)
        return -1;
    current->next->key = key;
    current->next->val = val;
    current->next->next = NULL;
}

// fetches the value based on the key
// uses the user-defined function 'cmp' to define how to match the keys
// the cmp function should return 0 if there isn't a match and 1 if there is
void* tableFetch(struct table* head, void* key, int (*cmp)(void*, void*))
{
    if (head == NULL)
        return (int*) -1;
    struct table* current = head;
    while (current != NULL)
    {
        if ((*cmp)(current->key, key))
            return current->val;
        current = current->next;
    }
    return (int*) -1;
}
