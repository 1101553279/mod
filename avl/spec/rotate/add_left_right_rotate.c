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
----------------------------------------------------------------
-1  1   1   | h+1  h+1  h    h+1 | 0   0   -1  | h+3 -> h+3 | break;
~   0   ~   | h    h    h    h   | 0   0   0   | h+3 -> h+2 | break;  impossible
~  -1   ~   | h+1  h    h+1  h+1 | 1   0   0   | h+3 -> h+3 | break;

**********************************************************************/
void add_left_right_rotate(struct avl_node *fn, struct avl_node **root)
{
    struct avl_node *sfn = fn->p;
    struct avl_node **ppn = NULL;
    struct avl_node *k3 = fn;
    struct avl_node *k1 = k3->l;
    struct avl_node *k2 = k1->r;

    printf("add left(%d) right(%d) rotate!\r\n", fn->l->key, fn->key);
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
    else if(0 == k2->factor)        /* no possible when avl_add */
        k1->factor = k2->factor = k3->factor = 0;
    else
        k1->factor=1, k2->factor=0, k3->factor=0;

    return;
}