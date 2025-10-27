/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:16:42 by clouden           #+#    #+#             */
/*   Updated: 2025/10/20 20:20:51 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <libft.h>

// void *ft_realloc(void *ptr, size_t size)
// {
// 	size_t	i;
// 	void *mem;

// 	i = 0;
// 	if (size == 0)
// 	{
// 		if (ptr)
// 			free(ptr);
// 		return (NULL);
// 	}
// 	mem = malloc(size);
// 	if (!mem)
// 		return (NULL);
// 	while (i < size && ((unsigned char *)ptr)[i])
// 	{
// 		((unsigned char *)mem)[i] = ((unsigned char *)ptr)[i];					
// 		i++;		
// 	} 	
// 	free(ptr);
// 	ptr = NULL;
// 	return(mem);		
// }

