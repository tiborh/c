#ifndef STK_ERROR
#define STK_ERROR -32767
#endif

#ifndef MYSTACK_H
#define MYSTACK_H

/* incomplete type, to be fleshed out elsewhere */
typedef struct Stack Stack;

Stack* stk_create(int);
void stk_push(Stack*, int);
int stk_pop(Stack*);
int stk_top(Stack*);
int stk_size(Stack*);
int stk_error(Stack*);
void stk_destroy(Stack*);
#endif

