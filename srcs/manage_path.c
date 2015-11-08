#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int strlen_until_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}

char *join_path_to_command(char *command, char *path_value)
{
    int cur_path_len;
    char *tmp_cur_path;
    char *cur_path;
    char *cur_full_cmd;

    cur_path = NULL;
    cur_full_cmd = NULL;
    cur_path_len = -1;
    while (cur_path_len != 0 && path_value)
    {
        cur_path_len = strlen_until_char(path_value, ':');
        tmp_cur_path = ft_strndup(path_value, cur_path_len);
        cur_path = ft_strjoin(tmp_cur_path, "/"); // leaks
        free(tmp_cur_path);
        cur_full_cmd = ft_strjoin(cur_path, command);
        free(cur_path);
        if (access(cur_full_cmd, X_OK) == 0)
            return (cur_full_cmd);
        free(cur_full_cmd);
        if (path_value[cur_path_len] != '\0')
            path_value = &path_value[cur_path_len + 1];
        else
            cur_path_len = 0;
    }
    return (NULL);
}

int make_full_path(char **command, char *path_value)
{
    char *full_command;

    full_command = NULL;
    if ((full_command = join_path_to_command(command[0], path_value)))
    {
        free(command[0]);
        command[0] = full_command;
        return (1);
    }
    return (0);
}

static char *get_path_from_environ(void)
{
    extern char **environ;
    char *path_value;

    path_value = NULL;
    while (*environ)
    {
        if (ft_strncmp(*environ, "PATH=", 5) == 0)
        {
            path_value = &(*environ)[5];
            return (path_value);
        }
        environ++;
    }
    return (NULL);
}

int     make_exploitable(char **command)
{
    char *path_value;

    path_value = NULL;
    if (access(*command, X_OK) == 0)
        return (1);

    if ((path_value = get_path_from_environ()))
        return (make_full_path(command, path_value));

    return (0);
}