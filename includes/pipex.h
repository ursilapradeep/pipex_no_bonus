/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:43:23 by uvadakku          #+#    #+#             */
/*   Updated: 2025/11/09 13:13:34 by us               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>    // for open() and O_CREAT, O_WRONLY, O_TRUNC
# include <sys/stat.h> // for file permission constants (mode_t)
# include  <sys/wait.h>
# include "libft.h"

int		main(int argc, char **argv, char **env);
void	parent(char **av, int *p_fd, char **env);
void	child(char **av, int *p_fd, char **env);
void	exec(char *cmd, char **env);
void	exit_handler(int n_exit);
int		open_file(char *file, int mode);
void	ft_free_tab(char **tab);
char	*my_getenv(char *name, char **env);
char	*handle_direct_access(char **cmd_parts);
char	*search_in_path(char *cmd, char **all_path);
char	*find_path(char *cmd, char **env);

#endif