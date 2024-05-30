/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:36:56 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/05 11:52:29 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *s, ...)
{
	int	i;
	int	len;

	va_list(args);
	i = 0;
	len = 0;
	va_start(args, s);
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += ft_mandatory(&s[i++], args);
		}
		else
		{
			len += ft_putchar(s[i]);
			i++;
		}
	}
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	int	len;
// 	// char *ptr;

// 	len = ft_printf("%p", -1);
// 	// ft_printf("%d", len);

// 	printf("%p", -1);
// 	// ft_printf("%s\n%s\n%s\n", "salut", "les", "amis");
// }