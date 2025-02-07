/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:05 by xenon             #+#    #+#             */
/*   Updated: 2025/02/05 18:22:31 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	err_exit(char *err_message)
{
	perror(err_message);
	exit(EXIT_FAILURE);
}

int	err_return(char *err_message)
{
	perror(err_message);
	return (1);
}
