#ifndef __AVL_H__
#define __AVL_H__

struct avl_node{
    struct avl_node *p; /* parent */
    struct avl_node *l; /* left */
    struct avl_node *r; /* right */
    int factor;         /* balance factor */
    int key;            /* key value */
};

/* avl tree structure */
struct avl{
    struct avl_node *root;  /* tree root node */
};

void avl_init(struct avl *av);
int avl_add(struct avl *av, int key);
int avl_del(struct avl *av, int key);
int avl_size(struct avl *av);
/* iterate the whole tree for every node */
typedef int (* avl_iterate_cb_t)(struct avl_node *cn, void *user);
void avl_iterate(struct avl *av, avl_iterate_cb_t cb, void *user);
/* free the whole avl tree */
void avl_uninit(struct avl *av);

/****** for debug avl tree ******/
void avl_tree_print(struct avl *av);
void avl_table_print(struct avl *av);
#endif
