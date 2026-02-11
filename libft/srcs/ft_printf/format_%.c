/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_%.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:19:03 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 09:30:29 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_percent(char c)
{
	return (write (1, &c, 1));
}

int	ft_format_percent(va_list ap)
{
	(void)ap;
	return (ft_putchar_percent('%'));
}
