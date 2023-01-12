/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:45:54 by mben-sal          #+#    #+#             */
/*   Updated: 2023/01/11 18:32:40 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	ft_putchar(char c, int *len)
{
	write(2, &c, 1);
	(*len)++;
}

void	ft_putstr(char *s, int *len)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		ft_putchar(s[i], len);
		i++;
	}
}

void	ft_check_per(va_list pf, char c, int *len)
{
	if (c == 'c')
		ft_putchar (va_arg (pf, int), len);
	else if (c == 's')
		ft_putstr (va_arg (pf, char *), len);
	else
		ft_putchar(c, len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	pf;
	int		len;

	i = 0;
	len = 0;
	va_start(pf, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_check_per(pf, str[i + 1], &len);
			i++;
		}
		else
			ft_putchar(str[i], &len);
		i++;
	}
	va_end(pf);
	return (len);
}
