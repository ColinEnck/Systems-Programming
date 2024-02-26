/*
USAGE: ./[exec] flags [input filename] [output filename]
flags:
-e  encodes the input file
-d  decodes the input file
Flags are required
The resulting file is saved as [output filename]
NOTE: both files must be in a .txt format
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "s_linked_list.h"

typedef struct Leaf
{
    char c;
    int freq;
    struct Node* left;
    struct Node* right;
} Leaf;

void usage(const char* arg0);
// returns a linked list of sorted Leafs
struct Node *freqs(char text[]);
//Leaf *buildTree(struct Node *head);
int cmpfreqs(const void* a, const void* b);
// cmp for linked list
int cmpll(void *a, void *b);

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        usage(argv[0]);
        return 0;
    }

    int infd, outfd;
    char* buffer = NULL;
    off_t size;
    Leaf *temp, *chart = NULL;
    struct Node *head;

    if ((infd = open(argv[2], O_RDONLY)) == -1)
    {   
        perror("Error opening input file");
        return 0;
    }
    if ((outfd = open(argv[3], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
    {
        perror("Error opening output file");
        return 0;
    }

    if ((size = lseek(infd, 0, SEEK_END)) == -1)
    {
        perror("Error reading size of input file");
        return 0;
    }
    // reset the fdin to the beginning of the file
    lseek(infd, 0, SEEK_SET);

    buffer = malloc((long) size);
    if (read(infd, buffer, size) == -1)
    {
        perror("Error reading from input file");
        return 0;
    }
    close(infd);

    if (strcmp(argv[1], "-e") == 0)
    {
        head = freqs(buffer);

        // testing
        //temp = (Leaf*) malloc(sizeof(Leaf));
        //temp->c = 'G';
        //temp ->freq = 6;
        //sortNode(head, temp, cmpll);

        // for testing
        for (int i = 0; (temp = (Leaf*) indexNode(head, i)) != NULL; i++)
        {
            printf("%c\t%d\n", temp->c, temp->freq);
        }
    } else if (strcmp(argv[1], "-d") == 0)
    {
        // TODO: decode the text
    } else {
        usage(argv[0]);
        return 0;
    }

    close(outfd);
    return 0;
}

void usage(const char* arg0)
{
    printf("USAGE: %s [flags] [input filename] [output filename]\n", arg0);
    printf("Flags:\n-e\tencodes the input file\n-d\tdecodes the input file\n");
    printf("Flags are required\nThe resulting file is saved as [output filename]\n");
    printf("NOTE: both files must be in .txt format\n");
}

struct Node* freqs(char text[])
{
    int newsize = 0;
    struct Node *head;

    Leaf* chars = (Leaf*) malloc(sizeof(Leaf)*256);
    // sets the priority queue in ascending ASCII codes
    for (int i = 0; i < 256; i++)
    {
        chars[i].c = i;
        chars[i].freq = 0;
        chars[i].left = NULL;
        chars[i].right = NULL;
    }

    for (int cursor = 0; text[cursor] != '\0'; cursor++)
        for (int c = 0; c < 256; c++)
            if (text[cursor] == c)
            {
                chars[c].freq++;
                break;
            }

    // TODO: remove the sorting before-hand, probably not needed
    qsort(chars, 256, sizeof(*chars), cmpfreqs);
    for (int i = 0; i < 256; i++)
    {
        if (chars[i].freq != 0)
            newsize++;
        else break;
    }

    head = (struct Node*) malloc(sizeof(struct Node));
    head->val = NULL;
    head->next = NULL;
    for (int i = 0; i < newsize; i++)
        addNodeEnd(head, &chars[i]);
      
    return head;
}

//Leaf *buildTree(struct Node *head)
//{
//    
//}

int cmpfreqs(const void* a, const void* b)
{
    const Leaf x = *(const Leaf*) a;
    const Leaf y = *(const Leaf*) b;
    return (x.freq < y.freq) - (x.freq > y.freq);
}

int cmpll(void *a, void *b)
{
    Leaf x = *(Leaf*) a;
    Leaf y = *(Leaf*) b;
    return (x.freq >= y.freq);
}
