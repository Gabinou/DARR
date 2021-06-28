#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include "darr.h"

/* MINCTEST - Minimal C Test Library - 0.2.0
*  ---------> MODIFIED FOR DARR <----------
* Copyright (c) 2014-2017 Lewis Van Winkle
*
* http://CodePlea.com
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgement in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __MINCTEST_H__
#define __MINCTEST_H__
/*****************************TEST GLOBALS*****************************/
FILE * globalf;
/* NB all tests should be in one file. */
static int ltests = 0;
static int lfails = 0;

/* Display the test results. */
#define lresults() do {\
    if (lfails == 0) {\
        dupprintf(globalf,"ALL TESTS PASSED (%d/%d)\n", ltests, ltests);\
    } else {\
        dupprintf(globalf,"SOME TESTS FAILED (%d/%d)\n", ltests-lfails, ltests);\
    }\
} while (0)

/* Run a test. Name can be any string to print out, test is the function name to call. */
#define lrun(name, test) do {\
    const int ts = ltests;\
    const int fs = lfails;\
    const clock_t start = clock();\
    dupprintf(globalf,"\t%-14s", name);\
    test();\
    dupprintf(globalf,"pass:%2d   fail:%2d   %4dms\n",\
            (ltests-ts)-(lfails-fs), lfails-fs,\
            (int)((clock() - start) * 1000 / CLOCKS_PER_SEC));\
} while (0)

/* Assert a true statement. */
#define lok(test) do {\
    ++ltests;\
    if (!(test)) {\
        ++lfails;\
        dupprintf(globalf,"%s:%d error \n", __FILE__, __LINE__);\
    }} while (0)

#endif /*__MINCTEST_H__*/

void dupprintf(FILE * f, char const * fmt, ...) { // duplicate printf
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
}


/*******************************ACTUAL TESTS***************************/
void test_log2() {
    lok(log2(0.0) == -INFINITY);
    lok(log2(0.0) == -INFINITY);
    lok(log2(0) == -INFINITY);
    lok(log2(0) == -INFINITY);
    lok(log2(1.0) == 0.0);
    lok(log2(1.0) == 0);
    lok(log2(2.0) == 1.0);
    lok(log2(2.0) == 1);
}

void test_struct() {
    typedef struct temp_struct_def {
        uint8_t a;
        uint64_t b;
        float c;
    } temp_struct_def;
    size_t test_arr_len = 10;
    temp_struct_def * test_arr = DARR_INIT(test_arr, temp_struct_def, test_arr_len);
    lok(DARR_LEN(test_arr) == test_arr_len);
    lok(DARR_NUM(test_arr) == 0);
    temp_struct_def temp_struct;
    temp_struct.a = 1;
    temp_struct.b = 2;
    temp_struct.c = 3.0f;
    DARR_PUT(test_arr, temp_struct);
    lok(DARR_LEN(test_arr) == test_arr_len);
    lok(DARR_NUM(test_arr) == 1);
    lok(test_arr[0].a == 1);
    lok(test_arr[0].b == 2);
    lok(test_arr[0].c == 3.0f);
    DARR_FREE(test_arr);
}


