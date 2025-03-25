#ifndef _PTR_LIST_H_
#define _PTR_LIST_H_

#include <stddef.h>

typedef struct _ptr_list_t_ {
    void** buffer;
    size_t len;
    size_t cap;
} ptr_list_t;

ptr_list_t* create_ptr_list(void);
void append_ptr_list(ptr_list_t* lst, void* ptr);
void* index_ptr_list(ptr_list_t* lst, int index);
void push_ptr_list(ptr_list_t* lst, void* ptr);
void* pop_ptr_list(ptr_list_t* lst);
void* peek_ptr_list(ptr_list_t* lst);
void* iterate_ptr_list(ptr_list_t* lst, int* post);
int len_ptr_list(ptr_list_t* lst);

#endif /* _PTR_LIST_H_ */
