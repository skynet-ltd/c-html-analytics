#include "../headers/cli.h"

int add_string_flag(cli *self, const char *flag, const char *def)
{
    if (flag == NULL)
    {
        return -1;
    }
    if (g_hash_table_insert(self->cli_flags, (gpointer)strdup(flag), (gpointer)strdup(def)) == TRUE)
    {
        return 0;
    }
    return -1;
}
int add_int_flag(cli *self, const char *flag, int def)
{
    if (flag == NULL)
    {
        return -1;
    }
    char *str;
    asprintf(&str, "%i", def);
    if (g_hash_table_insert(self->cli_flags, (gpointer)strdup(flag), (gpointer)strdup(str)) == TRUE)
    {
        free(str);
        return 0;
    }
    free(str);
    return -1;
}

const char *get_string_flag(cli *self, const char *key)
{
    return g_hash_table_lookup(self->cli_flags, (gpointer)key);
}

int get_int_flag(cli *self, const char *key)
{
    const char *ret = g_hash_table_lookup(self->cli_flags, (gpointer)key);
    return strtoimax(ret, (char **)NULL, 10);
}

void parse(cli *self, int argc, char *const *argv)
{
    const char **keys = (const char **)g_hash_table_get_keys_as_array(self->cli_flags, 0);
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
                printf("%s : %s\n", *keys_p, optarg);
                g_hash_table_replace(self->cli_flags, (gpointer)strdup(*keys_p), (gpointer)strdup(optarg));
            }
        }
    }
    free(short_opt);
    g_free(keys);
}

void cli_free(cli *self)
{
    g_hash_table_destroy(self->cli_flags);
    free(self);
}

void key_destroy(gpointer data)
{
    g_free(data);
}

void val_destroy(gpointer data)
{
    g_free(data);
}

cli *new_cli()
{
    cli *cli_s = calloc(1, sizeof(cli));
    cli_s->cli_flags = g_hash_table_new_full(g_str_hash, g_str_equal, key_destroy, val_destroy);
    cli_s->add_int_flag = add_int_flag;
    cli_s->add_string_flag = add_string_flag;
    cli_s->get_int_flag = get_int_flag;
    cli_s->get_string_flag = get_string_flag;
    cli_s->free = cli_free;
    cli_s->parse = parse;
    return cli_s;
}