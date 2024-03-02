#include "../headers/assert.h"
#include <util/util.h>


i32 total_tests;
i32 passing_tests;
i32 failing_tests;
i32 crashing_tests;
i64 test_start_time;
i64 test_total_time;
i64 test_func_time;

static List *funcs;




void begin_assert(i32 flags) {

}

void assert_coll(void (*func_test)());
void assert_true(boolean expression, char *msg);
void assert_false(boolean expression, char *msg);
void assert_null(void *, char *msg);
void end_assert();
