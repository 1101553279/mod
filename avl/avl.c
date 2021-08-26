#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static int avl_del_balance(struct avl_node *cn, struct avl_node **root);
static void right_rotate(struct avl_node *fn, struct avl_node **root);
static void left_right_rotate(struct avl_node *fn, struct avl_node **root);
static void left_rotate(struct avl_node *fn, struct avl_node **root);
static void right_left_rotate(struct avl_node *fn, struct avl_node **root);
static struct avl_node *node_new(int key, struct avl_node *fn);
static int table_line_print_iterate_cb(struct avl_node *cn, void *user);
static void tree_node_recursive(struct avl_node *n, int level);
static void tree_node_print(struct avl_node *n, int level, const char *fmt, ...);
static int size_iterate_cb(struct avl_node *cn, void *user);

/******************************************************************************
* brief    : init a avl tree
* Param    : 
* Return   :
* Note     :
******************************************************************************/
void avl_init(struct avl *av)
{
    if(NULL != av)
        av->root = NULL;

    return;
}

/******************************************************************************
* brief    : add a key into avl tree
* Param    : 
* Return   :
* Note     :
******************************************************************************/
int avl_add(struct avl *av, int key)
{
    struct avl_node **ppn = &av->root;
    struct avl_node *fn = NULL;     /* father node */
    struct avl_node *cn = NULL;     /* current node */

    while(NULL != (*ppn))
    {
        if(key < (*ppn)->key) 
            fn = *ppn, ppn = &(*ppn)->l;
        else if((*ppn)->key < key)
            fn = *ppn, ppn = &(*ppn)->r;
        else
            break;
    }
    
    if(NULL != (*ppn))
    {
        printf("add: key(%d) has been added -> ignore!\r\n", key);
        return -1;
    }

    printf("add: key(%d)\r\n", key);
    *ppn = node_new(key, fn);

    /* do add balance */
    cn = *ppn;
    while(NULL != (fn=cn->p))
    {
        if(cn == fn->l)
        {
            if(1 == fn->factor)
            {
                if(-1 == cn->factor)
                    left_right_rotate(fn, &av->root);
                else if(1 == cn->factor)
                    right_rotate(fn, &av->root);
                else
                    ;            /* impossible */
                break;
            }
            else if(-1 == fn->factor)
            {
                fn->factor = 0;
                break;
            }
            else
                fn->factor = 1;
        }
        else
        {
            if(-1 == fn->factor)
            {
                if(1 == cn->factor)
                    right_left_rotate(fn, &av->root);
                else if(-1 == cn->factor)
                    left_rotate(fn, &av->root);
                else
                    ;           /* impossible */
                break;
            }
            else if(1 == fn->factor)
            {
                fn->factor = 0;
                break;
            }
            else
                fn->factor = -1;
        }

        cn = cn->p;     /* continue backtrace: update father node's factor */
    }
    

    return 0;
}

/******************************************************************************
* brief    : do balance after del a node 
* Param    : 
* Return   :
* Note     :
******************************************************************************/
static int avl_del_balance(struct avl_node *cn, struct avl_node **root)
{
    struct avl_node *fn;            /* father node */
    struct avl_node *sn = NULL;     /* slibing node */

    while(NULL!=cn && NULL!=(fn=cn->p))
    {
        if(cn == fn->l)
        {
            if(-1 == fn->factor)    /* cn==fn->l && -1==fn->factor indicating that sn is not NULL */
            {
                sn = fn->r;
                if(0==sn->factor) 
                {
                    left_rotate(fn, root);
                    break;          /* stop backtrace : height is not changed*/
                }
                else if(-1 == sn->factor)
                {
                    left_rotate(fn, root);
                    cn = cn->p;     /* must do: update factor from cn->father */
                }
                else if(1 == sn->factor)
                {
                    right_left_rotate(fn, root);
                    cn = cn->p;     /* must do: update factor from cn->father */
                }
            }
            else if(0 == fn->factor)
            {
                fn->factor = -1;
                break;
            }
            else
                fn->factor = 0;
        }
        else
        {
            if(1 == fn->factor)     /* cn==fn->r && 1==fn->factor indicating that sn is not NULL */
            {
                sn = fn->l;
                if(0 == sn->factor)
                {
                    right_rotate(fn, root);
                    break;          /* stop backtrace : height is not changed*/
                }
                else if(1 == sn->factor)
                {
                    right_rotate(fn, root);
                    cn = cn->p;     /* must do: update factor from cn->father */
                }
                else if(-1 == sn->factor)
                {
                    left_right_rotate(fn, root);
                    cn = cn->p;     /* must do: update factor from cn->father */
                }
            }
            else if(0 == fn->factor)
            {
                fn->factor = 1; 
                break;
            }
            else
                fn->factor = 0;
        }

        cn = cn->p;     /* continue backtrace: update father node's factor */
    }

    return 0;
}

