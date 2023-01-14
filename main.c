/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 13:13:40 by mben-sal          #+#    #+#             */
/*   Updated: 2023/01/13 19:45:21 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

char	*git_path(char **env)
{
	int		i;
	char	*path;
	int		len;
	char	*check;

	i = 0;
	check = "PATH=";
	while (env[i])
	{
		if (strncmp(env[i], check, 5) == 0)
		{
			len = strlen(env[i]);
			path = ft_substr(env[i], 5, len);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*ft_path(char **spl, char *cmd)
{
	int		i;
	char	*path;

	i = -1;
	while (spl[++i])
	{
		path = ft_strjoin(spl[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(cmd);
			return (path);
		}
		free(path);
	}
	free(cmd);
	return (NULL);
}

char	*ft_check_path(char **spl, char *av)
{
	char	*cmd;
	char	**str;

	str = ft_split(av, ' ');
	if (strncmp(str[0], "/", 1) == 0)
	{
		if (access(str[0], F_OK | X_OK) == 0)
		{
			free (str[1]);
			return (str[0]);
		}
		ft_free(str);
		ft_printf("pipex: %s: %s\n", strerror(errno), av);
		return (NULL);
	}
	cmd = ft_strjoin("/", str[0]);
	ft_free(str);
	return (ft_path(spl, cmd));
}

char	*ft_check_cmd(char **env, char *av)
{
	char	*str;
	char	**spl;
	char	*cmd1;

	str = git_path(env);
	if (!str)
	{
		spl = ft_split(av, ' ');
		ft_printf("pipex: command not found: %s\n", spl[0]);
		ft_free(spl);
		return (0);
	}
	spl = ft_split(str, ':');
	cmd1 = ft_check_path(spl, av);
	if (cmd1 == NULL)
		ft_printf("pipex: command not found: %s\n", av);
	ft_free(spl);
	free(str);
	return (cmd1);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd1;
	char	*cmd2;
	int		pipfd[2];
	int		pid[2];

	if (ac != 5 || env[0] == NULL)
	{
		ft_printf("pipex: %s\n", strerror(errno));
		exit (EXIT_FAILURE);
	}
	cmd1 = ft_check_cmd(env, av[2]);
	cmd2 = ft_check_cmd(env, av[3]);
	if (pipe(pipfd) == -1)
	{
		perror("an error with opening the pipe\n");
		exit (EXIT_FAILURE);
	}
	pid[0] = first_child(cmd1, av, env, pipfd);
	pid[1] = second_child(cmd2, av, env, pipfd);
	close(pipfd[0]);
	close(pipfd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
