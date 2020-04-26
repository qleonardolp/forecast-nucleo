#include <mbed.h>
#include <debug.hpp>
#include <forecast/App.hpp>
#include <forecast/controllers/ForcePID.hpp>
#include <memory>

int main() {
    forecast::App app;
    app.setLogger([](const forecast::Hardware* hw, const forecast::Controller*,
                     const forecast::Controller*) {
        /* return std::vector<float>{hw->getTauM().val,
                                  hw->getThetaM().val,
                                  0.f,
                                  0.f,
                                  0.f,
                                  0.f,
                                  0.f,
                                  0.f}; */
        return std::vector<float>{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, hw->getT(),
                                  hw->getDT()};
        /* hw->getThetaM().val, hw->getThetaE().val,
          hw->getTauM().val, hw->getTauE().val, hw->getTauS().val,
          hw->getT(), hw->getDT()}; */
    });

    app.setEnvRefGen(
        [](const forecast::Hardware* hw) { return utility::ddvar(); });

    app.setMotorRefGen([](const forecast::Hardware* hw) {
        utility::ddvar test;
        test.val = 0.075f + 0.025f * sin(2.0f * 3.14f * 1.0f * hw->getT());
        test.dval = 0.0f;
        test.ddval = 0.0f;
        return test;
    });

    app.setMotor(new forecast::ForcePID);
    app.setEnviorment(new forecast::ForcePID);

    app.waitConnection();

    app.requireMotorParams();
    app.requireEnvironmentParams();

    auto freq = app.requireFloatValue("frequency of the loop");

    app.execControlLoop(static_cast<ulong>(freq));
}

// #include <forecast/debug.hpp>
// int main() {
//     DEBUG_INFO("0123456789\r\n");
//     // Serial debug(PC_10, PC_11, 9600);
//     // debug.printf("0123456789\r\n");
// }
