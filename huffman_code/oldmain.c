// TODO:
    // build binary tree from array of Node's
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

typedef struct Node
{
    char c;
    int freq;
    struct Node* left;
    struct Node* right;
} Node;

void usage(const char* arg0);
// counts the frequency of each ASCII character
// and stores it in a 256-long array of Node's
// to set up for the binary tree
Node* freqs(char text[]);
int cmpfreqs(const void* a, const void* b);

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        usage(argv[0]);
        return 0;
    }

    int infd, outfd;
    int newsize = 0;
    char* buffer = NULL;
    off_t size;
    Node tmp, *chart = NULL;

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
        chart = freqs(buffer);
        qsort(chart, 256, sizeof(*chart), cmpfreqs);
        for (int i = 0; i < 256; i++)
        {
            if (chart[i].freq != 0)
                newsize++;
            else break;
        }

        // for testing
        for (int i = 0; i < newsize; i++)
            printf("%c\t%d\n", chart[i].c, chart[i].freq);

        // TODO: generate the binary tree
        for (i = newsize; i < 256; i++) // zeros out the rest
            chart[i] = NULL;
    } else if (strcmp(argv[1], "-d") == 0)
    {
        // TODO: decode the text
    } else {
        usage(argv[0]);
        return 0;
    }

    // close(outfd);
    return 0;
}

void usage(const char* arg0)
{
    printf("USAGE: %s [flags] [input filename] [output filename]\n", arg0);
    printf("Flags:\n-e\tencodes the input file\n-d\tdecodes the input file\n");
    printf("Flags are required\nThe resulting file is saved as [output filename]\n");
    printf("NOTE: both files must be in .txt format\n");
}

Node* freqs(char text[])
{
    Node* chars = (Node*) malloc(sizeof(Node)*256);
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
    return chars;
}

int cmpfreqs(const void* a, const void* b)
{
    const Node x = *(const Node*) a;
    const Node y = *(const Node*) b;
    return (x.freq < y.freq) - (x.freq > y.freq);
}