/******************************************************************************
* brief    : del a key from avl tree
* Param    : 
* Return   :
* Note     :
******************************************************************************/
int avl_del(struct avl *av, int key)
{
    struct avl_node *cn = NULL;     /* current node */
    struct avl_node *fn = NULL;     /* father node */
    struct avl_node **ppn = &av->root; 
    struct avl_node *nn = NULL;     /* next node */

    while(NULL != *ppn)
    {
        if(key < (*ppn)->key)
            ppn = &(*ppn)->l;
        else if((*ppn)->key < key)
            ppn = &(*ppn)->r;
        else
            break;
    }
    if(NULL == *ppn)
    {
        printf("del: key(%d) is not found!\r\n", key);
        return -1;
    }

    cn = *ppn;
    if(NULL!=cn->l && NULL!=cn->r)
    {
        ppn = &cn->l;
        while(NULL != (*ppn)->r)
            ppn = &(*ppn)->r;
        cn->key = (*ppn)->key;
        cn = *ppn;
    }
    
    nn = (NULL==cn->l)? cn->r: cn->l;
    if(NULL == nn)  /* deleted node has no child, responding to if(NULL != nn) as following */
        avl_del_balance(cn, &av->root);

    fn = cn->p;     /* record deleted's father node */
    if(NULL != fn)
        ppn = (cn==fn->l)? &(fn->l): &(fn->r);
    else 
        ppn = &av->root;
    *ppn = nn;      /* remove cn node from tree */

    if(NULL != nn)  /* deleted node has one child */
    {
        nn->p = fn;
        avl_del_balance(nn, &av->root);
    }

    free(cn);

    return 0;
}

/******************************************************************************
* brief    : get avl tree size
* Param    : 
* Return   :
* Note     :
******************************************************************************/
int avl_size(struct avl *av)
{
    int size = 0;

    avl_iterate(av, size_iterate_cb, &size);

    return size;
}

/******************************************************************************
* brief    : iterate avl tree, call cb callback for every node 
* Param    : 
* Return   :
* Note     :
******************************************************************************/
void avl_iterate(struct avl *av, avl_iterate_cb_t cb, void *user)
{
    struct avl_node *pn = NULL;
    struct avl_node *cn = av->root;

    while(NULL != cn)
    {
        if(NULL == cn->l)
        {
            cb(cn, user);       /* call function */
            cn = cn->r;
        }
        else
        {
            pn = cn->l;         /* find previous node of current node */
            while(NULL!=pn->r && cn!=pn->r)
                pn = pn->r;
            if(NULL == pn->r)   /* first meet, change cn->r = cn */
            {
                pn->r = cn;
                cn = cn->l;
            }
            else                /* second meet, change cn->r = NULL back */
            {
                pn->r = NULL;
                cb(cn, user);   /* call function */
                cn = cn->r;
            }
        }
    }
    
    return;
}

/******************************************************************************
* brief    : free the whole avl tree
* Param    : 
* Return   :
* Note     :
******************************************************************************/
void avl_uninit(struct avl *av)
{
    struct avl_node *sn = NULL;     /* save node */
    struct avl_node *pn = NULL;     /* previous node */
    struct avl_node *cn = av->root; /* current node */
    
    while(NULL != cn)
    {
        if(NULL == cn->l)
        {
            sn = cn;
            printf("free node : %d\r\n", sn->key);
            cn = cn->r;
            free(sn);
        }
        else
        {
            pn = cn->l; /* find the previous node of current node */
            while(NULL != pn->r)
                pn = pn->r;
            sn = cn->l; 
            cn->l = NULL;
            pn->r = cn;
            cn = sn;
        }
    }

    av->root = NULL;    /* do for safety */

    return;
}


/******************************************************************************
* brief    : print avl tree by tree graph
* Param    : 
* Return   :
* Note     :
******************************************************************************/
void avl_tree_print(struct avl *av)
{
    printf("*** tree ***\r\n");
    tree_node_recursive(av->root, 1);

    return;
}

/******************************************************************************
* brief    : print avl tree by table graph
* Param    : 
* Return   :
* Note     :
******************************************************************************/
void avl_table_print(struct avl *av)
{
    printf("---------------------------------------------------"
           "------------------\r\n");
    printf("%-10s | %-10s | %-10s | %-10s | %-10s | %-10s \r\n", 
            "parent", "left", "current", "right", "factor", "key");
    printf("---------------------------------------------------"
           "------------------\r\n");
    avl_iterate(av, table_line_print_iterate_cb, NULL);

    return;
}

