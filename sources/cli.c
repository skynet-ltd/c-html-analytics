#include "../headers/cli.h"

static cli *store = &(cli){.string_flags = NULL};

void init_if_empty()
{
    if (store->string_flags == NULL)
    {
        store->string_flags = g_hash_table_new(g_str_hash, g_str_equal);
    }
}

int add_string_flag(const char *flag, const char *def)
{
    if (flag == NULL)
    {
        return -1;
    }
    init_if_empty();
    if (g_hash_table_insert(store->string_flags, (gpointer)flag, (gpointer)def) == TRUE)
    {
        return 0;
    }
    return -1;
}
const char *get_string_flag(const char *key)
{
    return g_hash_table_lookup(store->string_flags, key);
}

void parse(int argc, char *const *argv)
{
    const char **keys = (const char **)g_hash_table_get_keys_as_array(store->string_flags, 0);
    opterr = 0;
    char *short_opt = strdup("");
    for (const char **keys_p = keys; *keys_p; keys_p++)
    {
        char *tmp_opt = short_opt;
        asprintf((char **)&tmp_opt, "%s%s%s", tmp_opt, *keys_p, ":");
        free(short_opt);
        short_opt = strdup(tmp_opt);
        free(tmp_opt);
    }
    for (int c = getopt(argc, argv, short_opt); c != -1; c = getopt(argc, argv, short_opt))
    {
        for (const char **keys_p = keys; *keys_p; keys_p++)
        {
            if (**keys_p == c && optarg)
            {
                g_hash_table_replace(store->string_flags, (gpointer)*keys_p, (gpointer)optarg);
            }
        }
    }
    free(short_opt);
    g_free(keys);
}

void cli_free()
{
    g_hash_table_destroy(store->string_flags);
}