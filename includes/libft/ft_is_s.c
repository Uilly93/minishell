/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:46:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/05 11:51:41 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_s(const char *s)
{
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	else
		ft_putstr((char *)s);
	return (ft_strlen((char *)s));
}
