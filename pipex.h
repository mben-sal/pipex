/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:21:06 by mben-sal          #+#    #+#             */
/*   Updated: 2023/01/13 19:31:01 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<stdarg.h>
# include<stdarg.h>
# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<fcntl.h>
# include<string.h>
# include <sys/errno.h>
# include <errno.h>

typedef struct s_spl
{
	size_t	i;
	size_t	j;
	size_t	len;
	int		index;
	int		count;
	char	**ptr;
}	t_spl;

int		ft_strncmp(const char *first, const char *second, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		second_child(char *cmd2, char **av, char **env, int *pipfd);
int		first_child(char *cmd1, char **av, char **env, int *pipfd);
void	**ft_free(char **s);
void	ft_check_per(va_list pf, char c, int *len);
int		ft_printf(const char *str, ...);
void	ft_check_per(va_list pf, char c, int *len);
void	ft_putstr(char *s, int *len);
void	ft_putchar(char c, int *len);

#endif