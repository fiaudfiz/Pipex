/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:10:50 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 09:30:29 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const t_alias	g_format_tab[] = {
{'d', ft_format_d},
{'i', ft_format_i},
{'s', ft_format_s},
{'x', ft_format_x},
{'X', ft_format_big_x},
{'c', ft_format_c},
{'u', ft_format_u},
{'%', ft_format_percent},
{'p', ft_format_p},
{0, NULL}
};
