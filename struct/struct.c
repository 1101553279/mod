
// put structure into structure
struct stack{ 
    int count;                  // element number
    struct elem {               // element
        void *x;                // element context
        struct elem *link;      // for element link list
    } *head;                    // elemnt link list head
};

