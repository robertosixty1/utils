#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// why do i need to be cross platform
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void usage(FILE* stream) {
    fprintf(stream, "Usage: cp <input> <output>\n");
}

int is_regular_file(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        usage(stderr);
        fprintf(stderr, "ERROR: Not enough arguments provided\n");
        exit(1);
    }

    const char* input = argv[1];

    if (!is_regular_file(input)) {
        fprintf(stderr, "ERROR: is_regular_file() returned `0` for `%s` (maybe file is directory?)\n", input);
        exit(1);
    }

    const char* output = argv[2];
    FILE* file = fopen(input, "r");

    if (!file) {
        fprintf(stderr, "ERROR: Could not open file `%s`: %s\n", input, strerror(errno));
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    size_t sz = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char buffer[sz];
    fread(buffer, 1, sz, file);
    buffer[sz] = '\0';
    fclose(file);
    ////////////////////
    FILE* output_file = fopen(output, "wb");

    if (!output_file) {
        fprintf(stderr, "ERROR: Could not open file `%s`: %s\n", input, strerror(errno));
        exit(1);
    }

    fwrite(buffer, 1, sz, output_file);
    return 0;
}
