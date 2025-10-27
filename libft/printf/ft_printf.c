/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:54:33 by clouden           #+#    #+#             */
/*   Updated: 2025/07/14 16:12:45 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr_fd(unsigned int n, int fd)
{
	int	bytes;

	bytes = 0;
	if (n >= 10)
		bytes += ft_putunbr_fd(n / 10, fd);
	bytes += ft_putchar_fd(n % 10 + '0', fd);
	return (bytes);
}

int	ft_puthex_fd(unsigned long long n, int fd, char mode)
{
	int		bytes;
	char	*x;
	char	*upx;
	int		r;

	bytes = 0;
	x = "0123456789abcdef";
	upx = "0123456789ABCDEF";
	if (n >= 16)
		bytes += ft_puthex_fd(n / 16, fd, mode);
	r = n % 16;
	if (mode == 'x' || mode == 'p')
		bytes += ft_putchar_fd(x[r], fd);
	if (mode == 'X')
		bytes += ft_putchar_fd(upx[r], fd);
	return (bytes);
}

int	ft_putptr_fd(void *ptr, int fd)
{
	int	bytes;

	bytes = 0;
	if (ptr == NULL)
	{
		bytes += ft_putstr_fd("(nil)", fd);
		return (bytes);
	}
	bytes += ft_putstr_fd("0x", fd);
	bytes += ft_puthex_fd((uintptr_t)ptr, fd, 'x');
	return (bytes);
}

static int	ft_mapfmt(char *new, va_list args)
{
	unsigned long long	ptr;

	if (*new == 's')
		return (ft_putstr_fd(va_arg(args, const char *), 1));
	if (*new == 'd' || *new == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (*new == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (*new == 'u')
		return (ft_putunbr_fd(va_arg(args, unsigned int), 1));
	if (*new == '%')
		return (ft_putchar_fd('%', 1));
	if (*new == 'x' || *new == 'X')
	{
		ptr = (unsigned long long)va_arg(args, unsigned int);
		return (ft_puthex_fd(ptr, 1, *new));
	}
	if (*new == 'p')
		return (ft_putptr_fd(va_arg(args, void *), 1));
	return (ft_putchar_fd(*new, 1));
}

int	ft_printf(const char *fmt, ...)
{
	va_list			args;
	char			*new;
	char			*old;
	ssize_t			bytes;	

	new = ft_strchr(fmt, '%');
	if (!new)
		return (write(1, fmt, ft_strlen(fmt)));
	va_start(args, fmt);
	bytes = write(1, fmt, new - fmt);
	while (new)
	{
		if (new[1] == '\0')
			return (va_end(args), bytes + write(1, new, 1));
		bytes += ft_mapfmt(++new, args);
		old = ++new;
		new = ft_strchr(new, '%');
		if (new)
			bytes += write(1, old, new - old);
		else
			bytes += write(1, old, ft_strlen(old));
	}
	return (va_end(args), bytes);
}
