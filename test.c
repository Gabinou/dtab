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

#define TEMPLATE_TYPES REGISTER_ENUM(uint8_t) \
REGISTER_ENUM(int8_t) \
REGISTER_ENUM(uint16_t) \
REGISTER_ENUM(int16_t) \
REGISTER_ENUM(uint32_t) \
REGISTER_ENUM(int32_t) \
REGISTER_ENUM(uint64_t) \
REGISTER_ENUM(int64_t) \
REGISTER_ENUM(float) \
REGISTER_ENUM(double)

/*******************************ACTUAL TESTS***************************/
struct Position {
    uint32_t x;
    uint32_t y;
};

void test_struct() {
    struct dtab * dtab_test1;
    DTAB_INIT(dtab_test1, struct Position);
    lok(dtab_test1->len == DTAB_LEN_INIT);
    struct Position * temp_posp = DTAB_GET(dtab_test1, "Test");
    lok(temp_posp == NULL);
    struct Position temp_pos = {.x = 1, .y = 2};
    lok(temp_pos.x == 1);
    lok(temp_pos.y == 2);
    DTAB_ADD(dtab_test1, temp_pos, "Test");
    temp_posp = (struct Position *) DTAB_GET(dtab_test1, "Test");
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
    DTAB_ADDP(dtab_test1, temp_posp2, "Test");
    temp_posp = DTAB_GET(dtab_test1, "Test");
    lok(temp_posp != NULL);
    lok(temp_posp->x == temp_posp2->x);
    lok(temp_posp->y == temp_posp2->y);

    temp_posp = DTAB_GET(dtab_test1, DTAB_STRINGIFY(Test));
    lok(temp_posp != NULL);
    lok(temp_posp->x == temp_posp2->x);
    lok(temp_posp->y == temp_posp2->y);

    temp_posp = DTAB_GETS(dtab_test1, Test);
    lok(temp_posp != NULL);
    lok(temp_posp->x == temp_posp2->x);
    lok(temp_posp->y == temp_posp2->y);

    struct dtab * dtab_test2 = DTAB_INIT(dtab_test2, struct Position);
    lok(dtab_test2->len == DTAB_LEN_INIT);

    temp_posp2->x = 1;
    temp_posp2->y = 1;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test3");

    temp_posp2->x = 2;
    temp_posp2->y = 2;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test4");

    temp_posp2->x = 3;
    temp_posp2->y = 3;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test5");

    temp_posp2->x = 4;
    temp_posp2->y = 4;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test6");

    temp_posp2->x = 5;
    temp_posp2->y = 5;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test7");

    temp_posp2->x = 6;
    temp_posp2->y = 6;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test8");

    temp_posp2->x = 7;
    temp_posp2->y = 7;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test8");

    temp_posp2->x = 8;
    temp_posp2->y = 8;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test9");

    temp_posp = DTAB_GET(dtab_test1, "Test3");
    lok(temp_posp != NULL);

    temp_posp = DTAB_GET(dtab_test1, "Test4");
    lok(temp_posp != NULL);

    temp_posp = DTAB_GET(dtab_test1, "Test5");
    lok(temp_posp != NULL);

    temp_posp = DTAB_GET(dtab_test1, "Test6");
    lok(temp_posp != NULL);

    DTAB_DEL(dtab_test1, "Test6");
    temp_posp = DTAB_GET(dtab_test1, "Test6");
    lok(temp_posp == NULL);

    temp_posp = DTAB_GET(dtab_test1, "Test3");
    lok(temp_posp != NULL);
    lok(temp_posp->x == 1);
    lok(temp_posp->y == 1);

    temp_posp = DTAB_GET(dtab_test1, "Test4");
    lok(temp_posp != NULL);
    lok(temp_posp->x == 2);
    lok(temp_posp->y == 2);

    temp_posp = DTAB_GET(dtab_test1, "Test5");
    lok(temp_posp != NULL);
    lok(temp_posp->x == 3);
    lok(temp_posp->y == 3);

    temp_posp = DTAB_GET(dtab_test1, "Test8");
    lok(temp_posp != NULL);
    lok(temp_posp->x == 7);
    lok(temp_posp->y == 7);

    DTAB_DEL_SCRAMBLE(dtab_test1, "Test5");
    temp_posp = DTAB_GET(dtab_test1, "Test5");
    lok(temp_posp == NULL);

    temp_posp = DTAB_GET(dtab_test1, "Test3");
    lok(temp_posp != NULL);
    lok(temp_posp->x == 1);
    lok(temp_posp->y == 1);

    temp_posp = DTAB_GET(dtab_test1, "Test4");
    lok(temp_posp != NULL);
    lok(temp_posp->x == 2);
    lok(temp_posp->y == 2);

    temp_posp = DTAB_GET(dtab_test1, "Test8");
    lok(temp_posp != NULL);
    lok(temp_posp->x == 7);
    lok(temp_posp->y == 7);

    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test10");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test11");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test12");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test13");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test14");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test15");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test16");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test17");
    temp_posp2->x = 9;
    temp_posp2->y = 9;
    DTAB_ADDP(dtab_test1, temp_posp2, "Test18");
    lok(dtab_test1->len == DTAB_LEN_INIT * DTAB_GROWTH_FACTOR);

    DTAB_FREE(dtab_test2);
    DTAB_FREE(dtab_test1);
    free(temp_posp2);
}

