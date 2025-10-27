/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:16:24 by clouden           #+#    #+#             */
/*   Updated: 2025/10/27 20:46:50 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;

	i = 0;
	d_len = ft_strlen(dst);
	if (size == 0 || (size == 1 && dst[0] == '\0'))
	{
		return (ft_strlen((char *)src));
	}
	else if ((size == 1 && dst[0] != '\0') || \
			(size > 1 && d_len > size - 1))
	{
		return (size + ft_strlen((char *)src));
	}
	else if (size > 1 && d_len == size - 1)
		return (d_len + ft_strlen((char *)src));
	while (src[i] && d_len + i < size - 1)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + ft_strlen((char *)src));
}


static int	ft_getsize(long n, int neg)
{
	int	size;

	size = 2;
	if (neg == 1)
		size++;
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*ft_ifzero(char *str)
{
	int	size;

	size = 2;
	str = ft_calloc(1, size);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}


static char	*ft_buildstr(long n, char *str, int size)
{
	str = ft_calloc(1, size);
	if (!str)
		return (NULL);
	size--;
	str[size] = '\0';
	while (n >= 0)
	{
		if (n == 0 && size == 0)
			return (str);
		else if (n == 0 && size == 1)
		{
			size--;
			str[size] = '-';
			return (str);
		}
		else
		{
			size--;
			str[size] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	num;

	str = NULL;
	num = n;
	if (num == 0)
	{
		str = ft_ifzero(str);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (num < 0)
	{
		num = num * -1;
		size = ft_getsize(num, 1);
	}
	else
		size = ft_getsize(num, 0);
	str = ft_buildstr(num, str, size);
	if (str == NULL)
		return (NULL);
	return (str);
}

int	ft_isshelloperator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
