#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

void err_n_die(const char *fmt, ...) {
    int errno_save;
    va_list ap;

    // Save errno in case it gets overwritten
    errno_save = errno;

    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);

    if (errno_save != 0) {
        fprintf(stderr, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
    }

    va_end(ap);
    exit(1);
}

char *bin2hex(const unsigned char *input, size_t len) {
    char *output;
    size_t i;

    if (input == NULL || len == 0)
        return NULL;

    // Each byte -> 2 hex characters + 1 null terminator
    output = malloc(len * 2 + 1);
    if (output == NULL)
        return NULL;

    for (i = 0; i < len; i++) {
        sprintf(output + i * 2, "%02x", input[i]);
    }

    output[len * 2] = '\0'; // Null-terminate the string
    return output;
}
