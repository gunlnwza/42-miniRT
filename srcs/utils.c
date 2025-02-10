/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:00:30 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 18:00:52 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

// would be removed

// For choice of params,
// Please refer to https://en.wikipedia.org/wiki/Linear_congruential_generator
unsigned int	ft_random_unsigned_int(void)
{
	static unsigned int	value = 42;

	value = 1664525 * value + 1013904223;
	return (value);
}

double	ft_random(void)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	temp;

	a = ft_random_unsigned_int();
	b = ft_random_unsigned_int();
	if (a > b)
	{
		temp = a;
		a = b;
		b = temp;
	}
	return ((double) a / b);
}

/*
// ft_random test
int	main()
{
	int	n = 10;
	int	times = 1000000;
	
	int	bin[n];
	ft_memset(bin, 0, n * sizeof(int));

	for (int i = 0; i < times; i++)
	{
		float val = ft_random();
		int	idx = (val * n);
		bin[idx] += 1;
		// printf("%i %f \n", i, val);
	}
	printf("\n");
	
	for (int i = 0; i < n; i++)
	{
		printf("bin[%i] = %i\n", i, bin[i]);
	}
}
*/
