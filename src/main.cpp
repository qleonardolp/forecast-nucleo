#include <mbed.h>
#include <forecast/App.hpp>
#include <forecast/controllers/ForcePID.hpp>
#include <memory>

int main() {
    forecast::App app;

    app.setLogger([](const forecast::Hardware* hw,
                       const forecast::Controller*,
                       const forecast::Controller*) {
        return std::vector<float>{1.f,        2.f,        3.f,
                                  4.f,        5.f,        6.f /* , 7.f, 8.f */,
                                  hw->getT(), hw->getDT()};
    });

    app.setEnvRefGen([](size_t cycle){
        return utility::ddvar();
    });
    app.setMotorRefGen([](size_t cycle){
        return utility::ddvar();
    });

    app.setMotor(new forecast::ForcePID);
    app.setEnviorment(new forecast::ForcePID);

    app.waitForHandshake();

    app.requireMotorParams();
    app.requireEnvironmentParams();
    

    app.execControlLoop(2500);
}

// #include <forecast/debug.hpp>
// int main() {
//     DEBUG_INFO("0123456789\r\n");
//     // Serial debug(PC_10, PC_11, 9600);
//     // debug.printf("0123456789\r\n");
// }
