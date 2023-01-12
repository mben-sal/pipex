/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:39:22 by mben-sal          #+#    #+#             */
/*   Updated: 2023/01/12 12:35:35 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	first_child(char *cmd1, char **av, char **env, int *pipfd)
{
	int		pid;
	int		fd;
	char	**spl;

	spl = ft_split(av[2], ' ');
	fd = open(av[1], O_RDONLY | O_APPEND);
	if (fd < 0)
		return (ft_printf("pipex: %s: %s\n", strerror(errno), av[1]));
	pid = fork();
	if (pid == -1)
		return (ft_printf("pipex: %s\n", strerror(errno)));
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(pipfd[0]);
		dup2(pipfd[1], STDOUT_FILENO);
		close(fd);
		close(pipfd[1]);
		execve(cmd1, spl, env);
	}
	free(cmd1);
	ft_free(spl);
	return (pid);
}

int	second_child(char *cmd2, char **av, char **env, int *pipfd)
{
	int		pid;
	int		fd;
	char	**spl;

	spl = ft_split(av[3], ' ');
	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
		return (ft_printf("pipex: %s: %s\n", strerror(errno), av[4]));
	pid = fork();
	if (pid == -1)
		return (ft_printf("pipex: %s\n", strerror(errno)));
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(pipfd[1]);
		dup2(pipfd[0], STDIN_FILENO);
		close(fd);
		close(pipfd[0]);
		execve(cmd2, spl, env);
	}
	free(cmd2);
	ft_free(spl);
	return (pid);
}
