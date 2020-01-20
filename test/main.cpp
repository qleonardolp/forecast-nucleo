#include <mbed.h>
#include <unity.h>
#include <forecast/com.hpp>

void f() {
    TEST_ASSERT(false);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(f);

    UNITY_END();
}
