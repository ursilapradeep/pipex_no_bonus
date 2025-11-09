/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:16:23 by uvadakku          #+#    #+#             */
/*   Updated: 2025/11/09 12:43:35 by us               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
	{
		fprintf(stderr, "./pipex infile cmd cmd outfile\n");
		exit (1);
	}
}

int	open_file(char *file, int mode)
{
	int	ret;

	ret = 0;
	if (mode == 0)
		ret = open(file, O_RDONLY);
	else if (mode == 1)
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ret < 0)
	{
		if (mode == 0)
		{
			ret = open("/dev/null", O_RDONLY);
			if (ret < 0)
				exit(1);
		}
		else
			exit(1);
	}
	return (ret);
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
