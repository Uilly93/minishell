/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:46:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/25 11:17:50 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_s(const char *s, int fd)
{
	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	else
		ft_putstr_fd((char *)s, fd);
	return (ft_strlen((char *)s));
}
