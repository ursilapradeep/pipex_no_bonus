/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:57:15 by uvadakku          #+#    #+#             */
/*   Updated: 2025/11/17 12:44:11 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_in_path(char *cmd, char **all_path)
{
	int		i;
	char	*exec;
	char	*path_part;

	i = -1;
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		if (!path_part)
			return (NULL);
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (!exec)
			return (NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*handle_direct_access(char **cmd_parts)
{
	char	*result;

	if (access(cmd_parts[0], F_OK | X_OK) == 0)
	{
		result = ft_strdup(cmd_parts[0]);
		ft_free_tab(cmd_parts);
		return (result);
	}
	return (NULL);
}
