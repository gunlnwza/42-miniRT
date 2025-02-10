/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:27:14 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:30:34 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# include "conversion/conversion.h"


# include "ft_printf/ft_printf.h"


# include "ft_string/ft_string.h"


# include "get_next_line/get_next_line.h"


# include "list/list.h"


# include "memory/memory.h"


# include "putting/putting.h"


int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_isascii(int c);
int	ft_isinset(int c, char *set, int n);
int	ft_isprint(int c);
int	ft_islower(int c);
int	ft_isupper(int c);
int	ft_isspace(int c);


# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define ERROR -1

#endif
