/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:27:58 by nsiefert          #+#    #+#             */
/*   Updated: 2024/05/02 02:58:02 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*\ -- ERROR-VALUES -- \*/
#define SUCCESS 0
#define ERROR 1
#define MALLOC_ERROR 2
#define FREE_ERROR 3
#define INVALID_COMMAND 4
#define GRAMMAR_ERROR 5
#define PARSING_ERROR 6

/*\ -- COLORS -- \*/
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

/*\ -- PATHS -- \*/
# define PATH1 "/home/nsiefert/.fzf/bin"
# define PATH2 "/home/nsiefert/bin"
# define PATH3 "/usr/local/sbin"
# define PATH3 "/usr/local/bin"
# define PATH4 "/usr/sbin"
# define PATH5 "/usr/bin"
# define PATH6 "/sbin"
# define PATH7 "/bin"
# define PATH8 "/usr/games"
# define PATH9 "/usr/local/games"
# define PATH10 "/snap/bin"

#endif