#define REGISTER_ENUM(type) test_##type() {\
    struct dtab * dtab_test1;\
    DTAB_INIT(dtab_test1, uint64_t);\
    lok(dtab_test1->len == DTAB_LEN_INIT);\
    uint64_t * temp_posp = DTAB_GET(dtab_test1, "Test");\
    lok(temp_posp == NULL);\
    uint64_t tempval = 4;\
    DTAB_ADD(dtab_test1, tempval, "Test");\
    temp_posp = DTAB_GET(dtab_test1, "Test");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == tempval);\
    uint64_t temp_posp2 = 4;\
    DTAB_ADDP(dtab_test1, &temp_posp2, "Test2");\
    temp_posp = DTAB_GET(dtab_test1, "Test2");\
    lok(temp_posp != NULL);\
    lok(temp_posp2 == *temp_posp);\
    temp_posp = DTAB_GET(dtab_test1, DTAB_STRINGIFY(Test));\
    lok(temp_posp != NULL);\
    lok(temp_posp2 == *temp_posp);\
    temp_posp = DTAB_GETS(dtab_test1, Test);\
    lok(temp_posp != NULL);\
    lok(temp_posp2 == *temp_posp);\
    struct dtab * dtab_test2 = DTAB_INIT(dtab_test2, struct Position);\
    lok(dtab_test2->len == DTAB_LEN_INIT);\
    temp_posp2 = 1;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test31");\
    temp_posp2 = 2;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test3");\
    temp_posp2 = 3;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test4");\
    temp_posp2 = 4;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test5");\
    temp_posp2 = 5;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test6");\
    temp_posp2 = 6;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test7");\
    temp_posp2 = 7;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test8");\
    temp_posp2 = 8;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test9");\
    temp_posp2 = 9;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test10");\
    temp_posp = DTAB_GET(dtab_test1, "Test3");\
    lok(temp_posp != NULL);\
    temp_posp = DTAB_GET(dtab_test1, "Test4");\
    lok(temp_posp != NULL);\
    temp_posp = DTAB_GET(dtab_test1, "Test5");\
    lok(temp_posp != NULL);\
    temp_posp = DTAB_GET(dtab_test1, "Test6");\
    lok(temp_posp != NULL);\
    DTAB_DEL(dtab_test1, "Test6");\
    temp_posp = DTAB_GET(dtab_test1, "Test6");\
    lok(temp_posp == NULL);\
    temp_posp = DTAB_GET(dtab_test1, "Test3");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == 2);\
    temp_posp = DTAB_GET(dtab_test1, "Test4");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == 3);\
    temp_posp = DTAB_GET(dtab_test1, "Test5");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == 4);\
    temp_posp = DTAB_GET(dtab_test1, "Test8");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == 7);\
    DTAB_DEL_SCRAMBLE(dtab_test1, "Test5");\
    temp_posp = DTAB_GET(dtab_test1, "Test5");\
    lok(temp_posp == NULL);\
    temp_posp = DTAB_GET(dtab_test1, "Test3");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == 2);\
    temp_posp = DTAB_GET(dtab_test1, "Test4");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == 3);\
    temp_posp = DTAB_GET(dtab_test1, "Test8");\
    lok(temp_posp != NULL);\
    lok(*temp_posp == 7);\
    temp_posp2 = 9;\
    DTAB_ADD(dtab_test1, temp_posp2, "Test10");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test11");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test12");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test13");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test14");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test15");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test16");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test17");\
    DTAB_ADD(dtab_test1, temp_posp2, "Test18");\
    lok(dtab_test1->len == DTAB_LEN_INIT * DTAB_GROWTH_FACTOR);\
    DTAB_FREE(dtab_test2);\
    DTAB_FREE(dtab_test1);\
}
TEMPLATE_TYPES
#undef REGISTER_ENUM

int main() {
    globalf = fopen("dtab_test_results.txt", "w+");
    dupprintf(globalf, "\nHello, World! I am testing dtab.\n");
    lrun("test_struct", test_struct);
#define REGISTER_ENUM(type) lrun(DTAB_STRINGIFY(test_##type), test_##type);
    TEMPLATE_TYPES
#undef REGISTER_ENUM
    lresults();

    dupprintf(globalf, "dtab Test End \n \n");
    fclose(globalf);
    return (0);
}