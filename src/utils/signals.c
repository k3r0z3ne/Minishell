/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:55:04 by witong            #+#    #+#             */
/*   Updated: 2025/02/01 17:52:59 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
	rl_redisplay();
	g_signal = 128 + SIGINT;
}

void	setup_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		err_exit("sigaction");
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		err_exit("sigaction");
}
void	ignore_ctrl_c(void)
{
	struct sigaction sa_int;

	sa_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
}

void	activate_ctrl_c(void)
{
	struct sigaction sa_int;

	sa_int.sa_handler = SIG_DFL;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		err_exit("sigaction");
}

void	activate_ctrl_backslash(void)
{
	struct sigaction sa_quit;

	sa_quit.sa_handler = SIG_DFL;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		err_exit("sigaction");
}
// Ajouter activate_ctrl_backslash et activate_ctrl_c au debut des childs
// A AJOUTER A LA FIN DES CHILDS
// if (WIFSIGNALED(status))
// 	g_signal = WTERMSIG(status) + 128;


