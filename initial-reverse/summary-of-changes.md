# Summary of Changes

### Build + Testing Instructions
```bash
prompt> gcc -o reverse reverse.c
prompt> ./test-reverse.sh
```

### `reverse.c > main()`
Parsed command line arguments. Opens `stdin` and `stdout` by default. If arguments are provided, the respective file pointers are updated to the given input and output files.
```c
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
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[ARG_INPUT]);
            exit(1);
        }
    }
    if (argc > 2)
    {
        if (!file_compare(argv[ARG_INPUT], argv[ARG_OUTPUT]))
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        fout = fopen(argv[ARG_OUTPUT], "w");
    }

    exit(reverse(fin, fout));
}
```

### `reverse.c > file_compare()`
Resolves the argument paths to verify that the input and output files are unique.
```c
int file_compare(const char* i_path, const char* o_path)
/*
    Returns 1 if paths point to different files
    Returns 0 if paths point to the same file
    Returns -1 on error
*/
{
    struct stat i_stat, o_stat;
    if (stat(i_path, &i_stat) == -1 ||
        stat(o_path, &o_stat) == -1)
        return -1;
    return !(i_stat.st_ino == o_stat.st_ino && i_stat.st_dev == o_stat.st_dev);
}
```

### `reverse.c > reverse()`
Recursively reads lines until `EOF` (for file inputs) or an empty line (for `stdin`) occurs. Prints lines in reverse order unless an error occured.
```c
int reverse(FILE* fin, FILE* fout)
{
    int ret_val = 0;

    char* in_line = NULL;
    size_t in_len = 0;
    ssize_t nread = getline(&in_line, &in_len, fin);

    if (nread == -1)
    {
        if (errno == ENOMEM)
        {
            fprintf(stderr, "malloc failed\n");
            ret_val = 1;
        }
        goto RET;
    }

    if (nread > 1)
        ret_val = reverse(fin, fout);

    if (ret_val != 1)
        fprintf(fout, "%s", in_line);

RET:
    free(in_line);
    return ret_val;
}
```
