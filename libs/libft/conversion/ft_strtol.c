/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:54:21 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/02/25 18:11:27 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

static int	convert_digit(char c, int base)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (base == 16 && c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (base == 16 && c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

static long	convert_to_long(const char *str, int *i, int base)
{
	long	result;
	int		digit;

	result = 0;
	while (str[*i] != '\0')
	{
		digit = convert_digit(str[*i], base);
		if (digit < 0)
			break ;
		if (result > (LONG_MAX - digit) / 10)
		{
			result = LONG_MAX;
			break ;
		}
		result = result * 10 + digit;
		(*i)++;
	}
	return (result);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	sign = parse_sign(&str + i);
	result = convert_to_long(str, &i, base);
	if (endptr)
		*endptr = (char *)&str[i];
	return (result * sign);
}
