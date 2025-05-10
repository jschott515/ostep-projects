#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_INPUT 1
#define ARG_OUTPUT 2

int reverse(FILE* fin, FILE* fout);


int main(int argc, char** argv)
{
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    FILE *fin = stdin;
    FILE *fout = stdout;

    if (argc > 1)
    {
        fin = fopen(argv[ARG_INPUT], "r");
        if (!fin)
        {
            fprintf(stderr, "error: cannot open file %s\n", argv[ARG_INPUT]);
            exit(1);
        }
    }
    if (argc > 2)
    {
        if (!strcmp(argv[ARG_INPUT], argv[ARG_OUTPUT]))
        {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        fout = fopen(argv[ARG_OUTPUT], "w");
    }

    return reverse(fin, fout);
}

int reverse(FILE* fin, FILE* fout)
{

}