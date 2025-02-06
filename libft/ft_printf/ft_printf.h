/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:40:19 by nteechar          #+#    #+#             */
/*   Updated: 2024/07/27 13:44:06 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

unsigned int	ft_printf(const char *format, ...);

// these functions will all return the length printed
unsigned int	put_char(unsigned char c);
unsigned int	put_str(const char *s);
unsigned int	put_address(void *ptr);
unsigned int	put_int(int n);
unsigned int	put_unsigned_int(unsigned int n);
unsigned int	put_hex(size_t n, int put_uppercase);

#endif
