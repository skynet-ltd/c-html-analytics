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
    int err = cli_store->add_string_flag(cli_store, "f", "");
    if (err)
    {
        printf("add_string_flag return %i\n", err);
        return err;
    }
    err = cli_store->add_int_flag(cli_store, "j", 10);
    if (err)
    {
        printf("add_int_flag return %i\n", err);
        return err;
    }
    cli_store->parse(cli_store, argc, argv);
    const char *in_file_path = cli_store->get_string_flag(cli_store, "f");
    if (in_file_path == "")
    {
        return -1;
    }
    int jobs = cli_store->get_int_flag(cli_store, "j");
    FILE *in_file = fopen(in_file_path, "r");
    if (!in_file)
    {
        fprintf(stderr, "error: can't open file %s\n", in_file_path);
        return -2;
    }
    char *line = NULL;
    size_t n = 0;
    while (getline(&line, &n, in_file) > 0)
    {
        fprintf(stdout, "%s\n", line);
    }
    fclose(in_file);
    cli_free(cli_store);
}
