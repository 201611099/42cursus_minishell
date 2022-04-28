/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:39:28 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/28 12:20:15 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <string.h>
# include <sys/errno.h>
# include "../libft/libft.h"
# include "./astree.h"

# define REPLACE 1

typedef struct s_info
{
	t_tok_list	*list;
	t_astree	*tree;
	t_list		*env_list;
	int			exitcode;
}	t_info;

typedef struct s_enode
{
	char	*key;
	char	*value;
}	t_enode;

/*
 * main.c
 */
void	print_err(int err);

/*
** list.c
*/
void	add_token(t_tok_list **list, t_tok *new_tok);
t_tok_list *create_list(void);
t_tok	*get_token(t_tok_list *list, int pos);
void	list_clear(t_tok_list *list);

/*
** tokenize.c
*/
void	tokenize(t_tok_list **list, char *str);
int		ft_isblank(char c);

/*
** quotecheck.c
*/
int	check_quote(char *str);

/*
** syntax.c
*/
int		syntax(t_info *info);
void	pipeline(t_info *info, int *idx);
void	cmd(t_info *info, int *idx);
void	simple_cmd(t_info *info, int *idx);
void	redir(t_info *info, int *idx);
void	redirs(t_info *info, int *idx);
void	args(t_info *info, int *idx);
void	path(t_info *info, int *idx);
void	filename(t_info *info, int *idx);

/*
** util.c
*/
void	print_token(t_tok_list *list);
void	print_tree(t_node* root);
void	as_print(t_node *syntax);
void	ft_clear(t_info *info);

/*
** semantic.c
*/
int		chk_syntax(t_node *node);

/*
** replace_env.c
*/
void	replace_recur(t_info *info, t_node *node);

/*
** env_list.c
*/
void	env_preprocess(t_info *info, char **envp);
char	*get_env(t_info *info, char *name);


#endif
