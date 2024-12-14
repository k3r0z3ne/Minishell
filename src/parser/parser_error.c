#include "../../include/minishell.h"

bool	parser_error(t_token **tokens)
{
	if ((*tokens)->type == PIPE && (*tokens)->next && (*tokens)->next->type == PIPE)
		return (unexpected_token(tokens), true);
	else if ((*tokens)->type == PIPE && (!(*tokens)->next || (*tokens)->next->type == END))
		return (unexpected_token(tokens), true);
	else if (is_redirection2((*tokens)->type) && (!(*tokens)->next || !is_word((*tokens)->next->type)))
		return (unexpected_token(tokens), true);
	return (false);
}
