#include "minishell.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void go_to_home_directory(t_sh *shell)
{
	if (get_env_value("HOME", shell->env))
	{
		change_dir(get_env_value("HOME", shell->env), shell);
	}
	else
	{
		ft_putendl_fd("cd: HOME not set", 2);
		shell->last_command_ret = 1;
	}
}

void go_to_old_pwd(t_sh *shell)
{
	if (get_env_value("OLDPWD", shell->env))
	{
		change_dir(get_env_value("OLDPWD", shell->env), shell);
		ft_putendl(get_env_value("PWD", shell->env));
	}
	else
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		shell->last_command_ret = 1;
	}
}