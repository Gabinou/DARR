
#ifndef DARR_H
#define DARR_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// DARR: Dynamic arrays for C99.
// A darr is basically an array with two additional elements, allocated length and number of active element saved at positions -2 and -1 respectively. 
// Implementation is very simple, based on a limited number of macros.

#define DARR_GROWTH_FACTOR 2
#define DARR_PTR_SHIFT 2
#define DARR_LEN_INDEX -2
#define DARR_NUM_INDEX -1

#define DARR_LEN(darr) do {(*((size_t *)darr + DARR_LEN_INDEX))} while(0) // allocated length
#define DARR_NUM(darr) do {(*((size_t *)darr + DARR_NUM_INDEX))} while(0) // number of active elements

// DARR_INIT: a darr is an array with two size_t at indices -1 and -2.
#define DARR_INIT(darr, type, len) do {\
    (type*)(((size_t* )malloc(sizeof(size_t)*DARR_PTR_SHIFT + sizeof(type)*(len)))+DARR_PTR_SHIFT);\
    (*((size_t *)darr + DARR_LEN_INDEX)) = len;\
    (*((size_t *)darr + DARR_NUM_INDEX)) = 0;\
} while(0)

// DARR_REALLOC: DARR internal. Not to be called directly by users.
#define DARR_REALLOC(darr, len) do {\
    (void *)((size_t* )realloc(((size_t* )darr + DARR_LEN_INDEX), (sizeof(size_t)*DARR_PTR_SHIFT + (sizeof(*darr))*(len)))+DARR_PTR_SHIFT)\
} while(0)

// DARR_DEL_SCRAMBLE: delete elem by copying top element over it, and decrementing DARR_NUM
#define DARR_DEL_SCRAMBLE(darr, elem) do {\
    if (elem < DARR_NUM(darr)) {\
    darr = memmove((darr + elem), (darr + --DARR_NUM(darr)), sizeof(*darr));\
}\
} while(0)

// DARR_DEL: delete elem by moving all subsequent elements over
#define DARR_DEL(darr, elem) do {\
    memmove((darr + elem), (darr + elem + 1), sizeof(*darr) * (--DARR_NUM(darr) - elem))\
} while(0)

// DARR_GROW: double length of array (depending on DARR_GROWTH_FACTOR)
#define DARR_GROW(darr) do {\
    DARR_LEN(darr)*=DARR_GROWTH_FACTOR;\
    darr = DARR_REALLOC(darr, DARR_LEN(darr));\
} while(0)

// DARR_PUT: put elem on top of darr, at DARR_NUM
#define DARR_PUT(darr, elem) do {if ((DARR_NUM(darr) + 1) >= (DARR_LEN(darr))) {\
DARR_GROW(darr);\
}\
darr[DARR_NUM(darr)++] = elem;\
} while(0)

// DARR_POP: get top element of darr, and "remove" it by decrementing DARR_NUM
#define DARR_POP(darr) do {darr[--DARR_NUM(darr)]} while(0)

// DARR_FREE: free whole darr
#define DARR_FREE(darr) do {free((((size_t* )darr) + DARR_LEN_POSITION))} while(0)

#endif /* DARR_H */