void test_len_num() {
    size_t test_arr_len = 10;
    uint8_t * test_arr = DARR_INIT(test_arr, uint8_t, test_arr_len);
    lok(DARR_LEN(test_arr) == test_arr_len);
    lok(DARR_NUM(test_arr) == 0);
    DARR_GROW(test_arr);
    lok(DARR_LEN(test_arr) == test_arr_len * DARR_GROWTH_FACTOR);
    lok(DARR_NUM(test_arr) == 0);
    DARR_PUT(test_arr, 1);
    lok(DARR_NUM(test_arr) == 1);
    DARR_PUT(test_arr, 2);
    lok(DARR_NUM(test_arr) == 2);
    DARR_PUT(test_arr, 3);
    lok(DARR_NUM(test_arr) == 3);
    DARR_PUT(test_arr, 4);
    lok(DARR_NUM(test_arr) == 4);
    DARR_PUT(test_arr, 5);
    lok(DARR_NUM(test_arr) == 5);
    DARR_PUT(test_arr, 6);
    lok(DARR_NUM(test_arr) == 6);
    DARR_PUT(test_arr, 7);
    lok(DARR_NUM(test_arr) == 7);
    DARR_PUT(test_arr, 8);
    lok(DARR_NUM(test_arr) == 8);
    DARR_PUT(test_arr, 9);
    lok(DARR_NUM(test_arr) == 9);
    DARR_PUT(test_arr, 10);
    lok(DARR_NUM(test_arr) == 10);
    DARR_PUT(test_arr, 11);
    lok(DARR_NUM(test_arr) == 11);
    DARR_PUT(test_arr, 12);
    lok(DARR_NUM(test_arr) == 12);
    DARR_PUT(test_arr, 13);
    lok(DARR_NUM(test_arr) == 13);
    DARR_PUT(test_arr, 14);
    lok(DARR_NUM(test_arr) == 14);
    DARR_PUT(test_arr, 15);
    lok(DARR_NUM(test_arr) == 15);
    DARR_PUT(test_arr, 16);
    lok(DARR_NUM(test_arr) == 16);
    DARR_PUT(test_arr, 17);
    lok(DARR_NUM(test_arr) == 17);
    DARR_PUT(test_arr, 18);
    lok(DARR_NUM(test_arr) == 18);
    DARR_PUT(test_arr, 19);
    lok(DARR_NUM(test_arr) == 19);
    DARR_PUT(test_arr, 20);
    lok(DARR_NUM(test_arr) == 20);
    DARR_PUT(test_arr, 21);
    lok(DARR_NUM(test_arr) == 21);
    uint16_t testput = 40;
    DARR_PUT(test_arr, testput);
    lok(DARR_NUM(test_arr) == 22);

    DARR_DEL(test_arr, 1);
    lok(test_arr[0] == 1);
    lok(test_arr[1] == 3);
    lok(test_arr[2] == 4);
    lok(test_arr[3] == 5);
    lok(test_arr[4] == 6);
    lok(test_arr[5] == 7);
    lok(test_arr[6] == 8);
    lok(test_arr[7] == 9);
    lok(test_arr[8] == 10);
    lok(test_arr[9] == 11);
    lok(test_arr[10] == 12);
    lok(test_arr[11] == 13);
    lok(test_arr[12] == 14);
    lok(test_arr[13] == 15);
    lok(test_arr[14] == 16);
    lok(test_arr[15] == 17);
    lok(test_arr[16] == 18);
    lok(test_arr[17] == 19);
    lok(test_arr[18] == 20);
    lok(test_arr[19] == 21);
    lok(test_arr[20] == testput);
    lok(DARR_NUM(test_arr) == 21);
    DARR_DEL(test_arr, 300);
    lok(DARR_NUM(test_arr) == 21);
    DARR_DEL_SCRAMBLE(test_arr, 300);
    lok(DARR_NUM(test_arr) == 21);

    DARR_DEL_SCRAMBLE(test_arr, 1);
    lok(test_arr[0] == 1);
    lok(test_arr[1] == testput);
    lok(test_arr[2] == 4);
    lok(test_arr[3] == 5);
    lok(test_arr[4] == 6);
    lok(test_arr[5] == 7);
    lok(test_arr[6] == 8);
    lok(test_arr[7] == 9);
    lok(test_arr[8] == 10);
    lok(test_arr[9] == 11);
    lok(test_arr[10] == 12);
    lok(test_arr[11] == 13);
    lok(test_arr[12] == 14);
    lok(test_arr[13] == 15);
    lok(test_arr[14] == 16);
    lok(test_arr[15] == 17);
    lok(test_arr[16] == 18);
    lok(test_arr[17] == 19);
    lok(test_arr[18] == 20);
    lok(test_arr[19] == 21);
    lok(DARR_NUM(test_arr) == 20);

    lok(DARR_POP(test_arr) == 21);
    lok(DARR_NUM(test_arr) == 19);

    lok(DARR_NUM(test_arr) == 19);
    DARR_DEL(test_arr, 18);
    lok(DARR_NUM(test_arr) == 18);
    DARR_DEL_SCRAMBLE(test_arr, 17);
    lok(DARR_NUM(test_arr) == 17);


    size_t test_arr2_len = 20;
    uint16_t * test_arr2 = NULL;
    test_arr2 =  DARR_INIT(test_arr2, uint16_t, test_arr2_len);
    lok(DARR_LEN(test_arr2) == test_arr2_len);
    lok(DARR_NUM(test_arr2) == 0);
    DARR_GROW(test_arr2);
    lok(DARR_LEN(test_arr2) == test_arr2_len * DARR_GROWTH_FACTOR);
    lok(DARR_NUM(test_arr2) == 0);
    DARR_FREE(test_arr);
    DARR_FREE(test_arr2);
}

int main() {
    globalf = fopen("darr_test_results.txt", "w+");
    dupprintf(globalf, "\nHello, World! I am testing darr.\n");
    lrun("log2", test_log2);
    lrun("test_len_num", test_len_num);
    lrun("test_struct", test_struct);

    lresults();

    dupprintf(globalf, "darr Test End \n \n");
    fclose(globalf);
    return (0);
}