#pragma once
#include "error.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib-2.0/glib.h>
#include <string.h>
#include <inttypes.h>

typedef struct cli
{
    GHashTable *cli_flags;
    int (*add_string_flag)(struct cli *, const char *, const char *);
    int (*add_int_flag)(struct cli *, const char *, int);
    const char *(*get_string_flag)(struct cli *, const char *);
    int (*get_int_flag)(struct cli *, const char *);
    void (*parse)(struct cli *, int, char *const *);
    void (*free)(struct cli *);
} cli;

int asprintf(char **, const char *, ...);

extern cli *new_cli();

int add_string_flag(cli *, const char *, const char *);
const char *get_string_flag(cli *, const char *);
int add_int_flag(cli *, const char *, int);
int get_int_flag(cli *, const char *);

void parse(cli *, int, char *const *);
void cli_free(cli *);
