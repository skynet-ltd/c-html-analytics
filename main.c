#include "headers/container.h"

//int counter = 0;

Error *walk_callback(const char *path, struct dirent *dr, void *ret)
{
    if (dr->d_type == DT_DIR)
    {
        return walk_dir(path, walk_callback, ret);
    }
    char *tmp_str = strdup(path);
    vector *temp = (vector *)ret;
    int code = temp->push(temp, tmp_str);
    if (code != 0)
    {
        free(tmp_str);
        return &(Error){.code = -5, .error = "realloc error"};
    }
    return NULL;
}

int main(int argc, char *const *argv)
{
    int err = add_string_flag("d", "");
    if (err)
    {
        return err;
    }
    err = add_int_flag("j", 10);
    if (err)
    {
        return err;
    }
    parse(argc, argv);
    printf("%i\n", get_int_flag("j"));
    printf("%s\n", get_string_flag("d"));
    cli_free();
}