/*******************************************************
          (1)                     
          k2(fn)                        k1
        /   \                         /    \
    (1)k1    |C|          ==>      |A|      k2
      /  \   (h)                 (h+1)     /  \
   |A|    |B|                            |B|    |C|
   (h+1)  (h)                           (h)    (h)

 k1   k2   | A   B  C   |  k1  k2 |     H        | do
---del--------------------------------------------------
 0    1    | h   h  h-1 | -1   1  | h+2 -> h+2   | break
 1    1    | h+1 h  h   |  0   0  | h+3 -> h+2   | backtrace
---add--------------------------------------------------
 1    1    | h+1 h  h   |  0   0  | h+2 -> h+2   | break

*******************************************************/
static void right_rotate(struct avl_node *fn, struct avl_node **root)
{
    struct avl_node *sfn = fn->p;
    struct avl_node **ppn = NULL;
    struct avl_node *k2 = fn;
    struct avl_node *k1 = k2->l;

    printf("right rotate -> key(%d)!\r\n", fn->key);

    if(NULL != sfn)
        ppn = (sfn->l==fn)? &(sfn->l): &sfn->r;
    else
        ppn = root;
    
    /* k2 node */
    k2->l = k1->r;
    if(k1->r)
        k1->r->p = k2;

    /* k1 node */
    k1->r = k2;
    k2->p = k1;
    
    *ppn = k1;
    k1->p = sfn;

    if(0 == k1->factor)
        k1->factor=-1, k2->factor=1;
    else
        k1->factor = k2->factor = 0;
}

/*********************************************************************
         (1)             
          k3(fn)                            k2
        /   \                            /      \
   (-1)k1    |D|         ==>           k1         k3
      /   \                           /  \       /  \
   |A|     k2                       |A|   |B|  |C|  |D|
          /  \
       |B|    |C|

k1  k2  k3  | A    B    C    D   | k1  k2  k3  |   H        |  do
---del-----------------------------------------------------------
-1  -1  1   | h+1  h    h+1  h+1 | 1   0   0   | h+4 -> h+3 | backtrace
-1  0   1   | h    h    h    h   | 0   0   0   | h+3 -> h+2 | backtrace
-1  1   1   | h+1  h+1  h    h+1 | 0   0   -1  | h+4 -> h+3 | backtrace
---add-----------------------------------------------------------
-1  1   1   | h+1  h+1  h    h+1 | 0   0   -1  | h+3 -> h+3 | break;
-1  0   1   | h    h    h    h   | 0   0   0   | h+3 -> h+2 | break;  impossible
-1 -1   1   | h+1  h    h+1  h+1 | 1   0   0   | h+3 -> h+3 | break;

**********************************************************************/
static void left_right_rotate(struct avl_node *fn, struct avl_node **root)
{
    struct avl_node *sfn = fn->p;
    struct avl_node **ppn = NULL;
    struct avl_node *k3 = fn;
    struct avl_node *k1 = k3->l;
    struct avl_node *k2 = k1->r;

    printf("left(%d) right(%d) rotate!\r\n", fn->l->key, fn->key);
    if(NULL != sfn)
        ppn = (sfn->l==fn)? &(sfn->l): &(sfn->r);
    else
        ppn = root;

    /* k1 node */
    k1->r = k2->l; 
    if(NULL != k2->l)
        k2->l->p = k1;
    k1->p = k2;

    /* k3 node */
    k3->l = k2->r;
    if(NULL != k2->r)
        k2->r->p = k3;
    k3->p = k2;

    /* k2 node */
    k2->l = k1; 
    k2->r = k3;
    k2->p = sfn;

    *ppn = k2;

    if(1 == k2->factor)
        k1->factor=0, k2->factor=0, k3->factor=-1;
    else if(0 == k2->factor)                /* impossible when avl_add */
        k1->factor = k2->factor = k3->factor = 0;
    else
        k1->factor=1, k2->factor=0, k3->factor=0;

    return;
}

