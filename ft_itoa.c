/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbelva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:59:33 by cbelva            #+#    #+#             */
/*   Updated: 2020/11/03 12:30:08 by cbelva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_count_digits(int number, int is_minus)
{
	size_t	len;

	len = 1;
	number /= 10;
	while (number)
	{
		number /= 10;
		len++;
	}
	if (is_minus)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	size_t	len;
	long	number;
	int		is_minus;
	char	*result;
	char	*iter;

	is_minus = n < 0;
	number = n < 0 ? -n : n;
	len = ft_count_digits(number, is_minus);
	result = (char*)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	iter = result + len;
	*(iter--) = '\0';
	number = is_minus ? -(long)n : n;
	*(iter--) = number % 10 + '0';
	number /= 10;
	while (number)
	{
		*(iter--) = number % 10 + '0';
		number /= 10;
	}
	if (is_minus)
		*iter = '-';
	return (result);
}
