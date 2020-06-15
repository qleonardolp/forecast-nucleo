#include <mbed.h>
#include <debug.hpp>
#include <forecast/App.hpp>
#include <forecast/controllers/ForcePID.hpp>
#include <forecast/controllers/ImpedanceControl.hpp>
#include <memory>

int main() {
    forecast::App app;
    app.setLogger([](const forecast::Hardware* hw, const forecast::Controller*,
                     const forecast::Controller*) {

        return std::vector<float>{hw->getThetaM().val, hw->getT(), hw->getDT()}; 
    });

    app.setEnvRefGen([](const forecast::Hardware* hw) { 
            utility::ddvar test;
            test.val = sin(2.0f * 3.14f * 2.0f * hw->getT());
            test.dval = 0.0f;
            test.ddval = 0.0f;
            return test;
    });

    app.setMotorRefGen([](const forecast::Hardware* hw) {
        utility::ddvar test;
        test.val = sin(2.0f * 3.14f * 2.0f * hw->getT());
        test.dval = 0.0f;
        test.ddval = 0.0f;
        return test;
    });

    app.setMotor(new forecast::ForcePID);
    // app.setEnviorment(new forecast::ForcePID);
    app.setEnviorment(new forecast::ImpedanceControl);

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
