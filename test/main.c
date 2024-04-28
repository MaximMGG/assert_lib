#include "../headers/assert.h"

void sumtest() {
    int a = 4;
    int b = 4;
    assert_true(a + b == 7, "Incorrent sum");
}

void subtest() {
    int a = 4;
    int b = 4;
    assert_true(a - b == 0, "Incorrent sub");
}


void nulltest() {
    char *c = "123";
    void *b = c;
    assert_null(b, "Impossible");
}

void notnulltest() {
    char *name = "Bob";
    assert_not_null(name, "name is null");
}

void multestfail() {
    int a = 2;
    int b = {2};
    assert_false(a * b == 4, "Shoud be incorrent");
}

void severaltest() {
    int a = 4;
    int b = 8;
    int c = 12;

    assert_true(a + b == 11, "incorrent sum2");
    assert_true(a + b + c == 24, "Incorrent sum3");

    assert_true(a * b == 30, "Incorrect mult");
}


int main() {
    assert_begin(ASSERT_DEFAULT | ASSERT_LOG_RESULT);
    assert_call(sumtest);
    assert_call(subtest);
    assert_call(nulltest);
    assert_call(notnulltest);
    assert_call(multestfail);
    assert_call(severaltest);
    assert_end();
    return 0;
}
