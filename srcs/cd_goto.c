#include <stdlib.h>
#include "minishell.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void go_to_home_directory(t_sh *shell)
{
	if (get_env_value("HOME", shell->env))
	{
		change_dir(get_env_value("HOME", shell->env), shell, 0);
	}
	else
	{
		ft_putendl_fd("cd: HOME not set", 2);
		shell->l_ret = 1;
	}
}

void go_to_old_pwd(t_sh *shell)
{
	char *old_pwd;

	if (get_env_value("OLDPWD", shell->env))
	{
		if ((old_pwd = ft_strdup(get_env_value("OLDPWD", shell->env))))
		{
			change_dir(old_pwd, shell, 0);
			if (shell->l_ret == 0 && ft_strcmp(old_pwd, get_env_value("PWD", shell->env)) == 0)
			{
				ft_putendl(old_pwd);
			}
			free(old_pwd);
		}
		else
		{
			shell->l_ret = 2;
		}
	}
	else
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		shell->l_ret = 1;
	}
}