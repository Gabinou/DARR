
#ifndef DARR_H
#define DARR_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define DARR_GROWTH_FACTOR 2
#define DARR_LEN(arr) (*((size_t *)arr - 2)) // allocated length
#define DARR_NUM(arr) (*((size_t *)arr - 1)) // number of active elements
#define DARR_INIT(arr, type, len) (type*)(((size_t* )malloc(sizeof(size_t)*2 + sizeof(type)*(len)))+2);\
    (*((size_t *)arr - 2))=len
#define DARR_REALLOC(arr, len) (void *)((size_t* )realloc(((size_t* )arr - 2), (sizeof(size_t)*2 + (sizeof(*arr))*(len)))+2)
#define DARR_DEL(arr, elem, bytesize, num) memcpy((arr + elem), (arr + (num - 1)), bytesize)
#define DARR_GROW(arr) DARR_LEN(arr)*=DARR_GROWTH_FACTOR;\
arr = DARR_REALLOC(arr, DARR_LEN(arr));
#define DARR_PUT(arr, elem) if ((DARR_NUM(arr) + 1) >= (DARR_LEN(arr))) {\
DARR_GROW(arr);\
}\
arr[DARR_NUM(arr)++] = elem;
#define DARR_POP(arr) arr[--DARR_NUM(arr)]
#define DARR_FREE(arr) free((((size_t* )arr) - 2))

#endif /* DARR_H */
