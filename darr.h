
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

#define DARR_LEN(arr) (*((size_t *)arr + DARR_LEN_INDEX)) // allocated length
#define DARR_NUM(arr) (*((size_t *)arr + DARR_NUM_INDEX)) // number of active elements

// DARR_INIT: a darr is an array with two size_t at indices -1 and -2.
//    EX: uint8_t * test_arr = DARR_INIT(test_arr, uint8_t, test_arr_len);
#define DARR_INIT(arr, type, len) (type*)(((size_t* )malloc(sizeof(size_t)*DARR_PTR_SHIFT + sizeof(type)*(len)))+DARR_PTR_SHIFT);\
    (*((size_t *)arr + DARR_LEN_INDEX)) = len;\
    (*((size_t *)arr + DARR_NUM_INDEX)) = 0;

// DARR_REALLOC: DARR internal. Not to be called directly by users.
#define DARR_REALLOC(arr, len) (void *)((size_t* )realloc(((size_t* )arr + DARR_LEN_INDEX), (sizeof(size_t)*DARR_PTR_SHIFT + (sizeof(*arr))*(len)))+DARR_PTR_SHIFT)

// DARR_DEL_SCRAMBLE: delete elem by copying top element over it, and decrementing DARR_NUM
#define DARR_DEL_SCRAMBLE(arr, elem) memmove((arr + elem), (arr + --DARR_NUM(arr)), sizeof(*arr))

// DARR_DEL: delete elem by moving all subsequent elements over
#define DARR_DEL(arr, elem) memmove((arr + elem), (arr + elem + 1), sizeof(*arr) * (--DARR_NUM(arr) - elem))

// DARR_GROW: double length of array (depending on DARR_GROWTH_FACTOR)
#define DARR_GROW(arr) DARR_LEN(arr)*=DARR_GROWTH_FACTOR;\
arr = DARR_REALLOC(arr, DARR_LEN(arr));

// DARR_PUT: put elem on top of darr, at DARR_NUM
#define DARR_PUT(arr, elem) if ((DARR_NUM(arr) + 1) >= (DARR_LEN(arr))) {\
DARR_GROW(arr);\
}\
arr[DARR_NUM(arr)++] = elem;

// DARR_POP: get top element of darr, and "remove" it by decrementing DARR_NUM
#define DARR_POP(arr) arr[--DARR_NUM(arr)]

// DARR_FREE: free whole darr
#define DARR_FREE(arr) free((((size_t* )arr) + DARR_LEN_POSITION))

#endif /* DARR_H */
