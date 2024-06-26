/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:38:42 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/25 11:17:00 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nb, char *base, int fd)
{
	long long		i;
	char			result [100];
	int				len;

	if (nb == 0)
	{
		ft_putchar_fd(base[0], fd);
		return (1);
	}
	i = 0;
	if ((int)nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	while (nb > 0)
	{
		result[i] = base[nb % ft_strlen(base)];
		nb /= ft_strlen(base);
		i++;
	}
	len = i;
	while (i > 0)
		ft_putchar_fd(result[i-- - 1], fd);
	return (len);
}
