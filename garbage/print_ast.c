/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:07:26 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/15 11:32:01 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// void	print_ast(t_list *node, int depth)
// {
// 	while (node)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("	");
// 		if (node->content)
// 			printf("- %s\n", (char *)node->content);
// 		else
// 			printf("- (group)\n");
// 		if (node->arr)
// 		{
// 			printf("	Array elements:\n");
// 			for (int i = 0; node->arr[i] != NULL; i++)
// 			{
// 				for (int j = 0; j < depth + 1; j++)
// 					printf("	");
// 				printf("- %s\n", node->arr[i]);
// 			}
// 		}
// 		if (node->child)
// 			print_ast(node->child, depth + 1);
// 		node = node->next;
// 	}
// }
