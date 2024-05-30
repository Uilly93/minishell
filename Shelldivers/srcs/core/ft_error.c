/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:28:14 by nate              #+#    #+#             */
/*   Updated: 2024/05/02 04:32:43 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Print the error message and exit with an error
void    ft_error(char *str)
{
    ft_printf_fd(2,"\033[1m\033[37m Error \033[0m \n \033[1m\033[31m %s 033[0m \n", str);
    exit(1);
}