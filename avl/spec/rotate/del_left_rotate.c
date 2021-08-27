/*******************************************************
          -1         
          k1(fn)                         k2
        /   \                          /   \
     |A|     k2(-1|0)   ==>          k1     |C|
            /  \                    /  \
         |B|    |C|              |A|    |B|
 
 k1   k2   | A   B   C   |  k1  k2 |     H        | do
-------------------------------------------------------
-1   -1    | h   h   h+1 |  0   0  | h+3 -> h+2   | backtrace
-1    0    | h-1 h   h   | -1   1  | h+2 -> h+2   | break

*******************************************************/
void del_left_rotate(struct avl_node *fn, struct avl_node **root)
{
    struct avl_node *sfn = fn->p;
    struct avl_node **ppn = NULL;
    struct avl_node *k1 = fn;
    struct avl_node *k2 = k1->r;

    printf("del left rotate -> key(%d)!\r\n", fn->key);
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