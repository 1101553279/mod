#include <stdio.h>
#include "avl.h"




int main(int argc, char *argv[])
{
    printf("this example is for AVL Tree usage!\r\n");
    struct avl t;

    avl_init(&t);

    avl_add(&t, 25);
    avl_tree_print(&t);
    avl_add(&t, 50);
    avl_tree_print(&t);
    /* left rotation */
    avl_add(&t, 75);
    avl_tree_print(&t);
    /* right left rotation */
    avl_add(&t, 85);
    avl_tree_print(&t);
    
    avl_add(&t, 65);
    avl_tree_print(&t);

    avl_add(&t, 55);
    avl_tree_print(&t);
    
    /* right rotation */
    avl_add(&t, 15);
    avl_tree_print(&t);
    
    avl_add(&t, 10);
    avl_tree_print(&t);
    
    /* left right rotation */
    avl_add(&t, 53);
    avl_tree_print(&t);
    
    avl_add(&t, 56);
    avl_tree_print(&t);
    
    avl_add(&t, 57);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_add(&t, 58);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_add(&t, 88);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_add(&t, 86);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_add(&t, 87);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_del(&t, 86);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_del(&t, 75);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_add(&t, 86);
    avl_tree_print(&t);
    
    avl_add(&t, 75);
    avl_tree_print(&t);
    
    avl_del(&t, 88);
    avl_tree_print(&t);
    
    avl_del(&t, 75);
    avl_tree_print(&t);
    
    avl_del(&t, 87);
    avl_tree_print(&t);
    
    avl_del(&t, 85);
    avl_tree_print(&t);
    
    avl_del(&t, 56);
    avl_tree_print(&t);

    avl_del(&t, 86);
    avl_tree_print(&t);
    avl_table_print(&t);

    printf("avl_size(&t) = %d\r\n", avl_size(&t));
    
    avl_uninit(&t);

#if 0
    avl_del(&t, 53);
    avl_tree_print(&t);
    avl_table_print(&t);
#endif

#if 0
    avl_del(&t, 53);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_del(&t, 10);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_del(&t, 50);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_del(&t, 15);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_add(&t, 28);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_del(&t, 56);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_del(&t, 57);
    avl_tree_print(&t);
    avl_table_print(&t);
#endif

#if 0
    avl_del(&t, 28);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_del(&t, 25);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_del(&t, 55);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_del(&t, 75);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_del(&t, 85);
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_del(&t, 65);
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_del(&t, 100);
    avl_tree_print(&t);
    avl_table_print(&t);
#endif
#if 0
    avl_add(&t, 25);
    avl_tree_print(&t);
    avl_add(&t, 50);
    avl_tree_print(&t);
    /* left rotation */
    avl_add(&t, 75);
    avl_tree_print(&t);
    /* right left rotation */
    avl_add(&t, 85);
    avl_tree_print(&t);
    
    avl_add(&t, 65);
    avl_tree_print(&t);

    avl_add(&t, 55);
    avl_tree_print(&t);
    
    /* right rotation */
    avl_add(&t, 15);
    avl_tree_print(&t);
    
    avl_add(&t, 10);
    avl_tree_print(&t);
    
    /* left right rotation */
    avl_add(&t, 53);
    avl_tree_print(&t);
    
    avl_add(&t, 56);
    avl_tree_print(&t);
    
    avl_add(&t, 57);
    avl_tree_print(&t);
    avl_table_print(&t);
#endif 

#if 0
    avl_add(&t, 1);
    avl_tree_print(&t);
    avl_add(&t, 2);
    avl_tree_print(&t);
    avl_add(&t, 3);
    avl_tree_print(&t);
#endif
#if 0
    avl_add(&t, 5);
    avl_add(&t, 2);
    avl_add(&t, 1);
    avl_add(&t, 3);
    avl_add(&t, 7);
    avl_add(&t, 6);
    avl_add(&t, 8);
    avl_tree_print(&t);
    avl_del(&t, 5);
    printf("after delete: \r\n");
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_rotate_right(&t, 3);
    printf("after rotate right(3):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_rotate_right(&t, 2);
    printf("after rotate right(2):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_rotate_right(&t, 1);
    printf("after rotate right(1):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_rotate_right(&t, 7);
    printf("after rotate right(7):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_rotate_right(&t, 10);
    printf("after rotate right(7):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);


    avl_rotate_left(&t, 1);
    printf("after rotate left(1):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_rotate_left(&t, 2);
    printf("after rotate left(2):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_rotate_left(&t, 10);
    printf("after rotate left(10):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_rotate_left(&t, 8);
    printf("after rotate left(8):\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_key_root(&t, 6);
    printf("after key(6) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_key_root(&t, 7);
    printf("after key(7) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_key_root(&t, 8);
    printf("after key(8) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
#endif
#if 0
    avl_key_root(&t, 8);
    printf("after key(8) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_key_root(&t, 7);
    printf("after key(8) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);

    avl_key_root(&t, 6);
    printf("after key(6) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_key_root(&t, 7);
    printf("after key(7) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
    
    avl_key_root(&t, 8);
    printf("after key(8) root:\r\n");
    avl_tree_print(&t);
    avl_table_print(&t);
#endif
    return 0;
}
