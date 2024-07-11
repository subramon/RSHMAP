#ifndef __calc_new_size_H
#define __calc_new_size_H
extern int
calc_new_size(
    uint32_t nitems, 
    uint32_t maxsize, 
    uint64_t size, 
    uint32_t *ptr_newsize,
    bool *ptr_resize
    );
#endif
