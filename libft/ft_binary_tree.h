#ifndef FT_BIN_TREE_H
# define FT_BIN_TREE_H

typedef struct s_binary_tree
{
	void					*content;
	struct s_binary_tree	*left;
	struct s_binary_tree	*right;
}	t_binary_tree;

t_binary_tree	*ft_binary_tree_new(void *content);
void			ft_binary_tree_clear(t_binary_tree **tree, void (*del)(void *));

void			ft_binary_tree_set_left(t_binary_tree *parent, t_binary_tree *child);
void			ft_binary_tree_set_right(t_binary_tree *parent, t_binary_tree *child);

#endif
