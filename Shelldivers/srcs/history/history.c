/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 03:09:38 by nsiefert          #+#    #+#             */
/*   Updated: 2024/05/02 01:32:21 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Trim the function to remove leading and trailing spaces and add it to the
// history if it is not empty.
// Return 0 if the string is not empty, 1 otherwise.
int history(char *str)
{
    int i;

    i = -1;
    str = ft_strtrim(str, " ");
    if (str)
    {
        add_history(str[i]);
        return (0);
    }
    return (1);
}
