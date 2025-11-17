/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:56:57 by uvadakku          #+#    #+#             */
/*   Updated: 2025/11/17 11:57:06 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **env)
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
	if (fd < 0)
		exit_handler(1);
	if (dup2(fd, 0) == -1)
		exit_handler(1);
	if (dup2(p_fd[1], 1) == -1)
		exit_handler(1);
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exec_cmd(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	if (fd < 0)
	{
		perror(av[4]);
		close(p_fd[0]);
		exit(1);
	}
	if (dup2(p_fd[0], 0) == -1)
		exit_handler(1);
	if (dup2(fd, 1) == -1)
		exit_handler(1);
	close(fd);
	close(p_fd[1]);
	close(p_fd[0]);
	exec_cmd(av[3], env);
}

pid_t	make_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_handler(1);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (argc != 5)
	{
		exit_handler(1);
		return (1);
	}
	if (pipe(p_fd) == -1)
		exit_handler(1);
	pid1 = make_fork();
	if (pid1 == 0)
		child(argv, p_fd, env);
	pid2 = make_fork();
	if (pid2 == 0)
		parent(argv, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
