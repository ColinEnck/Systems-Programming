#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable_test.h"
#include "hashtable.h"

int cmpstring(void* a, void* b);

int main()
{
    // this is all for testing
    struct table* head = (struct table*) malloc(sizeof(struct table));
    head->key = "Hi there!";
    head->val = 47;
    head->next = (struct table*) malloc(sizeof(struct table));
    struct table* second = head->next;
    second->key = "Hi again!";
    second->val = 521;
    second->next = NULL;
    //printTable_test(head);
    //tableAdd_test(head, "Why it's me again!", 7);
    //printTable_test(head);
    //printf("\nFetched: %d\n", tableFetch_test(head, "Hi there!"));

    int ret = (int) tableFetch(head, "Hi there!", cmpstring);
    printf("%d\n", ret);
    
    return 0;
}

int cmpstring(void* a, void* b)
{
    if (strcmp((char*) a, (char*) b) == 0)
        return 1;
    else return 0;
}
