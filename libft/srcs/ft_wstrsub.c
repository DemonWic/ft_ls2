/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:01:46 by ahintz            #+#    #+#             */
/*   Updated: 2019/11/16 15:01:48 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t	*ft_wstrsub(wchar_t *s, unsigned start, unsigned len)
{
	wchar_t		*str;
	unsigned	i;

	if (!(str = ft_memalloc(sizeof(wchar_t) * (len + 1))))
		return (NULL);
	i = 0;
	while (ft_wcharlen(s[i + start]) < len)
	{
		str[i] = s[i + start];
		i += ft_wcharlen(str[i]);
	}
	str[i] = '\0';
	return (str);
}
