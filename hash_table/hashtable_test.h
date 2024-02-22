#include <string.h>

struct table_t
{
    char* key;
    unsigned int val;
    struct table_t* next;
};

int tableAdd_test(struct table_t* head, char* key, unsigned int val)
{
    if (head == NULL)
        printf("Error: head pointer was NULL\n");
        return -1;
    struct table_t* current = head;
    while (current->next != NULL)
        current = current->next;
    current->next = (struct table_t*) malloc(sizeof(struct table_t));
    if (current->next == NULL)
        return -1;
    current->next->key = key;
    current->next->val = val;
    current->next->next = NULL;
}

int printTable_test(struct table_t* head)
{
    if (head == NULL)
    {
        printf("Error: head pointer was NULL\n");
        return -1;
    }
    struct table_t* current = head;
    while (current != NULL)
    {
        printf("%s, %d\n", current->key, current->val);
        current = current->next;
    }
    return 0;
}

int tableFetch_test(struct table_t* head, char* key)
{
    if (head == NULL)
    {
        printf("Error: head pointer was NULL\n");
        return -1;
    }
    struct table_t* current = head;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
            return current->val;
        current = current->next;
    }
    return -1;
}
