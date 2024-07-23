/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:46:56 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/23 08:52:22 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_p(void *ptr, int fd)
{
	char	*s;

	s = "0123456789abcdef";
	if (!ptr)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	ft_putstr_fd("0x", fd);
	return (ft_putnbr_base_long((unsigned long) ptr, s, fd) + 2);
}
