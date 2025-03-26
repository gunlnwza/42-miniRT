/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:42:39 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 11:41:31 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	is_valid_fov(char *fov_str)
{
	int		integer;
	char	*endptr;

	integer = ft_strtol(fov_str, &endptr);
	if (*endptr != '\0' || !is_in_rangef(1, 179, integer))
		return (FALSE);
	return (TRUE);
}

int	is_valid_ratio(char *ratio_str)
{
	double	decimal;
	char	*endptr;

	decimal = ft_strtod(ratio_str, &endptr);
	if (*endptr != '\0' || !is_in_rangef(0, 1, decimal))
		return (FALSE);
	return (TRUE);
}

int	is_valid_length(char *length_str)
{
	double	decimal;
	char	*endptr;

	decimal = ft_strtod(length_str, &endptr);
	if (*endptr != '\0' || decimal <= 0)
		return (FALSE);
	return (TRUE);
}
