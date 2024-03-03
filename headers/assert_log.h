#ifndef _ASSERT_LOG_H_
#define _ASSERT_LOG_H_
#include <util/m_list.h>
#include <util/m_string.h>

void alog_set_path(char *path);
void alog_log_test(List *funcs);
void alog_init(char *path);

#endif //_ASSERT_LOG_H_
