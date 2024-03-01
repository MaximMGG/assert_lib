#include "../headers/assert.h"
#include <ctime>


namespace ASSERT {

    void Assert::assert_print_result() {
        
    }

    Assert::Assert() {
        assert_total_start_time = clock();
    }
    Assert::~Assert() {
        time_t end_time = clock();
        assert_total_time = end_time - assert_total_start_time;
        assert_total_time = (assert_total_time / CLOCKS_PER_SEC * 1000);
    }

}
