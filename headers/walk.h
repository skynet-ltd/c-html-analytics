#pragma once
#include "error.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
extern int asprintf(char **, const char *, ...);
#endif

enum PATH
{
    UP,
    CURR
};

static const char *PATHS[] = {"..", "."};

typedef Error *(*walk_func)(const char *, struct dirent *, void *);

Error *walk_callback(const char *, struct dirent *, void *);

//walk_dir recursive walk target dir and aggregate results in ret
extern Error *walk_dir(const char *, walk_func, void *);
