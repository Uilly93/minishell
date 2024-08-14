/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:42:48 by tchalaou          #+#    #+#             */
/*   Updated: 2024/08/14 16:07:14 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_command(t_msh *msh, t_token **token)
{
	int	i;

	if (msh->cmd)
		free_tab(msh->cmd);
	msh->cmd = ft_calloc(sizeof(char *), (count_words(*token) + 1));
	if (!msh->cmd)
		return ;
	i = 0;
	while (*token && (*token)->id == WORD)
	{
		if (msh->cmd[i])
			free(msh->cmd[i]);
		msh->cmd[i] = NULL;
		msh->cmd[i] = ft_strdup((*token)->word);
		*token = (*token)->next;
		i++;
	}
}

int	fill_smaller(t_msh *msh, t_token **token)
{
	*token = (*token)->next;
	if (!*token)
		return (set_excode(&msh->env, 2),
			ft_printf(2, "msh: parsing error\n"), 1);
	if ((*token)->id == SMALLER)
	{
		*token = (*token)->next;
		msh->here_doc = 1;
	}
	if (!*token)
		return (set_excode(&msh->env, 2),
			ft_printf(2, "msh: parsing error\n"), 1);
	if ((*token)->id == WORD)
	{
		if (msh->infile)
			free(msh->infile);
		msh->infile = NULL;
		msh->infile = ft_strdup((*token)->word);
	}
	else
		return (set_excode(&msh->env, 2),
			ft_printf(2, "msh: parsing error\n"), 1);
	*token = (*token)->next;
	return (0);
}

int	fill_bigger(t_msh *msh, t_token **token)
{
	*token = (*token)->next;
	if (!*token)
		return (set_excode(&msh->env, 2),
			ft_printf(2, "msh: parsing error\n"), 1);
	if ((*token)->id == BIGGER)
	{
		*token = (*token)->next;
		msh->append = 1;
	}
	if (!*token)
		return (set_excode(&msh->env, 2),
			ft_printf(2, "msh: parsing error\n"), 1);
	if ((*token)->id == WORD)
	{
		if (msh->outfile)
			free(msh->outfile);
		msh->outfile = NULL;
		msh->outfile = ft_strdup((*token)->word);
	}
	else
		return (set_excode(&msh->env, 2),
			ft_printf(2, "msh: parsing error\n"), 1);
	*token = (*token)->next;
	return (0);
}

int	fill_msh(t_msh *msh, t_token **token)
{
	while (*token)
	{
		if ((*token)->id == WORD)
			fill_command(msh, token);
		else if ((*token)->id == SMALLER)
		{
			if (fill_smaller(msh, token))
				return (1);
		}
		else if ((*token)->id == BIGGER)
		{
			if (fill_bigger(msh, token))
				return (1);
		}
		else if ((*token)->id == PIPE)
		{
			*token = (*token)->next;
			return (0);
		}
		else
			*token = (*token)->next;
	}
	return (0);
}
