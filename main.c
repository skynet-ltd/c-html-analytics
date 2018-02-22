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
    int err = add_string_flag("d", NULL);
    if (err)
    {
        return err;
    }
    parse(argc, argv);
    vector *str_vec = new_vector(sizeof(char *), 0);
    Error *err_s = walk_dir(get_string_flag("d"), walk_callback, (void *)str_vec);
    if (err_s)
    {
        printf("Error: %s\n", err_s->error);
        return -2;
    }
    for (int i = 0; i < str_vec->length(str_vec); i++)
    {
        printf("%s\n", (const char *)str_vec->get(str_vec, i));
    }
    printf("Size of vector %i,capacity %i\n", str_vec->length(str_vec), str_vec->cap(str_vec));

    //clean memory
    str_vec->clear(str_vec, 1);
    cli_free();
}
