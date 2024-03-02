#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <util/m_list.h>

typedef char boolean;


typedef enum {
    ASSERT_SHOW_FUNC_TIME = 0b00000001,
    ASSERT_SHOW_FUNC = 0b00010000,
    ASSERT_SHOW_TOTAL_TIME = 0b00000010,
    ASSERT_LOG_RESULT = 0b00000100,
    ASSERT_CRASH_WHEN_FAIL = 0b00001000,
    ASSERT_SHOW_ASSERT_MSG = 0b00100000

} ASSERT_FLAGS;


void begin_assert(int flags);
void assert_coll(void (*func_test)());
void assert_true(boolean expression, char *msg);
void assert_false(boolean expression, char *msg);
void assert_null(void *, char *msg);
void end_assert();


#endif //_ASSERT_H_
