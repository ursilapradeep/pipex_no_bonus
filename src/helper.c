# include "pipex.h"

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