/*******************************************************
          -1         
          k1(fn)                         k2
        /   \                          /   \
     |A|     k2(-1|0)   ==>          k1     |C|
            /  \                    /  \
         |B|    |C|              |A|    |B|
 
 k1   k2   | A   B   C   |  k1  k2 |     H        | do
---del-------------------------------------------------
-1   -1    | h   h   h+1 |  0   0  | h+3 -> h+2   | backtrace
-1    0    | h-1 h   h   | -1   1  | h+2 -> h+2   | break
---add-------------------------------------------------
-1   -1    | h   h   h+1 |  0   0  | h+2 -> h+2   | break

*******************************************************/
static void left_rotate(struct avl_node *fn, struct avl_node **root)
{
    struct avl_node *sfn = fn->p;
    struct avl_node **ppn = NULL;
    struct avl_node *k1 = fn;
    struct avl_node *k2 = k1->r;

    printf("left rotate -> key(%d)!\r\n", fn->key);
    if(NULL != sfn) 
        ppn = (fn==sfn->l)? &sfn->l: &sfn->r;
    else
        ppn = root;

    /* k1 node */
    k1->r = k2->l;
    if(NULL != k2->l)
        k2->l->p = k1;

    /* k2 node */
    k2->l = k1;
    k1->p = k2;

    k2->p = sfn;
    *ppn = k2;

    if(-1 == k2->factor)
        k1->factor = k2->factor = 0;
    else
        k1->factor=-1, k2->factor=1;
}
/**********************************************************************
            -1
             k1(fn)                        k2
           /    \                       /     \
        |A|       k3(1)               k1         k3
                /   \       ==>     /   \        /  \
             k2      |D|        |A|      |B|  |C|    |D|
            /  \
         |B|    |C|

k1  k2  k3  | A    B    C    D   | k1  k2  k3  |   H        |  do
---del----------------------------------------------------------
-1  1   1   | h+1  h+1  h    h+1 | 0   0   -1  | h+4 -> h+3 | backtrace;
-1  0   1   | h    h    h    h   | 0   0   0   | h+3 -> h+2 | backtrace;
-1 -1   1   | h+1  h    h+1  h+1 | 1   0   0   | h+4 -> h+3 | backtrace;
---add----------------------------------------------------------
-1  1   1   | h+1  h+1  h    h+1 | 0   0   -1  | h+3 -> h+3 | break;
-1  0   1   | h    h    h    h   | 0   0   0   | h+3 -> h+2 | break;  impossible
-1 -1   1   | h+1  h    h+1  h+1 | 1   0   0   | h+3 -> h+3 | break;

**********************************************************************/
static void right_left_rotate(struct avl_node *fn, struct avl_node **root)
{
    struct avl_node *sfn = fn->p;
    struct avl_node **ppn = NULL;
    struct avl_node *k1 = fn;
    struct avl_node *k3 = k1->r;
    struct avl_node *k2 = k3->l;

    printf("right(%d) left(%d) rotate!\r\n", fn->r->key, fn->key);
    if(NULL != sfn)
        ppn = (fn==sfn->l)? &(sfn->l): &(sfn->r);
    else
        ppn = root;

    /* k1 node */
    k1->r = k2->l;
    if(NULL != k2->l)
        k2->l->p = k1;
    k1->p = k2;

    /* k3 node */
    k3->l = k2->r;
    if(NULL != k2->r)
        k2->r->p = k3;
    k3->p = k2;
    
    /* k2 node */
    k2->l = k1;
    k2->r = k3;
    k2->p = sfn;

    *ppn = k2;
    if(1 == k2->factor)
        k1->factor=0, k2->factor=0, k3->factor=-1;
    else if(0 == k2->factor)
        k1->factor = k2->factor = k3->factor = 0;
    else
        k1->factor=1, k2->factor=0, k3->factor=0;

    return;
}

static int size_iterate_cb(struct avl_node *cn, void *user)
{
    *(int *)(user) += 1;

    return 0;
}

static struct avl_node *node_new(int key, struct avl_node *fn)
{
    struct avl_node *cn = (struct avl_node *)malloc(sizeof(struct avl_node));
    if(NULL != cn)
    {
        cn->p = fn;
        cn->l = NULL;
        cn->r = NULL;
        cn->factor = 0;
        cn->key = key;
    }

    return cn;
}

static int table_line_print_iterate_cb(struct avl_node *cn, void *user)
{
    printf("%-10p : %-10p : %-10p : %-10p : %-10d : %-10d \r\n", 
            cn->p, cn->l, cn, cn->r, cn->factor, cn->key);

    return 0;
}

static void tree_node_recursive(struct avl_node *n, int level)
{
    if(NULL == n)
        tree_node_print(n, level, "%c\r\n", '~');
    else
    {
        tree_node_recursive(n->r, level+1);
        tree_node_print(n, level, "%d(%d)\r\n", n->key, n->factor);
        tree_node_recursive(n->l, level+1);
    }

    return;
}

static void tree_node_print(struct avl_node *n, int level, const char *fmt, ...)
{
    va_list ap;
    int i = 0;

    for(i=0; i < level; i++)
        putchar('\t');

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    return;
}

