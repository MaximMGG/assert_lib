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
    assert_begin(ASSERT_SHOW_FUNC | ASSERT_SHOW_FUNC_TIME | ASSERT_SHOW_TOTAL_TIME | ASSERT_SHOW_ASSERT_MSG);
    assert_coll(sumtest);
    assert_coll(subtest);
    assert_coll(nulltest);
    assert_coll(notnulltest);
    assert_coll(multestfail);
    assert_coll(severaltest);
    assert_end();
    return 0;
}
