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
    cli *cli_store = new_cli();
    int err = cli_store->add_string_flag(cli_store, "d", "aaaa");
    if (err)
    {
        return err;
    }
    err = cli_store->add_int_flag(cli_store, "j", 10);
    if (err)
    {
        return err;
    }
    cli_store->parse(cli_store, argc, argv);
    const char *dir = cli_store->get_string_flag(cli_store, "d");
    int jobs = cli_store->get_int_flag(cli_store, "j");
    if (dir == "")
    {
        return -1;
    }
    printf("%i\n", jobs);
    printf("%s\n", dir);
    cli_free(cli_store);
}
