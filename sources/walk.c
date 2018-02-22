#include "../headers/walk.h"

//wal_dir recursive walk target dir and aggregate results in ret
Error *walk_dir(const char *dir_name, walk_func callback, void *ret)
{
    Error *err = NULL;
    DIR *dir_ptr = opendir(dir_name);
    if (!dir_ptr)
    {
        err = &(Error){.code = 1, .error = "can't open dir"};
        return err;
    }
    struct dirent *dr = NULL;
    while (NULL != (dr = readdir(dir_ptr)))
    {
        if (strcmp(dr->d_name, PATHS[UP]) == 0 || strcmp(dr->d_name, PATHS[CURR]) == 0)
        {
            continue;
        }
        char *path;
        int res = asprintf(&path, "%s/%s", dir_name, dr->d_name);
        if (res <= 0)
        {
            err = &(Error){.code = 2, .error = "asprintf return error"};
            free(path);
            break;
        }
        err = callback(path, dr, ret);
        free(path);
        if (err)
        {
            break;
        }
    }
    closedir(dir_ptr);
    return err;
}