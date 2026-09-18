#ifndef TJG_SLURP_H_
#define TJG_SLURP_H_

#include <stdio.h>
#include <stdlib.h>

char *tjg_slurp(const char *file_path);

#endif // TJG_SLURP_H_


#ifdef TJG_SLURP_IMPLEMENTATION

char *tjg_slurp(const char *file_path) {
    FILE *f = NULL;
    char *contents = NULL;

    f = fopen(file_path, "r");
    if (!f) goto fail;

    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    if (pos < 0) goto fail;
    size_t size = (size_t)pos;

    contents = malloc(size + 1);
    if (!contents) goto fail;

    fseek(f, 0, SEEK_SET);
    if (fread(contents, 1, size, f) < size) goto fail;

    contents[size] = '\0';
    fclose(f);

    return contents;

fail:
    if (f) fclose(f);
    if (contents) free(contents);
    return NULL;
}

#endif // TJG_SLURP_IMPLEMENTATION


#ifdef TJG_STRIP_PREFIX
    #define slurp tjg_slurp
#endif // TJG_STRIP_PREFIX
