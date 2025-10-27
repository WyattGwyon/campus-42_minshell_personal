/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:57:26 by clouden           #+#    #+#             */
/*   Updated: 2025/07/03 14:57:31 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	while (s[i] != '\0')
// 		i ++;
// 	return (i);
// }

// int	ft_putchar_fd(char c, int fd)
// {
// 	int	bytes;

// 	bytes = 0;
// 	bytes += write(fd, &c, 1);
// 	return (bytes);
// }

// int	ft_putstr_fd(const char *s, int fd)
// {
// 	if (!s)
// 		return (ft_putstr_fd("(null)", 1));
// 	return (write(fd, s, ft_strlen(s)));
// }

// int	ft_putnbr_fd(int n, int fd)
// {
// 	int	bytes;

// 	bytes = 0;
// 	if (n == -2147483648)
// 	{
// 		bytes += write(fd, "-2147483648", 11);
// 		return (bytes);
// 	}
// 	if (n < 0)
// 	{
// 		bytes += ft_putchar_fd('-', fd);
// 		n = n * -1;
// 	}
// 	if (n >= 10)
// 		bytes += ft_putnbr_fd(n / 10, fd);
// 	bytes += ft_putchar_fd(n % 10 + '0', fd);
// 	return (bytes);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s != (char)c)
// 	{
// 		if (*s == '\0')
// 			return ((char *)0);
// 		else
// 			s++;
// 	}
// 	return ((char *)s);
// }
