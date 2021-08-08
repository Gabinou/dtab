#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include "dtab.h"

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
struct Position {
    uint32_t x;
    uint32_t y;
};

void test_struct() {
    struct dtab * dtab_test1;
    DTAB_INIT(dtab_test1, struct Position);
    lok(dtab_test1->len == DTAB_LEN_INIT);
    // struct Position * temp_pos = dtab_get(dtab_test1, DTAB_HASH("Test"));
    struct Position * temp_posp = DTAB_GET(dtab_test1, "Test");
    lok(temp_posp == NULL);
    struct Position temp_pos = {.x = 1, .y = 2};
    DTAB_ADD(dtab_test1, temp_pos, "Test");
    temp_posp = DTAB_GET(dtab_test1, "Test");
    lok(temp_posp != NULL);
    lok(temp_posp->x == temp_pos.x);
    lok(temp_posp->y == temp_pos.y);
    struct Position * temp_posp2 = malloc(sizeof(struct Position));
    temp_posp2->x = 2;
    temp_posp2->y = 4;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test2");
    temp_posp = DTAB_GET(dtab_test1, "Test2");
    lok(temp_posp != NULL);
    lok(temp_posp->x == temp_posp2->x);
    lok(temp_posp->y == temp_posp2->y);
    // DTAB_GET(dtab_test1, "Test");

    struct dtab * dtab_test2 = DTAB_INIT(dtab_test2, struct Position);
    lok(dtab_test2->len == DTAB_LEN_INIT);


}

int main() {
    globalf = fopen("dtab_test_results.txt", "w+");
    dupprintf(globalf, "\nHello, World! I am testing dtab.\n");
    // lrun("test_len_num", test_len_num);
    lrun("test_struct", test_struct);

    lresults();

    dupprintf(globalf, "dtab Test End \n \n");
    fclose(globalf);
    return (0);
}