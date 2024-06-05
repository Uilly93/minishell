/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:19:38 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/05 15:23:49 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H

# define COLOR_H

// Couleurs du texte
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"

// Couleurs du texte en gras
# define BOLD_BLACK "\001\033[1;30m\002"
# define BOLD_RED "\001\033[1;31m\002"
# define BOLD_GREEN "\001\033[1;32m\002"
# define BOLD_YELLOW "\001\033[1;33m\002"
# define BOLD_BLUE "\001\033[1;34m\002"
# define BOLD_MAGENTA "\001\033[1;35m\002"
# define BOLD_CYAN "\001\033[1;36m\002"
# define BOLD_WHITE "\001\033[1;37m\002"

// Couleurs de fond
# define BG_BLACK "\001\033[40m\002"
# define BG_RED "\001\033[41m\002"
# define BG_GREEN "\001\033[42m\002"
# define BG_YELLOW "\001\033[43m\002"
# define BG_BLUE "\001\033[44m\002"
# define BG_MAGENTA "\001\033[45m\002"
# define BG_CYAN "\001\033[46m\002"
# define BG_WHITE "\001\033[47m\002"

// Couleurs de fond en haute intensité
# define BG_BRIGHT_BLACK "\001\033[0;100m\002"
# define BG_BRIGHT_RED "\001\033[0;101m\002"
# define BG_BRIGHT_GREEN "\001\033[0;102m\002"
# define BG_BRIGHT_YELLOW "\001\033[0;103m\002"
# define BG_BRIGHT_BLUE "\001\033[0;104m\002"
# define BG_BRIGHT_MAGENTA "\001\033[0;105m\002"
# define BG_BRIGHT_CYAN "\001\033[0;106m\002"
# define BG_BRIGHT_WHITE "\001\033[0;107m\002"

// Attributs de texte
# define RESET "\001\033[0m\002"
# define BOLD "\001\033[1m\002"
# define UNDERLINE "\001\033[4m\002"
# define REVERSED "\001\033[7m\002"

#endif // COLOR_H