/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandatory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:48:03 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/05 11:52:19 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mandatory(const char *fmt, va_list args)
{
	int	len;

	len = 0;
	if (*fmt == 's')
		len += ft_is_s(va_arg(args, char *));
	else if (*fmt == 'c')
		len += ft_is_c((char)va_arg(args, int));
	else if (*fmt == 'd' || *fmt == 'i')
		len += ft_is_di(va_arg(args, int));
	else if (*fmt == 'p')
		len += ft_is_p(va_arg(args, void *));
	else if (*fmt == 'u')
		len += ft_is_u(va_arg(args, unsigned int));
	else if (*fmt == 'x')
		len += ft_is_xl(va_arg(args, unsigned long));
	else if (*fmt == 'X')
		len += ft_is_xu(va_arg(args, unsigned long));
	else if (*fmt == '%')
		len += ft_putchar('%');
	return (len);
}
