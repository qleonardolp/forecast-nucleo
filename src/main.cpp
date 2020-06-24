#include <mbed.h>
#include <debug.hpp>
#include <forecast/App.hpp>
#include <forecast/controllers/ForcePID.hpp>
#include <forecast/controllers/ImpedanceControl.hpp>
#include <forecast/controllers/MegaPD.hpp>

#include <memory>

int main() {

    forecast::App app;
    app.setLogger([](const forecast::Hardware* hw, const forecast::Controller*,
                     const forecast::Controller*) {

        return std::vector<float>{ hw->getTauS().val, hw->getTauM().val} ; 
    });

    app.setEnvRefGen([](const forecast::Hardware* hw) { 
            utility::ddvar test;
            test.val = 0.0f;
            test.dval = 0.0f;
            test.ddval = 0.0f;
            return test;
    });

    app.setMotorRefGen([](const forecast::Hardware* hw) {
        utility::ddvar test;
        test.val = 0.2f;
        test.dval = 0.0f;
        test.ddval = 0.0f;
        return test;
    });
    
    app.setMotor(new forecast::ForcePID);
    // app.setEnviorment(new forecast::ForcePID);
    app.setEnviorment(new forecast::ImpedanceControl);
    // app.setEnviorment(new forecast::MegaPD);

    app.waitConnection();

    app.requireMotorParams();
    app.requireEnvironmentParams();

    auto freq = app.requireFloatValue("frequency of the loop");

    app.execControlLoop(static_cast<ulong>(freq));
    // app.execControlLoop(3000);
}

// #include <forecast/debug.hpp>
// int main() {
//     DEBUG_INFO("0123456789\r\n");
//     // Serial debug(PC_10, PC_11, 9600);
//     // debug.printf("0123456789\r\n");
// }
