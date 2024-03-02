#include "../headers/assert.h"
#include <util/util.h>
#include <time.h>
// #include <stdlib.h>
#include <string.h>

#define FUNC_NAME(f) #f

#define TEST_FILE "=> %s\n"
#define TEST_FUNC_MSG_TIME "\t[==>> ASSERT => FUNC: %s -> %s, TIME: %ld ms]\n"
#define TEST_FUNC_MSG_TIME_MSG "\t[==>> ASSERT => FUNC: %s -> %s, TIME: %ld ms, report: %s\n]"
#define TEST_FUNC_MSG "\t[==>> ASSERT => FUNC: %s -> %s\n]"
#define TEST_FUNC_MSG_MSG "\t[==>> ASSERT => FUNC: %s -> %s, report %s\n]"
#define TEST_MSG "[====>>>>] ASSERT => TESTED: %d | PASSING: \033[32m%d\033[0m | FAILING: \033[31m%d\033[0m | CRASHING: %d\n"
#define TEST_TOTAL_TIME_MSG "[====>>>>] ASSERT => TOTAL TIME IS: %ld ms\n"

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
static char current_file[64];

static List *funcs;


static void assert_write_fail_msg(char *msg) {
    if (msg == NULL) {
        strcpy(fail_msg, "fail");
    } else {
        strcpy(fail_msg, msg);
    }
}

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

static const char *assert_get_status_fail_msg() {
    if (assert_status == ASSERT_PASS) {
        return "SUCCESS";
    } else {
        return fail_msg;
    }
}

static void print_all_stuff() {

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

void assert_coll_(void (*func_test)(), char *file) {
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
        } else {
            if (_ASSERT_SHOW_ASSERT_MSG) {
                snprintf(buf, 200, TEST_FUNC_MSG_MSG, FUNC_NAME(func_test), assert_get_status(), fail_msg);

            }
        }
    }
    assert_status = ASSERT_WAIT;
}

void assert_true(boolean expression, char *msg) {
    if (expression == true) {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_PASS;
        } else {
            return;
        }
    } else if (expression == false) {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_FAIL;
            if (_ASSERT_SHOW_ASSERT_MSG) {
                assert_write_fail_msg(msg);
            }
        } else {
            return;
        }
    } else {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_CRASH;
            if (_ASSERT_SHOW_ASSERT_MSG) {
                assert_write_fail_msg(msg);
            }
        } else {
            return;
        }
    }
}


void assert_false(boolean expression, char *msg) {
    if (expression == false) {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_PASS;
        } else {
            return;
        }
    } else if (expression == true) {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_FAIL;
            if (_ASSERT_SHOW_ASSERT_MSG) {
                assert_write_fail_msg(msg);
            }
        } else {
            return;
        }
    } else {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_CRASH;
            if (_ASSERT_SHOW_ASSERT_MSG) {
                assert_write_fail_msg(msg);
            }
        } else {
            return;
        }
    }
}

void assert_null(void *p, char *msg) {
    if (p == NULL) {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_PASS;
        }
    } else {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_write_fail_msg(msg);
            assert_status = ASSERT_FAIL;
        } else {
            return;
        }
    }
}

void assert_not_null(void *p, char *msg) {
    if (p != NULL) {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_status = ASSERT_PASS;
        }
    } else {
        if (assert_status != ASSERT_FAIL && assert_status != ASSERT_CRASH) {
            assert_write_fail_msg(msg);
            assert_status = ASSERT_FAIL;
        } else {
            return;
        }
    }
}

void end_assert() {
    print_all_stuff();
    list_free_all(funcs);
}
