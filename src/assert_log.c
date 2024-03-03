#include "../headers/assert_log.h"
#include <string.h>
#include <stdio.h>
#include <threads.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

const char *DEF_DIR_PATH = "./log/";

static char m_dir_path[256];
static char m_file_name[64];
static char m_file_path[312];

static char LOG_FINAL_MSG[256];
static char LOG_FINAL_TOTAL_TIME[64];

static void alog_check_dir_exist() {
    DIR *d = opendir(m_dir_path);
    if (d == NULL) {
        mkdir(m_dir_path, S_IWUSR | S_IRUSR | S_IXUSR);
    }
}
static void alog_set_file_name() {
    char *fmt = "Logging_%d-%d-%d.log";
    time_t t;
    t = time(&t);
    struct tm *timer = localtime(&t);
    snprintf(m_file_name, 64, fmt, timer->tm_year, timer->tm_mon, timer->tm_mday);
}

static void alog_set_file_path() {
    str *mdir = newstr(m_dir_path);
    str *mfile = newstr(m_file_name);
    mdir = str_concat(mdir, mfile);
    strcpy(m_file_path, mdir->str);

    str_free(mdir);
    str_free(mfile);
}

static void alog_check_filename() {
    DIR *d = opendir(m_dir_path);
    struct dirent *dirr;
    boolean same_name = false;

    if (d == NULL) {
        alog_check_dir_exist();
        d = opendir(m_dir_path);
    }

    while((dirr = readdir(d)) != NULL) {
        if (strcmp(m_file_name, dirr->d_name) == 0) {
            same_name = true;
            break;
        }
    }
    if (!same_name) {
        alog_set_file_name();
        alog_set_file_path();
    }
}


static int alog_start_work(void *funcs) {
    str *m_dpath = newstr(m_dir_path);
    FILE *f = fopen(m_file_path, "a");

    if (f == NULL) {
        alog_check_filename();
        f = fopen(m_file_path, "a");
    }

    time_t t = clock();
    t = time(&t);
    struct tm *timer = localtime(&t);
    char *fmt = "Start time is: %d-%d-%d:%d-%d\n";
    char buf[256];
    memset(buf, 0, 256);
    snprintf(buf, 256, fmt, timer->tm_year, timer->tm_mon, timer->tm_yday, 
                            timer->tm_hour, timer->tm_min, timer->tm_sec);
    fputs(buf, f);
    List *lfunc = (List *) funcs;

    for(int i = 0; i < lfunc->len; i++) {
        fputs(list_get(lfunc, i), f);
    }

    fputs(LOG_FINAL_MSG, f);
    if (LOG_FINAL_TOTAL_TIME[0] != 0) {
        fputs(LOG_FINAL_TOTAL_TIME, f);
    }

    fclose(f);

    return 0;
}


void alog_set_path(char *path) {
    if (path != NULL)
        strcpy(m_dir_path, path);
}

//TODO (Maxim) do multithread
void alog_log_test(List *funcs) {
    alog_start_work(funcs);
}

void alog_init(char *path) {
    if (path == NULL) {
        strcpy(m_dir_path, DEF_DIR_PATH);
    } else {
        strcpy(m_dir_path, path);
    }
}

