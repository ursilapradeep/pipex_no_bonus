/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:07:55 by uvadakku          #+#    #+#             */
/*   Updated: 2025/10/27 13:45:05 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = find_path(args[0], env);
	if (!path)
	{
		ft_putstr_fd("pipex command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		ft_free_tab(args);
		exit (1);
	}
	if (execve(path, args, env) == -1)
	{
		perror("execv failed");
		ft_free_tab(args);
		free(path);
		exit(1);
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2 (p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int	p_fd[2];
	int	pid;

	if (argc != 5)
	{
		exit_handler(1);
		return (1);
	}
	if (pipe(p_fd) == -1)
		exit (-1);
	pid = fork();
	if (pid == -1)
		exit (-1);
	if (!pid)
		child (argv, p_fd, env);
	parent(argv, p_fd, env);
	return (0);
}
