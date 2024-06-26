/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandatory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:48:03 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/25 11:20:45 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mandatory(const char *fmt, va_list args, int fd)
{
	int	len;

	len = 0;
	if (*fmt == 's')
		len += ft_is_s(va_arg(args, char *), fd);
	else if (*fmt == 'c')
		len += ft_is_c((char)va_arg(args, int), fd);
	else if (*fmt == 'd' || *fmt == 'i')
		len += ft_is_di(va_arg(args, int), fd);
	else if (*fmt == 'p')
		len += ft_is_p(va_arg(args, void *), fd);
	else if (*fmt == 'u')
		len += ft_is_u(va_arg(args, unsigned int), fd);
	else if (*fmt == 'x')
		len += ft_is_xl(va_arg(args, unsigned long), fd);
	else if (*fmt == 'X')
		len += ft_is_xu(va_arg(args, unsigned long), fd);
	else if (*fmt == '%')
		len += ft_is_c('%', fd);
	return (len);
}
