#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int is_enter(char *buf)
{
	if (buf && ft_strlen(buf) == 1 && buf[0] == '\n')
		return (1);
	return (0);
}

int is_real_line(char *buf)
{
	size_t len;
	size_t i;

	i = 0;
	if ((len = ft_nstrlen(buf)))
	{
		while (buf[i] && buf[i] != '\n')
		{
			i++;
		}
		if (i == len - 1 && (buf[0] != '\n'))
			return (1);
	}
	return (0);
}