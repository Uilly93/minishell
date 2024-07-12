/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:37:45 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/12 10:50:13 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_f(long int nb, int fd)
{
	size_t		len;

	len = 0;
	if (nb < 0)
	{
		len += ft_is_c('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
	{
		len += ft_putnbr_f(nb / 10, fd);
		len += ft_putnbr_f(nb % 10, fd);
	}
	else
		len += ft_is_c(nb + 48, fd);
	return (len);
}
