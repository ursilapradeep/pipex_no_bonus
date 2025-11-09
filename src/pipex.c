/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:07:55 by uvadakku          #+#    #+#             */
/*   Updated: 2025/11/09 12:28:33 by us               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0] || !args[0][0])
		handle_cmd_error(args, NULL);
	path = find_path(args[0], env);
	if (!path)
		handle_cmd_error(args, NULL);
	if (execve(path, args, env) == -1)
		handle_cmd_error(args, path);
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
	int			p_fd[2];
	pid_t		pid;
	int			status;

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
	waitpid(pid, &status, 0);
	parent(argv, p_fd, env);
	return (0);
}
