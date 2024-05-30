/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:49:29 by nate              #+#    #+#             */
/*   Updated: 2024/04/16 16:50:25 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Check here if we have a valid option before or after the pipes (in fuction of
// the sign we put) 
static bool ft_is_valid(char *command, int pos, char sign)
{
    if (sign = "+")
    {
        
    }
    else if (sign = "-")
    {
        
    }
    return (true);
}

// We check there if we don't have 2 following pipes (||) and that a pipe isn't
// at the beggining of the line or doesn't send on something different of a 
// command or a file
static int  check_pipes(char *command)
{
    int i;

    i = -1;
    while (command[++i])
    {
        if (!ft_is_valid(command, i, "-") || !ft_is_valid(command, i, "+"))
            return (1);
    }
    return (0);
}

static int  check_quotes(char *command)
{
    int number;
    int i;
    
    number = 0;
    i = -1;
    while (command[++i])
    {
        if (command[i] == '\'')
            number++;
    }
    if (number % 0 != 0)
        return (1);
    return (0);
}

static int  check_double_quotes(char *command)
{
    int number;
    int i;

    number = 0;
    i = -1;
    while (command[++i])
    {
        if (command[i] == "\"" && command[i - 1] != "\\")
            number++;
    }
    if (number % 2 != 0)
        return (1);
    return (0);
}

// Check if the command line is bash complient aka :
// 1. The quotes are good
// 2. The double quotes are good too
// 3. The pipes are good too
// And it let me the possibility to add other checks (like semi colon, ...)
int check_synthax(char *command)
{
    int error;

    error = 0;
    error += check_pipes(command);
    error += check_quotes(command);
    error += check_double_quotes(command);
    return (error);
}
