#pragma once
#include "error.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib-2.0/glib.h>
#include <string.h>
#include <inttypes.h>

typedef struct
{
    Error *last_error;
    GHashTable *cli_flags;
} cli;

void init_if_null(cli **);
int asprintf(char **, const char *, ...);

extern int add_string_flag(const char *, const char *);
extern const char *get_string_flag(const char *);
extern int add_int_flag(const char *, int);
extern int get_int_flag(const char *);

extern void parse(int, char *const *);
extern void cli_free();
