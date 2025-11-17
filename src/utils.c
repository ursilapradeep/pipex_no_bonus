/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:57:23 by uvadakku          #+#    #+#             */
/*   Updated: 2025/11/17 12:07:29 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **env)
{
	char	**all_path;
	char	**cmd_parts;
	char	*result;
	char	*env_path;

	cmd_parts = ft_split(cmd, ' ');
	if (!cmd_parts)
		return (NULL);
	result = handle_direct_access(cmd_parts);
	if (result)
		return (result);
	env_path = my_getenv("PATH", env);
	if (env_path)
		all_path = ft_split(env_path, ':');
	if (!env_path || !all_path)
	{
		ft_free_tab(cmd_parts);
		return (NULL);
	}
	result = search_in_path(cmd_parts[0], all_path);
	ft_free_tab(cmd_parts);
	ft_free_tab(all_path);
	return (result);
}

void	handle_cmd_error(char **args, char *path)
{
	ft_putstr_fd("command not found: ", 2);
	if (args && args[0])
		ft_putendl_fd(args[0], 2);
	else
		ft_putendl_fd("", 2);
	if (args)
		ft_free_tab(args);
	if (path)
		free(path);
	exit(127);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	open_file(char *file, int mode)
{
	int	ret;

	if (mode == 0)
	{
		ret = open(file, O_RDONLY);
		if (ret < 0)
		{
			perror(file);
			return (-1);
		}
	}
	else if (mode == 1)
	{
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (ret < 0)
			return (-1);
	}
	else
		return (-1);
	return (ret);
}

void	exit_handler(int n_exit)
{
	perror("pipex: ");
	exit(n_exit);
}
