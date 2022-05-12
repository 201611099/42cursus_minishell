/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:55:42 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 14:09:35 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
	
static char	*ft_strcat(char *dest, char *src)
{
	char* p_dest;
	char* p_src;

	p_dest = dest;
	while (*p_dest != '\0')
	{
		p_dest++;
	}
	p_src = src;
	while (*p_src != '\0')
	{
		*p_dest++ = *p_src++;
	}
	*p_dest = '\0';
	return dest;
}

static void print_tree_node(t_node* node, bool is_right, char *indent)
{
	char r_indent[512];
	char l_indent[512];
	
	ft_strlcpy(r_indent, indent , 512);
	ft_strlcpy(l_indent, indent , 512);
	if (node->right != NULL)
	{
		print_tree_node(node->right, true, ft_strcat(r_indent, is_right ? "        " : " |      "));
	}
	printf("%s", indent);
	if (is_right)
	{
		printf(" /");
	}
	else
	{
		printf(" \\");
	}
	printf("----- ");
	printf("[%s]\n", node->data);
	if (node->left != NULL)
	{
		print_tree_node(node->left, false, ft_strcat(l_indent, is_right ? "        " : " |      "));
	}
}

void	print_token(t_tok_list *list)
{
	t_tok *curr;
	int idx = 0;

	curr = list->head;
	while (curr)
	{
		printf("(%d/%d): %d\t| %s\n", idx, list->count, curr->type, curr->data);
		idx++;
		curr = curr->next;
	}
}

void	ft_lstprint_heredoc(t_list *list)
{
	t_list *cur;

	cur = list;
	while (cur)
	{
		printf("/=================\\\n");
		printf("fd : %d\n", ((t_heredoc *)cur->content)->fd);
		printf("row : %d\n", ((t_heredoc *)cur->content)->row);
		printf("col : %d\n", ((t_heredoc *)cur->content)->col);
		printf("h_name : %s\n", ((t_heredoc *)cur->content)->h_name);
		printf("line : %s\n", ((t_heredoc *)cur->content)->line);
		printf("eof : %s\n", ((t_heredoc *)cur->content)->eof);
		printf("\\=================/\n");
		cur = cur->next;
	}
	
}

void	print_tree(t_node* root)
{
	if (root->right != NULL)
	{
		print_tree_node(root->right, true, "");
	}
	printf("[%s]\n", root->data);
	if (root->left != NULL)
	{
		print_tree_node(root->left, false, "");
	}
	printf("\033[36mHeredoc count: %d\033[0m\n", get_info()->h_count);
}

void	print_err(char *line, int err)
{
	t_info	*info;
	
	info = get_info();
	ft_clear();
	free(line);
	line = NULL;
	if (err > 0)
		printf("\033[31m%s\033[0m\n", strerror(errno));
	else
		printf("\033[31mSyntax Error\033[0m\n");
}
