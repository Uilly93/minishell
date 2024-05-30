/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:32:05 by nate              #+#    #+#             */
/*   Updated: 2024/05/02 04:34:14 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int    ft_check_quotes(char *str)
{
    int nb_sq;
    int nb_dq;
    int i;

    nb_sq = 0;
    nb_dq = 0;
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\'' && str[i - 1] != "\\")
            nb_sq = (nb_sq + 1) % 2;
        else if (str[i] == "\"" && str[i - 1] != "\\")
        {
            if (nb_sq == 1)
                return (PARSING_ERROR);
            nb_dq = (nb_dq + 1) % 2;
        }
    }
    if (nb_dq % 2 != 0 || nb_sq % 2 != 0)
        return (PARSING_ERROR);
    return (0);
}

static int check_synthax(char *str)
{
    int     error;
    int     i;
    char    **tab;

    tab = ft_split(str, '|');
    i = -1;
    while (tab[++i])
    {
        if (tab[i][0] == '\0')
            return (PARSING_ERROR);
        else if (ft_check_quotes(tab[i]))
            return (PARSING_ERROR);
    }
}

pid_t   lexer(char *str, t_data *data)
{
    char    **tab;
    pid_t   pid;

    if (check_synthax(str))
    {
        ms_sig.exit_status = 2;
        ft_error_free("Syntax Error");
    }
    tab = ft_split(str, '|');
    pid = pars(tab, data);
    return (pid);
}
