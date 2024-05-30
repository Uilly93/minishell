/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:19:38 by wnocchi           #+#    #+#             */
/*   Updated: 2024/05/29 14:20:22 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H

# define COLOR_H

// Couleurs du texte
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

// Couleurs du texte en gras
# define BOLD_BLACK "\033[1;30m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_MAGENTA "\033[1;35m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_WHITE "\033[1;37m"

// Couleurs de fond
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"

// Couleurs de fond en haute intensité
# define BG_BRIGHT_BLACK "\033[0;100m"
# define BG_BRIGHT_RED "\033[0;101m"
# define BG_BRIGHT_GREEN "\033[0;102m"
# define BG_BRIGHT_YELLOW "\033[0;103m"
# define BG_BRIGHT_BLUE "\033[0;104m"
# define BG_BRIGHT_MAGENTA "\033[0;105m"
# define BG_BRIGHT_CYAN "\033[0;106m"
# define BG_BRIGHT_WHITE "\033[0;107m"

// Attributs de texte
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define REVERSED "\033[7m"

#endif // COLOR_H