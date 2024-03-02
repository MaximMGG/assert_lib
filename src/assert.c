#include "../headers/assert.h"
#include <util/util.h>
#include <time.h>
// #include <stdlib.h>
#include <string.h>

#define FUNC_NAME(f) #f

#define TEST_FILE "=> %s\n"
#define TEST_FUNC_MSG_TIME "\t[==>> ASSERT: FUNC: %s -> %s, TIME: %ld ms]\n"
#define TEST_FUNC_MSG_TIME_MSG "\t[==>> ASSERT: FUNC: %s -> %s, TIME: %ld ms, report: %s\n]"
#define TEST_MSG "[====>>>>] ASSERT: TESTED: %d | PASSING: \033[32m%d\033[0m | FAILING: \033[31m%d\033[0m | CRASHING: %d\n"
#define TEST_TOTAL_TIME_MSG "[====>>>>] ASSERT: TOTAL TIME IS: %ld ms\n"

const char *F_PASS = "\033[32mPASS\033[0m";
const char *F_FAIL = "\033[31mFAIL\033[0m";
const char *F_CRASH = "\033[93mCRASH\033[0m";

static i32 total_tests;
static i32 passing_tests;
static i32 failing_tests;
static i32 crashing_tests;
static i64 test_start_time;
static i64 test_total_time;
static i64 test_func_time;

static i8 _ASSERT_SHOW_FUNC = false;
static i8 _ASSERT_SHOW_FUNC_TIME = false;
static i8 _ASSERT_SHOW_TOTAL_TIME = false;
static i8 _ASSERT_SHOW_ASSERT_MSG = false;
static i8 _ASSERT_LOG_RESULT = false;
static i8 _ASSERT_CRASH_WHEN_FAIL = false;

#define ASSERT_PASS 1
#define ASSERT_FAIL 2
#define ASSERT_CRASH 3
#define ASSERT_WAIT 0

static i8 assert_status;
static char fail_msg[128];

static List *funcs;

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
    if (flags & ASSERT_SHOW_FUNC) {
        _ASSERT_SHOW_FUNC = true;
        funcs = list_create(0, M_STRING);
    }
    if (flags & ASSERT_SHOW_FUNC_TIME) {
        _ASSERT_SHOW_FUNC_TIME = true;
    }
    if (flags & ASSERT_SHOW_TOTAL_TIME) {
        _ASSERT_SHOW_TOTAL_TIME = true;
        test_start_time = clock();
    }
    if (flags & ASSERT_LOG_RESULT) {
        _ASSERT_LOG_RESULT = true;
    }
    if (flags & ASSERT_SHOW_ASSERT_MSG) {
        _ASSERT_SHOW_ASSERT_MSG = true;
    }
    if (flags & ASSERT_CRASH_WHEN_FAIL) {
        _ASSERT_CRASH_WHEN_FAIL = true;
    }
    assert_status = ASSERT_WAIT;
}

void assert_coll(void (*func_test)()) {
    time_t f_start = clock();
    func_test();
    time_t f_finish = clock();
    if (_ASSERT_SHOW_FUNC) {
        char buf[200];
        memset(buf, 0 , 200);
        if (_ASSERT_SHOW_FUNC_TIME) {
            test_func_time = (f_finish - f_start) / (CLOCKS_PER_SEC * 1000);
            if (_ASSERT_SHOW_ASSERT_MSG) {
                snprintf(buf, 200, TEST_FUNC_MSG_TIME_MSG, FUNC_NAME(func_test), assert_get_status(), test_func_time, fail_msg);
            } else {
                snprintf(buf, 200, TEST_FUNC_MSG_TIME, FUNC_NAME(func_test), assert_get_status(), test_func_time);
            }
        }
    }
    assert_status = ASSERT_WAIT;
}

void assert_true(boolean expression, char *msg) {

}


void assert_false(boolean expression, char *msg) {
    if (assert_status == ASSERT_FAIL || assert_status == ASSERT_CRASH) {
        return;
    }
    if (expression == 0) {
        assert_status = ASSERT_PASS;
    } else if (expression == 1){
#ifdef _ASSERT_SHOW_ASSERT_MSG
    #ifdef _ASSERT_SHOW_FUNC
        strcpy(fail_msg, msg);
    #endif
#endif
        assert_status = ASSERT_FAIL;
    } else {
        assert_status = ASSERT_CRASH;
    }

}

void assert_null(void *p, char *msg) {
    if (p == NULL) {
        assert_status = ASSERT_PASS;
    } else {
        assert_status = ASSERT_FAIL;
#ifdef _ASSERT_SHOW_ASSERT_MSG
    #ifdef _ASSERT_SHOW_FUNC
        strcpy(fail_msg, msg);
    #endif
#endif
    }
}

void end_assert();
