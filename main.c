/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 13:13:40 by mben-sal          #+#    #+#             */
/*   Updated: 2023/01/12 12:25:22 by mben-sal         ###   ########.fr       */
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

// void	ft_free(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

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
	int		i;
	char	*cmd;
	char	**str;

	str = ft_split(av, ' ');
	i = -1;
	if (strncmp(str[0], "/", 1) == 0)
	{
		if (access(str[0], F_OK | X_OK) == 0)
		{
			free (str[1]);
			return (str[0]);
		}
		ft_free(str);
		ft_printf("pipex: %s: %s\n", strerror(errno), av);
		exit(EXIT_FAILURE);
	}
	cmd = ft_strjoin("/", str[0]);
	ft_free(str);
	return (ft_path(spl, cmd));
}

// int	first_child(char *cmd1, char **av, char **env, int *pipfd)
// {
// 	int		pid;
// 	int		fd;
// 	char	**spl;

// 	spl = ft_split(av[2], ' ');
// 	pid = fork();
// 	fd = open(av[1], O_RDONLY);
// 	if (pid == -1)
// 	{
// 		printf("pipex: %s\n", strerror(errno));
// 	}
// 	if (pid == 0)
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(pipfd[0]);
// 		dup2(pipfd[1], STDOUT_FILENO);
// 		close(fd);
// 		close(pipfd[1]);
// 		execve(cmd1, spl, env);
// 	}
// 	free(cmd1);
// 	ft_free(spl);
// 	return (pid);
// }

// int	second_child(char *cmd2, char **av, char **env, int *pipfd)
// {
// 	int		pid;
// 	int		fd;
// 	char	**spl;

// 	spl = ft_split(av[3], ' ');
// 	pid = fork();
// 	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	if (pid == -1)
// 	{
// 		printf("pipex: %s\n", strerror(errno));
// 	}
// 	if (pid == 0)
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		close(pipfd[1]);
// 		dup2(pipfd[0], STDIN_FILENO);
// 		close(fd);
// 		close(pipfd[0]);
// 		execve(cmd2, spl, env);
// 	}
// 	free(cmd2);
// 	ft_free(spl);
// 	return (pid);
// }

char	*ft_check_cmd(char **env, char *av)
{
	char	*str;
	char	**spl;
	char	*cmd1;

	str = git_path(env);
	if (!str)
		ft_printf("pipex: %s\n", strerror(errno));
	spl = ft_split(str, ':');
	cmd1 = ft_check_path(spl, av);
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
	}
	pid[0] = first_child(cmd1, av, env, pipfd);
	pid[1] = second_child(cmd2, av, env, pipfd);
	close(pipfd[0]);
	close(pipfd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
