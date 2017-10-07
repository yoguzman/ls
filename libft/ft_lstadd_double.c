/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:55:08 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 18:55:11 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			ft_lstadd_double(t_list **alst, t_list *new)
{
	new->prev = NULL;
	new->next = *alst;
	(*alst)->prev = new;
	*alst = new;
}
