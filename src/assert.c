#include "../headers/assert.h"
#include <util/util.h>
#include <time.h>
// #include <stdlib.h>
#include <string.h>

#define FUNC_NAME(f) #f

#define TEST_MSG "[====>>>>] ASSERT: TESTED: %d | PASSING: %d | FAILING: %d | CRASHING: %d\n"
#define TEST_TOTAL_TIME_MSG "[====>>>>] ASSERT: TOTAL TIME IS: %ld ms\n"
#define TEST_FUNC_MSG "[==>> ASSERT: FUNC: %s -> %s, TIME: %ld ms]"

const char *F_PASS = "PASS";
const char *F_FAIL = "FAIL";
const char *F_CRASH = "CRASH";

i32 total_tests;
i32 passing_tests;
i32 failing_tests;
i32 crashing_tests;
i64 test_start_time;
i64 test_total_time;
i64 test_func_time;


#define ASSERT_PASS 1
#define ASSERT_FAIL 2
#define ASSERT_CRASH 3

i8 assert_status;

static List *funcs;
typedef struct {
    void (*func) (); 
    i64 ftime;
} funct;

static const char *assert_get_status() {
    switch (assert_status) {
        case ASSERT_PASS: {
            return F_PASS;
        } break;
        case ASSERT_FAIL: {
            return F_FAIL;
        } break;
        case ASSERT_CRASH: {
            return F_CRASH;
        } break;
    }
    return NULL;
}


void begin_assert(i32 flags) {
    if (flags & ASSERT_SHOW_FUNC_TIME) {
#define _ASSERT_SHOW_FUNC
        funcs = list_create(0, M_STRING);
    }
    if (flags & ASSERT_SHOW_TOTAL_TIME) {
#define _ASSERT_SHOW_TOTAL_TIME
        test_start_time = clock();
    }
    if (flags & ASSERT_LOG_RESULT) {
#define _ASSERT_LOG_RESULT

    }

}

void assert_coll(void (*func_test)()) {
    time_t f_start = clock();
    func_test();
    time_t f_finish = clock();
    i64 ftime = (f_finish - f_start) / (CLOCKS_PER_SEC * 1000);
    
    char buf[200];
    memset((void *) buf, 0, 200UL);

    snprintf(buf, 200, TEST_FUNC_MSG, FUNC_NAME(func_test), assert_get_status(), ftime);
}

void assert_true(boolean expression, char *msg);
void assert_false(boolean expression, char *msg);
void assert_null(void *, char *msg);
void end_assert();
