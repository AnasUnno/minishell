/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:05:49 by kzerri            #+#    #+#             */
/*   Updated: 2023/09/22 00:24:31 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree *create(int val)
{
    t_tree *tree = (t_tree *)malloc(sizeof(t_tree));
    tree->data = val;
    tree->left = NULL;
    tree->right = NULL;
    return (tree);
}

int count(t_tree *tree)
{
    int i = 0;

    if (!(tree))
        return 0;
    return (count(tree->left) + count(tree->right)  + 1);
}

void insert(t_tree **tree, int val)
{
    if (!(*tree))
    {
        *tree = create(val);
        return ;
    }
    else if (val <= (*tree)->data)
        insert(&(*tree)->left, val);
    else
       insert(&(*tree)->right ,val);
}

void print(t_tree *tree)
{
    if (!tree)
        return ;
    print(tree->left);
    print(tree->right);
    printf("%d\n", tree->data);
}

void    in_order(t_tree *root, int *res)
{
  if (!root)
    return ;
  in_order(root->left, res);
  *res = root->data;
  res++;
  in_order(root->right, res);
}
int* inorderTraversal(t_tree *root, int* returnSize){

  *returnSize = count(root);
  int *res = (int *)malloc(sizeof(int) * (*returnSize));
  int *set = res;
  in_order(root, res);
  return res;
}
int main()
{
    t_tree *tree;
    tree = NULL;

    int arr[4] = {1, 2 , 3, 4};
    int i = -1;
    while (++i < 4)
        insert(&tree, arr[i]);
    // print(tree);
    int a;
    int *arr1 = inorderTraversal(tree, &a);
    int d = -1;
    while (++d < 4)
        printf("%d\n", arr1[d]);
    
    // printf("%d", count(tree));
}
