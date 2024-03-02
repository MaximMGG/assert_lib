#ifndef _ASSERT_H_
#define _ASSERT_H_

#include <util/m_list.h>

typedef char boolean;
#define assert_coll(f) assert_coll_((void (*)()) f, __FILE__)


typedef enum {
    ASSERT_SHOW_FUNC_TIME = 0b00000001,
    ASSERT_SHOW_FUNC = 0b00010000,
    ASSERT_SHOW_TOTAL_TIME = 0b00000010,
    ASSERT_LOG_RESULT = 0b00000100,
    ASSERT_CRASH_WHEN_FAIL = 0b00001000,
    ASSERT_SHOW_ASSERT_MSG = 0b00100000

} ASSERT_FLAGS;


void assert_coll_(void (*func)(), char *file);
void assert_begin(int flags);
void assert_true(boolean expression, char *msg);
void assert_false(boolean expression, char *msg);
void assert_null(void *, char *msg);
void assert_not_null(void *p, char *msg);
void assert_end();


#endif //_ASSERT_H_
