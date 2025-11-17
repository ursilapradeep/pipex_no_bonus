/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:43:23 by uvadakku          #+#    #+#             */
/*   Updated: 2025/11/17 12:35:52 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>    
# include <sys/stat.h>
# include  <sys/wait.h>
# include "libft.h"

pid_t	make_fork(void);
int		main(int argc, char **argv, char **env);
void	parent(char **av, int *p_fd, char **env);
void	child(char **av, int *p_fd, char **env);
void	exec_cmd(char *cmd, char **env);
void	exit_handler(int n_exit);
int		open_file(char *file, int mode);
void	ft_free_tab(char **tab);
void	handle_cmd_error(char **args, char *path);
char	*my_getenv(char *name, char **env);
char	*handle_direct_access(char **cmd_parts);
char	*search_in_path(char *cmd, char **all_path);
char	*find_path(char *cmd, char **env);

#endif