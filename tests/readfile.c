#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#include "readfile.h"

char *read_file(char *filename)
{
    char *data;
    long length = 0;

    FILE *fh = fopen(filename, "rb");

    fseek(fh, 0, SEEK_END);
    length = ftell(fh);
    fseek(fh, 0, SEEK_SET);

    data = (char *) malloc(length+1);
    memset(data, 0x00, length+1);

    size_t result = fread(data, length, 1, fh);
    if (result != 1) {
        fputs("err", stderr);
        exit(1);
    }
    fclose(fh);

    return data;
}
