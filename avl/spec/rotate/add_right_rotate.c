/*******************************************************
          (1)
          k2(fn)                          k1
        /   \                           /    \
    (1)k1    |C|              ==>    |A|      k2
      /  \   (h)                   (h+1)     /  \
   |A|    |B|                              |B|    |C|
   (h+1)  (h)                             (h)    (h)

 k1   k2   | A   B  C  |  k1  k2 |     H        | do
-------------------------------------------------------
 1    1    | h+1 h  h  |  0   0  | h+2 -> h+2   | break

*******************************************************/
void add_right_rotate(struct avl_node *fn, struct avl_node **root)
{
    struct avl_node *sfn = fn->p;
    struct avl_node **ppn = NULL;
    struct avl_node *k2 = fn;
    struct avl_node *k1 = k2->l;

    printf("add right rotate -> key(%d)!\r\n", fn->key);

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

    k1->factor = k2->factor = 0;
}