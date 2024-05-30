/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:27:22 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/05 11:51:24 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && (nmemb > ULONG_MAX / size))
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}

/* int	main(void)
{
	void	*ptr;
	void	*ptr2;

	//printf("%s\n", ptr);
	ptr = ft_calloc(-1, -1);
	ptr2 = calloc(-5, -5);
	printf("%p\n", ptr);
	printf("%p\n", ptr2);
	free(ptr);
} */