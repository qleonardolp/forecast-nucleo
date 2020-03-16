#include <mbed.h>
#include <forecast/App.hpp>
#include <forecast/controllers/ForcePID.hpp>
#include <memory>

int main() {
    forecast::App app;

    app.setLogger([](const forecast::Hardware* hw,
                       const forecast::Controller*,
                       const forecast::Controller*) {
        return std::vector<float>{hw->getTauM().val, hw->getThetaM().val, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
                                /* hw->getThetaM().val, hw->getThetaE().val,
                                  hw->getTauM().val, hw->getTauE().val, hw->getTauS().val,
                                  hw->getT(), hw->getDT()}; */
    });

    app.setEnvRefGen([](const forecast::Hardware* hw){
        return utility::ddvar();
    });

    app.setMotorRefGen([](const forecast::Hardware* hw){
        utility::ddvar test;
        test.val = 0.075f + 0.025f*sin(2.0f*3.14f*1.0f*hw->getT());
        test.dval = 0.0f;
        test.ddval = 0.0f;
        return test;
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
