#include <unity.h>
#include <forecast/com.hpp>
#include <string>

using namespace forecast;
using namespace forecast::com;

void comEscape() {
    uint8_t unescaped[] = {0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b};
    uint8_t groundTrue[] = {0x00, 0x00, 0x01, 0x1b, 0x02, 0x1b,
                            0x03, 0x04, 0x1b, 0x1b, 0x1b, 0x1b};
    uint8_t escaped[24];  // 12 should be enough

    auto sz = escape(unescaped, escaped, sizeof(unescaped), 24);

    TEST_ASSERT_MESSAGE(sz == sizeof(groundTrue),
                        std::string(std::to_string(sz) +
                                    "!=" + std::to_string(sizeof(groundTrue)))
                            .c_str());

    for (size_t i = 0; i < sz; ++i) {
        auto msg = "escaped[" + std::to_string(i) +
                   "] is different from groundTrue[" + std::to_string(i) + "]";
        TEST_ASSERT_MESSAGE(escaped[i] == groundTrue[i], msg.c_str());
    }
}

void comUnescape() {
    uint8_t unescaped[24];
    uint8_t groundTrue[] = {0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b};
    uint8_t escaped[] = {0x00, 0x00, 0x01, 0x1b, 0x02, 0x1b,
                         0x03, 0x04, 0x1b, 0x1b, 0x1b, 0x1b};

    auto sz = unescape(escaped, unescaped, sizeof(escaped), 24);

    TEST_ASSERT_MESSAGE(sz == sizeof(groundTrue),
                        std::string(std::to_string(sz) +
                                    "!=" + std::to_string(sizeof(groundTrue)))
                            .c_str());

    for (size_t i = 0; i < sz; ++i) {
        auto msg = "unescaped[" + std::to_string(i) +
                   "] is different from groundTrue[" + std::to_string(i) + "]";
        TEST_ASSERT_MESSAGE(unescaped[i] == groundTrue[i], msg.c_str());
    }
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(comEscape);
    RUN_TEST(comUnescape);

    UNITY_END();
}