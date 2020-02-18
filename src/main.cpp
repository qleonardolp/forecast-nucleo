#include <mbed.h>
#include <control/ForcePID.hpp>
#include <forecast/App.hpp>
#include <memory>

int main() {
    forecast::App app(256, 256);

    float d = NAN;

    app.setLogger([&d](const forecast::Hardware* hw, const control::Control*,
                       const control::Control*) {
        return std::vector<float>{d + 1.f, d + 2.f, d + 3.f, d + 4.f, d + 5.f,
                                  d + 6.f/* , d + 7.f, d + 8.f */
                                  , hw->getT(), hw->getDT()};
    });

    app.setMotor(
        std::unique_ptr<control::Control>(new control::ForcePID(nullptr)));
    app.setEnviorment(
        std::unique_ptr<control::Control>(new control::ForcePID(nullptr)));

    while (std::isnan(d))
        d = app.requireFloatValue("hello");

    app.execControlLoop(2000);
}

// #include <forecast/debug.hpp>
// int main() {
//     DEBUG_INFO("0123456789\r\n");
//     // Serial debug(PC_10, PC_11, 9600);
//     // debug.printf("0123456789\r\n");
// }
