/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:11:53 by yson              #+#    #+#             */
/*   Updated: 2022/05/04 21:31:57 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export(t_info *info, char *data)
{
	t_enode *node;
	t_list	*cur;

	if (data[0] == '=')
	{
		printf("bash: export: '%s': not a valid identifier\n", data);
		return ;
	}
	if (!ft_strchr(data, '='))
		return ;
	cur = info->env_list;
	node = new_enode(data);
	while (cur && ft_strcmp(node->key, ((t_enode *)cur->content)->key))
		cur = cur->next;
	if (!cur)
		ft_lstadd_back(&(info->env_list), ft_lstnew(node));
	else
	{
		free_enode(cur->content);
		cur->content = node;
	}
}

void	builtin_export(t_info *info, t_node *cmd)
{
	t_node	*node;

	node = cmd->left;
	while (node)
	{
		ft_export(info, node->data);
		node = node->left;
	}
}
