/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:53:39 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/15 09:56:40 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	copy = ft_calloc(sizeof(char), n + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n && s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	return (copy);
}
