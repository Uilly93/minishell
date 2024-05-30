/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:00:08 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/19 09:53:50 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*reallocated;

	reallocated = ft_calloc(1, size);
	if (!reallocated)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(reallocated, (void *)ptr, size);
		free(ptr);
	}
	return (reallocated);
}
